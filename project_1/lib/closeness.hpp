#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>

#include <algorithm>

#include <util.hpp>

namespace project_1 {

  using namespace boost;
  using namespace util::graph;

  template <class Graph>
  double closeness_centrality(vertex_descriptor<Graph> v, const Graph& g) {
    const auto index = get(boost::vertex_index, g);
    const size_t V = num_vertices(g);

    auto *d = new vertex_size<Graph>[V];
    std::fill_n(d, V, 0);

    auto visitor = make_bfs_visitor(record_distances(d, on_tree_edge()));
    breadth_first_search(g, v, visitor(visitor));

    const double vertex_dist = std::accumulate(d, d + V, 0.0);
    delete d;

    return (double)(V - 1) / vertex_dist;
  }

};
