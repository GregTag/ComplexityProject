#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <random>

#include "src/dsu.hpp"
#include "tests/checks/united_check.hpp"

class RandomGraph : public ::testing::TestWithParam<std::tuple<int, double>> {
   protected:
    void SetUp() override {
        auto [size, prob] = GetParam();
        graph.emplace(size);
        std::bernoulli_distribution coin(prob);
        DisjointSetUnion dsu(size);
        std::vector<std::vector<bool>> edges(size, std::vector<bool>(size, false));
        size_t components = size;

        while (components > 1) {
            for (size_t u = 0; u < size; ++u) {
                for (size_t v = 0; v < u; ++v) {
                    if (!edges[u][v] && coin(gen)) {
                        edges[u][v] = true;
                        graph->AddEdge(u, v);
                        if (!dsu.InSameSet(u, v)) {
                            dsu.Unite(u, v);
                            --components;
                        }
                    }
                }
            }
        }
    }

    std::optional<EdgeList> graph;
    std::random_device rd;
    std::mt19937 gen{rd()};
};

TEST_P(RandomGraph, Check1) {
    UnitedCheck(*graph);
}
TEST_P(RandomGraph, Check2) {
    UnitedCheck(*graph);
}
TEST_P(RandomGraph, Check3) {
    UnitedCheck(*graph);
}
TEST_P(RandomGraph, Check4) {
    UnitedCheck(*graph);
}
TEST_P(RandomGraph, Check5) {
    UnitedCheck(*graph);
}

INSTANTIATE_TEST_SUITE_P(QuarterProb, RandomGraph,
                         ::testing::Combine(::testing::Range(10, 100),
                                            ::testing::Values(0.25, 0.5, 0.75)));

INSTANTIATE_TEST_SUITE_P(QuarterSize, RandomGraph,
                         ::testing::Combine(::testing::Values(25, 50, 75),
                                            ::testing::Range(0.01, 1.0, 0.01)));
