#include <benchmark/benchmark.h>

#include "src/spanning_tree.hpp"

static void BM_CompleteGraph(benchmark::State& state) {
    EdgeList graph(state.range(0));
    for (size_t u = 0; u < graph.GetSize(); ++u) {
        for (size_t v = 0; v < u; ++v) {
            graph.AddEdge(u, v);
        }
    }

    for (auto _ : state) {
        SpanningTree tree(graph);
        tree.ApproximateMinimumDegree();
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_CompleteGraph)
        ->RangeMultiplier(2)
        ->Range(2, 256)
        ->Threads(8)
        ->Repetitions(10)
        ->Complexity();
