#include "autisticsearch.h"

AutisticSearch::AutisticSearch(){

}

bool AutisticSearch::step(){
    m_path.append(counter);
    counter++;
}

void AutisticSearch::reset(){
    counter = 0;
    AbstractAlgorithm::reset();
}
