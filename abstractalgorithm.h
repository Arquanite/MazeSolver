#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H

#include "graf.h"
#include <QList>

class AbstractAlgorithm {
protected:
    Graf m_graph;
    QList<int> m_path;
    QList<int> m_visited;
    int m_start = 0;
    int m_end = 0;

public:
    virtual ~AbstractAlgorithm() {}
    virtual void reset();
    virtual bool step() = 0;

    virtual Graf graph();
    virtual void setGraph(const Graf &graph);

    virtual QList<int> path();
    virtual QList<int> visited();

    int start() const;
    void setStart(int start);
    int end() const;
    void setEnd(int end);
};

#endif // ABSTRACTALGORITHM_H
