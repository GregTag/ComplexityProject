#pragma once
#include "dsu.hpp"
#include "graphs/edge_list.hpp"
#include "graphs/linked_list.hpp"

class SpanningTree : public LinkedList {
    using Edge = EdgeList::Edge;
    static const Edge kEmpty;

   public:
    explicit SpanningTree(const EdgeList&);

    void ApproximateMinimumDegree();
    size_t GetMaxDegree() const;

   private:
    void BuildTree();
    void InitPhase();
    std::vector<size_t> FindCycle(size_t, size_t);
    void DivideIntoComponents();
    void Propagate(size_t);
    bool TryToImprove(size_t, size_t);

   private:
    const EdgeList& original;
    DisjointSetUnion dsu;
    std::vector<int> marks;
    std::vector<size_t> improvements_from;
    std::vector<Edge> improvements_to;
    size_t max_degree{0};
};
