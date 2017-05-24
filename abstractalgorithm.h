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
    enum AlgorithmState {
        Finish,
        Lost,
        Working
    };

    virtual ~AbstractAlgorithm() {}
    virtual void reset();
    virtual AlgorithmState step() = 0;

    virtual Graf graph();
    virtual void setGraph(const Graf &graph);

    virtual QList<int> path();
    virtual QList<int> visited();

    virtual int start() const;
    virtual void setStart(int start);
    virtual int end() const;
    virtual void setEnd(int end);
};

#endif // ABSTRACTALGORITHM_H
