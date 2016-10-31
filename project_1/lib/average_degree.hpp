#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <algorithm>
#include <all_vertex_degree.hpp>

template<class Graph>
double average_degree(Graph& g) {
  const std::vector<size_t> degrees = all_vertex_degree(g);
  return std::accumulate(degrees.begin(), degrees.end(), 0) / degrees.size();
}
