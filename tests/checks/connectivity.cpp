#include "connectivity.hpp"

#include "src/dsu.hpp"

bool IsConnectedGraph(const EdgeList& graph) {
    DisjointSetUnion dsu(graph.GetSize());
    for (auto [u, v] : graph.GetEdges()) {
        if (!dsu.InSameSet(u, v)) {
            dsu.Unite(u, v);
        }
    }
    size_t leader = dsu.Get(0);
    for (size_t i = 1; i < graph.GetSize(); ++i) {
        if (leader != dsu.Get(i)) {
            return false;
        }
    }
    return true;
}
