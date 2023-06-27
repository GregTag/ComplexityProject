#include <gtest/gtest.h>

#include <iostream>

#include "tests/checks/united_check.hpp"

TEST(DISABLED_SimpleTests, Interactive) {
    size_t n, m;
    std::cin >> n >> m;
    EdgeList graph(n);
    size_t u, v;
    for (size_t i = 0; i < m; ++i) {
        std::cin >> u >> v;
        graph.AddEdge(u, v);
    }
    UnitedCheck(graph);
}

class CompleteGraph : public ::testing::TestWithParam<int> {
   protected:
    void SetUp() override {
        size_t size = GetParam();
        graph.emplace(size);
        for (size_t u = 0; u < size; ++u) {
            for (size_t v = 0; v < u; ++v) {
                graph->AddEdge(u, v);
            }
        }
    }

    std::optional<EdgeList> graph;
};

TEST_P(CompleteGraph, Check) {
    UnitedCheck(*graph);
}

INSTANTIATE_TEST_SUITE_P(SimpleTests, CompleteGraph, ::testing::Range(2, 100),
                         ::testing::PrintToStringParamName());
