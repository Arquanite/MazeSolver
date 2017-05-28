#include "labiryntview.h"

LabiryntView::LabiryntView(int x, int y, QGraphicsView *view, QObject *parent) : QObject(parent), m_width(x), m_height(y), m_view(view){
    m_scene = new QGraphicsScene(this);
    m_view->setScene(m_scene);

    int mx = 64;
    m_scene->addRect(0, 0, m_width*mx, m_height*mx, QPen(QBrush(Qt::black), 7));
    for(int i=0; i<m_height; i++){
        for(int j=0; j<m_width; j++){
            MazeField *item = new MazeField(j*mx, i*mx, mx);
            m_scene->addItem(item);
            m_fields.append(item);
            connect(item, SIGNAL(typeChanged()), this, SLOT(typeChanged()));
            QGraphicsSimpleTextItem *label = new QGraphicsSimpleTextItem(QString::number(m_width*i+j));
            label->setPos(mx*j+0.4*mx, mx*i+0.4*mx);
            m_scene->addItem(label);
        }
    }
    for(int i=1; i<m_width; i++){
        int im = i*mx;
        MazeLine *item = new MazeLine(im, 0, mx, Qt::Vertical);
        item->setData(First, i-1);
        item->setData(Second, i);
        m_scene->addItem(item);
        m_edges.append(item);
    }
    for(int i=1; i<m_height; i++){
        int im = i*mx;
        MazeLine *item = new MazeLine(0, im, mx, Qt::Horizontal);
        item->setData(First, m_width*(i-1));
        item->setData(Second, m_width*i);
        m_scene->addItem(item);
        m_edges.append(item);
        for(int j=1; j<m_width; j++){
            int jm = j*mx;
            m_scene->addRect(jm-3, im-3, 6, 6, QPen(Qt::transparent), QBrush(Qt::black));
            MazeLine *item = new MazeLine(jm, im, mx, Qt::Vertical);
            item->setData(First, m_width*i+j-1);
            item->setData(Second, m_width*i+j);
            m_scene->addItem(item);
            m_edges.append(item);

            item = new MazeLine(jm, im, mx, Qt::Horizontal);
            item->setData(First, m_width*(i-1)+j);
            item->setData(Second, m_width*i+j);
            m_scene->addItem(item);
            m_edges.append(item);
        }
    }
    setNormal();
    edgeMode(true);
}

Graf LabiryntView::graph(){
    m_graf.clear();
    for(int i=0; i<m_width*m_height; i++){
        m_graf.append(QList<int>());
    }
    for(MazeLine *l : m_edges){
        if(!l->active()){
            m_graf[l->data(First).toInt()].append(l->data(Second).toInt());
            m_graf[l->data(Second).toInt()].append(l->data(First).toInt());
        }
    }
    for(int i=0; i<m_graf.size(); i++){
        QString lol;
        for(int j=0; j<m_graf.at(i).size(); j++){
            lol.append(QString::number(m_graf.at(i).at(j))+" ");
        }
    }
    return m_graf;
}

void LabiryntView::setGraph(Graf g){
    m_graf = g;
}

void LabiryntView::setPath(QList<int> path){
    setNormal();
    m_path = path;
    for(int i : path){
        m_fields[i]->waitFor(FieldType::Path);
    }
}

void LabiryntView::setVisitedList(QList<int> list){
    m_visited = list;
    for(int i : list){
        m_fields[i]->waitFor(FieldType::Visited);
    }
}

void LabiryntView::setNormal(){
    setType(FieldType::Normal);
}

void LabiryntView::setStart(){
    edgeMode(false);
    setType(FieldType::Start);
}

void LabiryntView::setEnd(){
    edgeMode(false);
    setType(FieldType::End);
}

void LabiryntView::setType(FieldType type){
    for(MazeField *field : m_fields){
        field->waitFor(type);
    }
}

void LabiryntView::typeChanged(){
    setNormal();
    edgeMode(true);
    emit success();
}

void LabiryntView::toggleRandomEdge(){
    m_edges[qrand()%m_edges.size()]->toggle();
}

void LabiryntView::edgeMode(bool active){
    Qt::MouseButton button;
    if(active) button = Qt::LeftButton;
    else button = Qt::NoButton;
    for(MazeLine *line : m_edges){
        line->setAcceptHoverEvents(active);
        line->setAcceptedMouseButtons(button);
    }
}

bool LabiryntView::editable() const {
    return m_editable;
}

void LabiryntView::setEditable(bool editable){
    edgeMode(editable);
    //if(editable) setNormal();
    setNormal();
    m_editable = editable;
}

int LabiryntView::start(){
    for(int i=0; i<m_fields.size(); i++){
        if(m_fields.at(i)->fieldType() == FieldType::Start) return i;
    }
    return -1;
}

int LabiryntView::end(){
    for(int i=0; i<m_fields.size(); i++){
        if(m_fields.at(i)->fieldType() == FieldType::End) return i;
    }
    return -1;
}
