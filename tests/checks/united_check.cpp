#include "united_check.hpp"

#include <gtest/gtest.h>

void UnitedCheck(const EdgeList& graph) {
    SpanningTree tree(graph);
    tree.ApproximateMinimumDegree();
    CheckSpanningTree(graph, tree);
    if (tree.GetMaxDegree() > 2) {
        EXPECT_TRUE(MinimumDegreeSpanningTreeIsGreaterThan(graph, tree.GetMaxDegree() - 2));
    }
    if (getenv("STATISTICS")) {
        ::testing::Test::RecordProperty("size", graph.GetSize());
        ::testing::Test::RecordProperty("edges", graph.GetEdges().size());
        ::testing::Test::RecordProperty("aproximated_minimum_degree", tree.GetMaxDegree());
        ::testing::Test::RecordProperty(
                "is_optimal", tree.GetMaxDegree() <= 2 || !MinimumDegreeSpanningTreeIsLessOrEqual(
                                                                  graph, tree.GetMaxDegree() - 1));
    }
}
