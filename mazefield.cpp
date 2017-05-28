#include "mazefield.h"

#include <QPen>
#include <QDebug>

MazeField::MazeField(int x, int y, int size) : QGraphicsRectItem(x+3, y+3, size-6, size-6){
    setAcceptHoverEvents(true);
    updateStyle();
    setPen(QPen(Qt::transparent));
}

QColor MazeField::color(){
    return m_color;
}

void MazeField::setColor(QColor color){
    m_color = color;
    setBrush(QBrush(color));
}

void MazeField::waitFor(FieldType type){
    if(m_type == FieldType::Path && type == FieldType::Visited) return;
    if(type == FieldType::Normal && !m_active) setType(type);
    else if(m_type != FieldType::Start && m_type != FieldType::End && (type == FieldType::Visited || type == FieldType::Path)){
        setType(type);
        return;
    }
    if(m_type == type) setType(FieldType::Normal);
    if(m_type == FieldType::Normal || m_type == FieldType::Path || m_type == FieldType::Visited) setType(type);
    if(!m_active) setType(type);
}

void MazeField::setType(FieldType type){
    m_type = type;
    switch(m_type){
    case FieldType::Normal:
        m_pressColor = QColor("#eeeeee");
        m_hoverColor = Qt::white;
        m_active = false;
        break;

    case FieldType::Start:
        m_pressColor = QColor("#49dc49");
        m_hoverColor = QColor("#a9efa9"); // 80%
        break;

    case FieldType::End:
        m_pressColor = QColor("#d24d2b");
        m_hoverColor = QColor("#e9a695"); // 75%
        break;

    case FieldType::Path:
        m_pressColor = QColor("#ffff00");
        m_hoverColor = QColor("#ffff00");
        m_active = true;
        break;

    case FieldType::Visited:
        m_pressColor = QColor("#ccc");
        m_hoverColor = QColor("#ccc");
        m_active = true;
        break;
    }
    updateStyle();
}

void MazeField::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    m_hovered = true;
    updateStyle();
    QGraphicsRectItem::hoverEnterEvent(event);
}

void MazeField::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    m_hovered = false;
    updateStyle();
    QGraphicsRectItem::hoverEnterEvent(event);
    m_pressed = false;
}

void MazeField::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event);
    if(m_type != FieldType::Normal){
        bool prev = m_active;
        m_active = true;
        m_pressed = true;
        if(!prev) emit typeChanged();
    }
    updateStyle();
}

void MazeField::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event);
    m_pressed = false;
}

void MazeField::updateStyle(){
    QColor newColor;
    int duration = 1;
    if(m_pressed){
        duration = 250;
        newColor = m_active ? m_pressColor : m_hoverColor;
    }
    else if(m_hovered){
        newColor = m_active ? m_pressColor : m_hoverColor;
    }
    else {
        duration = 250;
        newColor = m_active ? m_pressColor : Qt::white;
    }
    QPropertyAnimation *animation = new QPropertyAnimation(this, "color");
    animation->setDuration(duration);
    animation->setStartValue(color());
    animation->setEndValue(newColor);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

FieldType MazeField::fieldType() const {
    return m_type;
}
