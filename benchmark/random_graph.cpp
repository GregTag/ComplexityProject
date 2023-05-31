#include <benchmark/benchmark.h>

#include <random>

#include "src/spanning_tree.hpp"

static void BM_RandomGraph(benchmark::State& state, double prob) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::bernoulli_distribution coin(prob);

    size_t size = state.range(0);
    size_t components;
    DisjointSetUnion dsu(size);
    std::vector<std::vector<bool>> edges(size);

    for (auto _ : state) {
        state.PauseTiming();

        components = size;
        dsu.Reset();
        for (size_t i = 0; i < size; ++i) {
            edges[i].assign(size, false);
        }

        EdgeList graph(state.range(0));

        while (components > 1) {
            for (size_t u = 0; u < size; ++u) {
                for (size_t v = 0; v < u; ++v) {
                    if (!edges[u][v] && coin(gen)) {
                        edges[u][v] = true;
                        graph.AddEdge(u, v);
                        if (!dsu.InSameSet(u, v)) {
                            dsu.Unite(u, v);
                            --components;
                        }
                    }
                }
            }
        }

        state.ResumeTiming();

        SpanningTree tree(graph);
        tree.ApproximateMinimumDegree();
    }
}

void BM_Constant(benchmark::State& state) {
    BM_RandomGraph(state, state.range(1) * 0.01);
}

void BM_Linear(benchmark::State& state) {
    BM_RandomGraph(state, state.range(1) * 0.01 / state.range(0));
}

BENCHMARK(BM_Constant)
        ->ArgsProduct({benchmark::CreateRange(2, 256, 2), benchmark::CreateDenseRange(10, 90, 10)})
        ->Threads(8)
        ->Repetitions(10);

BENCHMARK(BM_Linear)
        ->ArgsProduct({benchmark::CreateRange(2, 256, 2), benchmark::CreateDenseRange(50, 190, 10)})
        ->Threads(8)
        ->Repetitions(10);
