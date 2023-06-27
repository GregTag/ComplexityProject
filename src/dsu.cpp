#include "dsu.hpp"

DisjointSetUnion::DisjointSetUnion(size_t sz) : leader(sz), rank(sz, 0) {
    Initialize(sz);
}

size_t DisjointSetUnion::Get(size_t x) {
    return (leader[x] == leader[leader[x]] ? leader[x] : leader[x] = Get(leader[x]));
}

void DisjointSetUnion::Unite(size_t a, size_t b) {
    a = Get(a);
    b = Get(b);

    if (rank[a] < rank[b]) {
        std::swap(a, b);
    } else if (rank[a] == rank[b]) {
        ++rank[a];
    }

    leader[b] = a;
}

bool DisjointSetUnion::InSameSet(size_t a, size_t b) {
    return Get(a) == Get(b);
}

void DisjointSetUnion::Reset() {
    rank.assign(leader.size(), 0);
    Initialize(leader.size());
}

void DisjointSetUnion::Initialize(size_t sz) {
    for (size_t i = 0; i < sz; ++i) {
        leader[i] = i;
    }
}
