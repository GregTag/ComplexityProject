#include <iostream>

#include "src/spanning_tree.hpp"

void PrintGraph(const LinkedList& graph) {
    std::vector<bool> visited(graph.GetSize(), false);
    std::string spaces = "";
    graph.DepthFirstSearch(
            0,
            [&visited, &spaces](size_t x) {
                spaces.push_back(' ');
                spaces.push_back(' ');
                if (visited[x]) {
                    return false;
                }
                std::cout << "\n" << spaces << "└─" << x;
                visited[x] = true;
                return true;
            },
            [&spaces](size_t) {
                spaces.pop_back();
                spaces.pop_back();
                return true;
            });
    std::cout << "\n";
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
    PrintGraph(tree);
    tree.ApproximateMinimumDegree();
    PrintGraph(tree);
    std::cout << "Approximated minimum degree " << tree.GetMaxDegree() << "\n";
}
