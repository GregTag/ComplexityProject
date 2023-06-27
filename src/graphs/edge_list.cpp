#include "edge_list.hpp"

void EdgeList::AddEdge(size_t u, size_t v) {
    edges.emplace_back(u, v);
}

size_t EdgeList::GetSize() const {
    return size;
}

const std::vector<EdgeList::Edge>& EdgeList::GetEdges() const {
    return edges;
}
