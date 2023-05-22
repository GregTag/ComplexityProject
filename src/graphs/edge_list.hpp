#pragma once

#include <vector>

// #include "linked_list.hpp"

class EdgeList {
   public:
    using Edge = std::pair<size_t, size_t>;

    explicit EdgeList(size_t n) : size(n) {}

    EdgeList(const EdgeList&) = default;

    void AddEdge(size_t, size_t);
    size_t GetSize() const;
    const std::vector<Edge>& GetEdges() const;
    // LinkedList ToLinkedList() const;

   private:
    size_t size;
    std::vector<Edge> edges;
};
