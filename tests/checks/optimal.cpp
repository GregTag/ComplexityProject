#include "optimal.hpp"

#include <ortools/sat/cp_model.h>
#include <ortools/sat/cp_model.pb.h>
#include <ortools/sat/cp_model_solver.h>
#include <ortools/sat/model.h>
#include <ortools/sat/sat_parameters.pb.h>
#include <ortools/util/sorted_interval_list.h>

#include <span>
#include <vector>

namespace operations_research::sat {

CpSolverStatus TryToFindConstraintSpanningTree(const EdgeList& graph, size_t k) {
    CpModelBuilder cp_model;

    std::vector<std::vector<BoolVar>> linked_list(graph.GetSize());
    auto circuit = cp_model.AddCircuitConstraint();
    for (size_t u = 0; u < graph.GetSize(); ++u) {
        for (size_t i = 1; i < k; ++i) {
            for (size_t j = 0; j < i; ++j) {
                circuit.AddArc(u * k + i, u * k + j, cp_model.NewBoolVar());
                circuit.AddArc(u * k + j, u * k + i, cp_model.NewBoolVar());
            }
        }
    }
    for (auto [u, v] : graph.GetEdges()) {
        for (size_t i = 0; i < k; ++i) {
            linked_list[u].push_back(cp_model.NewBoolVar());
            linked_list[v].push_back(cp_model.NewBoolVar());
            circuit.AddArc(u * k + i, v * k + i, linked_list[u].back());
            circuit.AddArc(v * k + i, u * k + i, linked_list[v].back());
        }

        std::span edge1(linked_list[u].end() - k, linked_list[u].end());
        std::span edge2(linked_list[v].end() - k, linked_list[v].end());
        auto sum1 = LinearExpr::Sum(edge1);
        auto sum2 = LinearExpr::Sum(edge2);
        cp_model.AddEquality(sum1, sum2);
        cp_model.AddAtMostOne(edge1);
        cp_model.AddAtMostOne(edge2);
    }

    SatParameters parameters;
    parameters.set_max_time_in_seconds(10.0);

    const CpSolverResponse response = SolveWithParameters(cp_model.Build(), parameters);
    return response.status();
}

}  // namespace operations_research::sat

using operations_research::sat::CpSolverStatus;

bool MinimumDegreeSpanningTreeIsGreaterThan(const EdgeList& graph, size_t k) {
    return operations_research::sat::TryToFindConstraintSpanningTree(graph, k) ==
           CpSolverStatus::INFEASIBLE;
}

bool MinimumDegreeSpanningTreeIsLessOrEqual(const EdgeList& graph, size_t k) {
    auto status = operations_research::sat::TryToFindConstraintSpanningTree(graph, k);
    return status == CpSolverStatus::OPTIMAL || status == CpSolverStatus::FEASIBLE;
}
