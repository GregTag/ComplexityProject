#pragma once

#include "src/graphs/edge_list.hpp"

enum class Result { FOUND, IMPOSSIBLE, TIMED_OUT };

Result SolveMinimumDegreeSpanningTree(const EdgeList&, size_t);
