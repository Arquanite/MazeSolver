#ifndef MAZELINE_H
#define MAZELINE_H

#include <QGraphicsLineItem>
#include <QObject>

class MazeLine : public QObject, public QGraphicsLineItem {
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    MazeLine(int x, int y, int length, Qt::Orientation orientation);
    QPainterPath shape() const override;

    QColor color();
    void setColor(QColor color);

    bool active() const;
    void setActive(bool active);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void updateStyle();

    int m_thickness = 6;
    int m_margin = 3;
    bool m_active = true;
    bool m_pressed = false;
    bool m_hovered = false;

    QColor m_color = Qt::black;
};

#endif // MAZELINE_H
