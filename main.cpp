#include <iostream>

#include "src/spanning_tree.hpp"

void PrintGraph(const LinkedList& graph) {
    std::vector<size_t> stack;
    std::cout << graph.GetSize() << " " << graph.GetSize() - 1 << "\n";
    graph.DepthFirstSearch(
            0,
            [&stack](size_t x) {
                if (stack.size() >= 2 && x == stack[stack.size() - 2]) {
                    return false;
                }
                if (stack.size() > 0) {
                    std::cout << stack.back() << " " << x << "\n";
                }
                stack.push_back(x);
                return true;
            },
            [&stack](size_t x) {
                if (x == stack.back()) {
                    stack.pop_back();
                }
                return true;
            });
}

int main() {
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
    PrintGraph(tree);
    std::cout << "Approximated minimum degree " << tree.GetMaxDegree() << "\n";
}
