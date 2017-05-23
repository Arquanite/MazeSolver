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
    void setPath(QList<int> path);
    void setVisitedList(QList<int> list);
    void redraw();

    bool editable() const;
    void setEditable(bool editable);

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

    Graf m_graf;
    QList<int> m_path;
    QList<int> m_visited;

    bool m_editable = true;

    enum Node {
        First,
        Second,
    };
};

#endif // LABIRYNTVIEW_H
