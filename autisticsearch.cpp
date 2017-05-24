#include "autisticsearch.h"

AutisticSearch::AutisticSearch(){

}

bool AutisticSearch::step(){
    if(counter == m_end) return true;
    if(m_end > m_start) counter++;
    else counter--;
    m_path.append(counter);
    if(counter == m_end) return true;
    else return false;
}

void AutisticSearch::reset(){
    counter = m_start;
    AbstractAlgorithm::reset();
}

void AutisticSearch::setStart(int start){
    counter = start;
    AbstractAlgorithm::setStart(start);
}
