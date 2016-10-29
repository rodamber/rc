#pragma once

#include <algorithm>
#include <vector>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/iteration_macros.hpp>

namespace project_1 {

  using namespace boost;

  // Takes a connected, undirected and mutable graph and adds new_vertices_count
  // vertices to graph g.
  template<class Graph>
  void barabasi_albert(size_t new_vertices_count, Graph& g) {
    double degree_sum = [&]() {
      std::vector<double> degrees(num_vertices(g), 0.0);
      auto index = get(vertex_index, g);

      BGL_FORALL_VERTICES_T(u, g, Graph) {
        degrees[index[u]] = out_degree(u, g);
      }

      return std::accumulate(degrees.begin(), degrees.end(), 0.0);
    }();

    const auto ba_add_vertex = [&]() {
      vertex_descriptor<Graph> v = add_vertex(g);

      BGL_FORALL_VERTICES_T(u, g, Graph) {
        const double deg_u = out_degree(u, g);
        const double p =  deg_u / degree_sum;

        if(util::random::random_bool(p)) {
          add_edge(v, u, g);
          degree_sum += deg_u;
        }
      }

      return g;
    };

    while(new_vertices_count--) {
      ba_add_vertex();
    }

    return g;
  }

}; // namespace project_1/
