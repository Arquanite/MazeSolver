#ifndef AUTISTICSEARCH_H
#define AUTISTICSEARCH_H

#include "abstractalgorithm.h"

class AutisticSearch : public AbstractAlgorithm {
private:
    int counter = 0;
public:
    AutisticSearch();
public:
    virtual bool step() override;
    virtual void reset() override;
    virtual void setStart(int start) override;

};

#endif // AUTISTICSEARCH_H
