#ifndef RANDOMFIRST_H
#define RANDOMFIRST_H

#include "abstractalgorithm.h"

class RandomFirst : public AbstractAlgorithm
{
private:
    int m_current;

public:
    RandomFirst();


    // AbstractAlgorithm interface
public:
    AlgorithmState step();

    // AbstractAlgorithm interface
public:
    void setStart(int start);
};

#endif // RANDOMFIRST_H
