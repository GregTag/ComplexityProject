#pragma once

#include <cstddef>
#include <set>
#include <vector>

class LinkedList {
   public:
    LinkedList(size_t);

    LinkedList(const LinkedList&) = default;

    void AddEdge(size_t, size_t);
    void RemoveEdge(size_t, size_t);
    bool CheckEdge(size_t, size_t) const;

    size_t GetSize() const;

    template <typename F, typename R>
    bool DepthFirstSearch(size_t, F&&, R&&) const;

   protected:
    std::vector<std::set<size_t>> graph;
};

template <typename F, typename R>
bool LinkedList::DepthFirstSearch(size_t x, F&& before, R&& after) const {
    if (before(x)) {
        for (auto y : graph[x]) {
            if (!DepthFirstSearch(y, before, after)) {
                break;
            }
        }
    }
    return after(x);
}
