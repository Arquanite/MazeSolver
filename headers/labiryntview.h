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
    explicit LabiryntView(int w, int h, QGraphicsView *view, QObject *parent = 0);

    Graf graph();
    void setGraph(Graf g, int w, int h);
    void setPath(QList<int> path);
    void setVisitedList(QList<int> list);

    bool editable() const;
    void setEditable(bool editable);

    int start();
    int end();

    int width() const;
    int height() const;

signals:
    void success();

public slots:
    void setNormal();
    void setStart();
    void setStart(int index);
    void setEnd();
    void setEnd(int index);
    void typeChanged();
    void toggleRandomEdge();

private:
    void redraw(int w, int h);
    void setType(FieldType type);
    void edgeMode(bool active);
    void setFieldsType(FieldType type);
    int m_width;
    int m_height;
    QGraphicsView *m_view;
    QGraphicsScene *m_scene = nullptr;
    QVector<MazeLine*> m_edges;
    QVector<MazeField*> m_fields;

    QList<int> m_path;
    QList<int> m_visited;

    bool m_editable = true;

    enum Node {
        First,
        Second,
    };
};

#endif // LABIRYNTVIEW_H
