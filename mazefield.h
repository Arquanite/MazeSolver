#ifndef MAZEFIELD_H
#define MAZEFIELD_H

#include <QGraphicsRectItem>
#include <QPropertyAnimation>
#include <QObject>

enum class FieldType {
    Normal,
    Start,
    End
};

class MazeField : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    MazeField(int x, int y, int size);

    QColor color();
    void setColor(QColor color);

    void waitFor(FieldType type);

signals:
    void typeChanged();

private:
    void setType(FieldType type);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void updateStyle();

    bool m_active = false;
    bool m_pressed = false;
    bool m_hovered = false;

    FieldType m_type = FieldType::Normal;

    QColor m_color = Qt::white;
    QColor m_hoverColor = Qt::white;
    QColor m_pressColor = Qt::white;
};

#endif // MAZEFIELD_H
