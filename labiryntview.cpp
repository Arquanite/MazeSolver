#include "labiryntview.h"

#include <QDebug>

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

Graf LabiryntView::labirynt(){
    return m_graf;
}

void LabiryntView::setLabirynt(Graf g){
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
    setNormal();
    m_visited = list;
    for(MazeField *field : m_fields){
        field->waitFor(FieldType::Visited);
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
    qDebug()<<editable;
    edgeMode(editable);
    if(editable) setNormal();
    setNormal();
    m_editable = editable;
}
