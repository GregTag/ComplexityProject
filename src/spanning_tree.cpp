#include "spanning_tree.hpp"

const SpanningTree::Edge SpanningTree::kEmpty = {0, 0};

SpanningTree::SpanningTree(const EdgeList& graph)
        : LinkedList(graph.GetSize()), original(graph), dsu(graph.GetSize()) {
    BuildTree();
}

size_t SpanningTree::GetMaxDegree() const {
    return max_degree;
}

void SpanningTree::BuildTree() {
    for (auto [u, v] : original.GetEdges()) {
        if (!dsu.InSameSet(u, v)) {
            dsu.Unite(u, v);
            AddEdge(u, v);
        }
    }
}

void SpanningTree::InitPhase() {
    dsu.Reset();
    marks.assign(graph.size(), false);
    improvements_from.assign(graph.size(), 0);
    improvements_to.assign(graph.size(), kEmpty);

    max_degree = 0;
    for (size_t i = 0; i < graph.size(); ++i) {
        max_degree = std::max(max_degree, graph[i].size());
    }
}

void SpanningTree::DivideIntoComponents() {
    for (size_t u = 0; u < graph.size(); ++u) {
        marks[u] = graph[u].size() < max_degree - 1;
    }
    for (size_t u = 0; u < graph.size(); ++u) {
        if (!marks[u]) {
            continue;
        }
        for (size_t v : graph[u]) {
            if (marks[v] && !dsu.InSameSet(u, v)) {
                dsu.Unite(u, v);
            }
        }
    }
}

SpanningTree::Edge SpanningTree::FindEdge() {
    for (auto [u, v] : original.GetEdges()) {
        if (marks[u] && marks[v] && !dsu.InSameSet(u, v)) {
            return {u, v};
        }
    }
    return kEmpty;
}

std::vector<size_t> SpanningTree::FindCycle(size_t s, size_t t) {
    std::vector<size_t> stack;
    DepthFirstSearch(
            s,
            [&stack, t](size_t x) {
                stack.push_back(x);
                return (stack.size() < 3 || x != stack[stack.size() - 3]) && x != t;
            },
            [&stack, t](size_t x) {
                if (stack.back() == t) {
                    return false;
                }
                stack.pop_back();
                return true;
            });
    return stack;
}

void SpanningTree::Propagate(size_t x) {
    auto [u, v] = improvements_to[x];
    if (graph[u].size() == max_degree - 1) {
        Propagate(u);
    }
    if (graph[v].size() == max_degree - 1) {
        Propagate(v);
    }
    RemoveEdge(x, improvements_from[x]);
    AddEdge(u, v);
    improvements_from[x] = 0;
    improvements_to[x] = kEmpty;
}

bool SpanningTree::TryToImprove(size_t u, size_t v) {
    auto cycle = FindCycle(u, v);

    // processing k degree
    for (size_t i = 0; i < cycle.size(); ++i) {
        size_t x = cycle[i];
        if (!marks[x] && graph[x].size() == max_degree) {
            improvements_from[x] = cycle[i + (i + 1 < cycle.size() ? 1 : -1)];
            improvements_to[x] = {u, v};
            Propagate(x);
            return true;
        }
    }

    // processing k-1 degree
    cycle.pop_back();
    for (size_t i = 0; i < cycle.size(); ++i) {
        size_t x = cycle[i];
        if (!marks[x] && graph[x].size() == max_degree - 1) {
            improvements_from[x] = cycle[i + (i + 1 < cycle.size() ? 1 : -1)];
            improvements_to[x] = {u, v};
        }
        marks[x] = true;
        if (!dsu.InSameSet(x, v)) {
            dsu.Unite(x, v);
        }
    }
    return false;
}

void SpanningTree::ApproximateMinimumDegree() {
    while (true) {
        InitPhase();
        DivideIntoComponents();
        while (true) {
            auto [u, v] = FindEdge();
            if (!u && !v) {
                return;
            }
            if (TryToImprove(u, v)) {
                break;
            }
        };
    }
}
