#include <iostream>

#include "src/spanning_tree.hpp"

const size_t kSize = 100;

int main() {
    // Prepare
    EdgeList graph(kSize);
    for (size_t u = 1; u < kSize; ++u) {
        for (size_t v = 0; v < u; ++v) {
            graph.AddEdge(u, v);
        }
    }

    // Workload
    while (true) {
        SpanningTree tree(graph);
        tree.ApproximateMinimumDegree();
    }
}
