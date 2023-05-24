#include <gtest/gtest.h>

#include <iostream>

#include "tests/checks/optimal.hpp"
#include "tests/checks/tree.hpp"

TEST(SimpleTests, Interactive) {
    size_t n, m;
    std::cin >> n >> m;
    EdgeList graph(n);
    size_t u, v;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> u >> v;
        graph.AddEdge(u, v);
    }
    SpanningTree tree(graph);
    tree.ApproximateMinimumDegree();
    CheckSpanningTree(graph, tree);
    if (tree.GetMaxDegree() > 2) {
        EXPECT_TRUE(MinimumDegreeSpanningTreeIsGreaterThan(graph, tree.GetMaxDegree() - 2));
    }
}
