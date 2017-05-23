#include "mazeline.h"

#include <QPen>
#include <QDebug>
#include <QPropertyAnimation>

MazeLine::MazeLine(int x, int y, int length, Qt::Orientation orientation){
    if(orientation == Qt::Vertical){
        setLine(x, y+m_thickness, x, y+length-m_thickness);
    }
    else {
        setLine(x+m_thickness, y, x+length-m_thickness, y);
    }
    setPen(QPen(QBrush(Qt::black), m_thickness));
    setAcceptHoverEvents(true);
}

QPainterPath MazeLine::shape() const {
    QPainterPath shape;
    QRectF rect(line().p1(), line().p2());
    float halfWidth = m_thickness/2.0;
    rect.adjust(-halfWidth-m_margin, -halfWidth-m_margin, halfWidth+m_margin, halfWidth+m_margin);
    shape.addRect(rect);
    return shape;
}

QColor MazeLine::color(){
    return m_color;
}

void MazeLine::setColor(QColor color){
    m_color = color;
    setPen(QPen(QBrush(color), m_thickness));
}

void MazeLine::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    m_hovered = true;
    updateStyle();
    QGraphicsLineItem::hoverEnterEvent(event);
}

void MazeLine::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    m_hovered = false;
    updateStyle();
    QGraphicsLineItem::hoverEnterEvent(event);
    m_pressed = false;
}

void MazeLine::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event);
    if(!m_pressed) m_active = !m_active;
    m_pressed = true;
    updateStyle();
}

void MazeLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event);
    m_pressed = false;
}

void MazeLine::updateStyle(){
    QColor newColor;
    int duration = 1;
    if(m_pressed){
        duration = 250;
        newColor = m_active ? QColor("#3399ff") : QColor("#b3d9ff");
    }
    else if(m_hovered){
        newColor = m_active ? QColor("#3399ff") : QColor("#b3d9ff"); // 85%
    }
    else {
        duration = 750;
        newColor = m_active ? Qt::black : QColor("#ddd");
    }
    QPropertyAnimation *animation = new QPropertyAnimation(this, "color");
    animation->setDuration(duration);
    animation->setStartValue(color());
    animation->setEndValue(newColor);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
//    qDebug()<<data(0).toInt()<<':'<<data(1).toInt();
}
