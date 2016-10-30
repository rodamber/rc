#pragma once

#include <algorithm>
#include <all_vertex_degree.hpp>

template<class Graph>
double degree_distribution(size_t k, const Graph& g) {
  auto degrees = all_vertex_degree(g);
  return std::count(degrees.begin(), degrees.end(), k) / degrees.size();
}
