#ifndef RANDOMFIRST_H
#define RANDOMFIRST_H

#include "abstractalgorithm.h"

class RandomFirst : public AbstractAlgorithm
{
private:
    int m_current;

public:
    RandomFirst();
    AlgorithmState step();
    void setStart(int start);
};

#endif // RANDOMFIRST_H
