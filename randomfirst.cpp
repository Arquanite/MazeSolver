#include "randomfirst.h"
#include <QDebug>

RandomFirst::RandomFirst(){

}

AbstractAlgorithm::AlgorithmState RandomFirst::step(){
    if(m_current == m_end) return Finish;
    bool moved = false;
    QList<int> sasiedzi = m_graph.at(m_current);
    qDebug()<<m_current;
    for(int i=0; i<sasiedzi.size(); i++){
        if(!m_visited.contains(sasiedzi.at(i))){
            moved = true;
//            m_visited.append(m_current);
            m_current = sasiedzi.at(i);
            m_path.append(m_current);
            m_visited.append(m_current);
            break;
        }
    }
    if(!moved){
        m_path.pop_back();
        m_current = m_path.at(m_path.size()-1);
    }
    qDebug()<<"Visited:"<<m_visited;
    qDebug()<<"Path:"<<m_path;
    if(m_current == m_end) return Finish;
    return Working;
}

void RandomFirst::setStart(int start){
    m_current = start;
    m_path.append(start);
    m_visited.append(start);
    AbstractAlgorithm::setStart(start);
}
