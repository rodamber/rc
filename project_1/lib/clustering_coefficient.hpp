#pragma once

#include <boost/graph/graph_traits.hpp>

namespace project_1 {

  using namespace boost;

  template <class Graph>
  using vertex_descriptor = typename graph_traits<Graph>::vertex_descriptor;

  template <class Graph>
  double clustering_coefficient(vertex_descriptor<Graph> v, const Graph& g);

  template <class Graph>
  double average_clustering_coefficient(vertex_descriptor<Graph> v, const Graph& g);


};
