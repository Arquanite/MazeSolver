#include "abstractalgorithm.h"

int AbstractAlgorithm::start() const
{
    return m_start;
}

void AbstractAlgorithm::setStart(int start)
{
    m_start = start;
}

int AbstractAlgorithm::end() const
{
    return m_end;
}

void AbstractAlgorithm::setEnd(int end)
{
    m_end = end;
}

void AbstractAlgorithm::reset(){
    m_path.clear();
    m_visited.clear();
}

Graf AbstractAlgorithm::graph(){
    return m_graph;
}

void AbstractAlgorithm::setGraph(const Graf &graph){
    m_graph = graph;
}

QList<int> AbstractAlgorithm::path(){
    return m_path;
}

QList<int> AbstractAlgorithm::visited(){
    return m_visited;
}
