#pragma once

#include <cstdio>

#include "src/graphs/edge_list.hpp"

class GraphReader {
   public:
    GraphReader(const char *);

    EdgeList ReadGraph();

   private:
    void PutEdges(EdgeList &, unsigned long *, int, int, int);

   private:
    const char *path;
    int codetype;
    FILE *file;
};
