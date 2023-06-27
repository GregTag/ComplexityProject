#include "united_check.hpp"

#include <gtest/gtest.h>

void UnitedCheck(const EdgeList& graph) {
    SpanningTree tree(graph);
    tree.ApproximateMinimumDegree();
    CheckSpanningTree(graph, tree);
    if (tree.GetMaxDegree() > 2) {
        auto status = SolveMinimumDegreeSpanningTree(graph, tree.GetMaxDegree() - 2);
        if (status == Result::TIMED_OUT) {
            GTEST_SKIP() << "Timed out";
        }
        EXPECT_EQ(status, Result::IMPOSSIBLE);
    }
    if (getenv("STATISTICS")) {
        ::testing::Test::RecordProperty("size", graph.GetSize());
        ::testing::Test::RecordProperty("edges", graph.GetEdges().size());
        ::testing::Test::RecordProperty("aproximated_minimum_degree", tree.GetMaxDegree());
        if (tree.GetMaxDegree() <= 2) {
            ::testing::Test::RecordProperty("is_optimal", true);
        } else {
            auto status = SolveMinimumDegreeSpanningTree(graph, tree.GetMaxDegree() - 1);
            if (status == Result::TIMED_OUT) {
                GTEST_SKIP() << "Timed out";
            }
            ::testing::Test::RecordProperty("is_optimal", status == Result::IMPOSSIBLE);
        }
    }
}
