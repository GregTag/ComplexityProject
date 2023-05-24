#include "tree.hpp"

#include <gtest/gtest.h>

#include "connectivity.hpp"

void CheckSpanningTree(const EdgeList& graph, const SpanningTree& tree) {
    ASSERT_TRUE(IsConnectedGraph(graph)) << "Original graph is not connected.";

    EXPECT_EQ(graph.GetSize(), tree.GetSize());
    std::vector<size_t> degrees(tree.GetSize(), 0);
    size_t edges = 0;
    size_t max_degree = 0;

    tree.DepthFirstSearch(
            0,
            [&degrees, &edges](size_t x) {
                ++edges;
                return !(degrees[x]++);
            },
            [](size_t x) { return true; });
    --edges;
    --degrees[0];
    EXPECT_EQ(edges + 2, tree.GetSize() * 2);
    for (size_t i = 0; i < degrees.size(); ++i) {
        EXPECT_GT(degrees[i], 0) << "Missed vertex " << i;
        max_degree = std::max(max_degree, degrees[i]);
    }
    EXPECT_EQ(max_degree, tree.GetMaxDegree());

    degrees.assign(tree.GetSize(), 0);
    edges = 0;
    max_degree = 0;
    for (auto [u, v] : graph.GetEdges()) {
        bool a = tree.CheckEdge(u, v);
        bool b = tree.CheckEdge(v, u);
        EXPECT_EQ(a, b);
        if (a) {
            ++edges;
            ++degrees[u];
            ++degrees[v];
        }
    }
    EXPECT_EQ(edges + 1, tree.GetSize());
    for (size_t i = 0; i < degrees.size(); ++i) {
        EXPECT_GT(degrees[i], 0) << "Missed vertex " << i;
        max_degree = std::max(max_degree, degrees[i]);
    }
    EXPECT_EQ(max_degree, tree.GetMaxDegree());
}
