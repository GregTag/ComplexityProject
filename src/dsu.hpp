#pragma once

#include <vector>

class DisjointSetUnion {
   public:
    DisjointSetUnion(size_t);

    size_t Get(size_t);
    void Unite(size_t, size_t);
    bool InSameSet(size_t, size_t);
    void Reset();

   private:
    void Initialize(size_t);

   private:
    std::vector<size_t> leader;
    std::vector<size_t> rank;
};
