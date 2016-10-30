#pragma once

#include <boost/graph/iteration_macros.hpp>

#include <util.hpp>

using namespace boost;

template <class Graph>
std::vector<size_t> all_vertex_degree(const Graph& g) {
  std::vector<size_t> degrees(num_vertices(g));
  const auto index = get(vertex_index, g);

  BGL_FORALL_VERTICES_T(v, g, Graph) {
    degrees[index[v]] = out_degree(v, g);
  }
  return degrees;
}
