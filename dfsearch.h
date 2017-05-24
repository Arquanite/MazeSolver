#ifndef DFSEARCH_H
#define DFSEARCH_H

#include "abstractalgorithm.h"

class DFSearch : public AbstractAlgorithm{

private:
    int m_current;

public:
    DFSearch();

    // AbstractAlgorithm interface
public:
    AlgorithmState step();

    // AbstractAlgorithm interface
public:
    void setStart(int start);
};

#endif // DFSEARCH_H
