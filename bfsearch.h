#ifndef BFSEARCH_H
#define BFSEARCH_H

#include <QQueue>
#include <QMultiMap>
#include "abstractalgorithm.h"

class BFSearch : public AbstractAlgorithm
{
private:
    QQueue<int> m_queue;
    QList<int> m_preds;
public:
    BFSearch();
    void reset();
    AlgorithmState step();
    void setStart(int start);

    void deleteDeadEnd(QList<int> list, int node);
};

#endif // BFSEARCH_H
