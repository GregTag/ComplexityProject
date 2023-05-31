#include <gtest/gtest.h>

#include <functional>
#include <iostream>
#include <optional>
#include <random>

#include "src/dsu.hpp"
#include "tests/checks/united_check.hpp"

using Generator = std::function<double(int, double)>;

class RandomGraph : public ::testing::TestWithParam<std::tuple<Generator, int, int, int>> {
   protected:
    void SetUp() override {
        auto [fun, size, constant, repeat] = GetParam();
        graph.emplace(size);
        std::bernoulli_distribution coin(fun(size, constant));
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

TEST_P(RandomGraph, Check) {
    UnitedCheck(*graph);
}

INSTANTIATE_TEST_SUITE_P(ConstantProbability, RandomGraph,
                         ::testing::Combine(::testing::Values([](int, double c) {
                                                return c * 0.1;
                                            }),
                                            ::testing::Range(10, 110, 10), ::testing::Range(2, 10),
                                            ::testing::Range(0, 10)));

INSTANTIATE_TEST_SUITE_P(LinearProbability, RandomGraph,
                         ::testing::Combine(::testing::Values([](int n, double c) {
                                                return c * 0.1 / n;
                                            }),
                                            ::testing::Range(10, 110, 10), ::testing::Range(1, 20),
                                            ::testing::Range(0, 10)));
