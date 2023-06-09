#include "linked_list.hpp"

LinkedList::LinkedList(size_t n) : graph(n) {}

void LinkedList::AddEdge(size_t u, size_t v) {
    graph[u].insert(v);
    graph[v].insert(u);
}

void LinkedList::RemoveEdge(size_t u, size_t v) {
    graph[u].erase(v);
    graph[v].erase(u);
}

bool LinkedList::CheckEdge(size_t u, size_t v) const {
    return graph[u].contains(v);
}

size_t LinkedList::GetSize() const {
    return graph.size();
}
