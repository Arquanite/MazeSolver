#ifndef LABIRYNTVIEW_H
#define LABIRYNTVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>

#include "mazeline.h"
#include "mazefield.h"
#include "graf.h"

class LabiryntView : public QObject {
    Q_OBJECT
public:
    explicit LabiryntView(int x, int y, QGraphicsView *view, QObject *parent = 0);

    Graf labirynt();
    void setLabirynt(Graf g);

    QList<int> path();
    void setPath(QList<int> path);

signals:
    void success();

public slots:
    void setNormal();
    void setStart();
    void setEnd();
    void typeChanged();

private:
    void setType(FieldType type);
    void edgeMode(bool active);
    void setFieldsType(FieldType type);
    int m_width;
    int m_height;
    QGraphicsView *m_view;
    QGraphicsScene *m_scene;
    QVector<MazeLine*> m_edges;
    QVector<MazeField*> m_fields;

    enum Node{
        First,
        Second,
    };
};

#endif // LABIRYNTVIEW_H
