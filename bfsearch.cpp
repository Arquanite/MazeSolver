#include "bfsearch.h"

BFSearch::BFSearch() {}

void BFSearch::reset() {
    while (!m_queue.isEmpty()) m_queue.dequeue();
    m_preds.clear();
    AbstractAlgorithm::reset();
}

AbstractAlgorithm::AlgorithmState BFSearch::step() {
    if(m_queue.size() < 1) return Lost;
    if(m_queue.head() == m_end) {
        QList<int> temp;
        int node = m_preds.at(m_visited.indexOf(m_queue.head()));
        while(node != m_start) {
            temp.append(node);
            node = m_preds.at(m_visited.indexOf(node));
        }
        m_path = temp;
        return Finish;
    }
    bool moved = false;
    int current = m_queue.dequeue();
    QList<int> sasiedzi = m_graph.at(current);
    int node = current;
    for(int i = 0; i < sasiedzi.size(); i++) {
        if(!m_visited.contains(sasiedzi.at(i))) {
            moved = true;
            current = sasiedzi.at(i);
            m_queue.enqueue(current);
            m_preds.append(node);
            m_path.append(current);
            m_visited.append(current);
        }
    }
    if(!moved) {
        if(m_path.size() < 2) return Lost;
        m_path.removeAll(current);
        sasiedzi = m_graph.at(m_preds.at(m_visited.indexOf(current)));
        deleteDeadEnd(sasiedzi, current);
        if (m_path.size() == 0) return Lost;
        current = m_path.at(m_path.size()-1);
    }
    if(current == m_end) {
        QList<int> temp;
        int node = m_preds.at(m_visited.indexOf(current));
        while(node != m_start) {
            temp.append(node);
            node = m_preds.at(m_visited.indexOf(node));
        }
        m_path = temp;
        return Finish;
    }
    if(m_queue.size() == 0) return Lost;
    return Working;
}

void BFSearch::setStart(int start) {
    m_queue.enqueue(start);
    m_preds.append(-1);
    m_path.append(start);
    m_visited.append(start);
    AbstractAlgorithm::setStart(start);
}

void BFSearch::deleteDeadEnd(QList<int> list, int node) {
    int numberOfNodes = 0;
    for(int i = 0; i < list.size(); i++) {
        if(m_path.contains(list.at(i))) numberOfNodes++;
    }
    if(numberOfNodes < 2) {
        m_path.removeAll(node);
        int current = m_preds.at(m_visited.indexOf(node));
        if(current < 0) return;
        QList<int> sasiedzi = m_graph.at(current);
        deleteDeadEnd(sasiedzi, current);
    }
    return;
}
