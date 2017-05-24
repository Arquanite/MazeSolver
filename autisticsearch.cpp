#include "autisticsearch.h"

AutisticSearch::AutisticSearch(){

}

AbstractAlgorithm::AlgorithmState AutisticSearch::step(){
    if(counter == m_end) return Finish;
    if(m_end > m_start) counter++;
    else counter--;
    m_path.append(counter);
    if(counter == m_end) return Finish;
    else return Working;
}

void AutisticSearch::reset(){
    counter = m_start;
    AbstractAlgorithm::reset();
}

void AutisticSearch::setStart(int start){
    counter = start;
    AbstractAlgorithm::setStart(start);
}
