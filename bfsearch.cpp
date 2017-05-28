#include "bfsearch.h"
#include <QDebug>

BFSearch::BFSearch() {}

void BFSearch::reset() {
    while (!m_queue.isEmpty()) m_queue.dequeue();
    m_preds.clear();
    AbstractAlgorithm::reset();
}

AbstractAlgorithm::AlgorithmState BFSearch::step() {
    if(m_queue.head() == m_end) return Finish;
    bool moved = false;
    int current = m_queue.dequeue();
    QList<int> sasiedzi = m_graph.at(current);
    for(int i = 0; i < sasiedzi.size(); i++) {
        if(!m_visited.contains(sasiedzi.at(i))) {
            moved = true;
            m_preds.append(current);
            current = sasiedzi.at(i);
            m_queue.enqueue(current);
            m_path.append(current);
            m_visited.append(current);
        }
    }
    if(!moved) {
        if(m_path.size() < 2) return Lost;
        m_path.pop_back();
        current = m_path.at(m_path.size()-1);
    }
    if(current == m_end) return Finish;
    qDebug() << m_queue;
    qDebug() << m_path;
    qDebug() << m_visited;
    qDebug() << m_preds;
    return Working;
}

void BFSearch::setStart(int start) {
    m_queue.enqueue(start);
    m_preds.append(-1);
    m_path.append(start);
    m_visited.append(start);
    AbstractAlgorithm::setStart(start);
}
