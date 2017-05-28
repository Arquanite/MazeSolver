#include "randomfirst.h"
#include <QDebug>

RandomFirst::RandomFirst(){

}

AbstractAlgorithm::AlgorithmState RandomFirst::step(){
    if(m_current == m_end) return Finish;
    bool moved = false;
    QList<int> sasiedzi;
    for(int s :  m_graph.at(m_current)){
        if(!m_visited.contains(s)) sasiedzi.append(s);
    }
    qDebug()<<m_current;
    if(!sasiedzi.empty()){
        int i = qrand()%sasiedzi.size();
        moved = true;
        m_current = sasiedzi.at(i);
        m_path.append(m_current);
        m_visited.append(m_current);
    }
    if(sasiedzi.empty() && m_path.size() == 1) return Lost;
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
