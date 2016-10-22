#pragma once

#include <boost/graph/graph_traits.hpp>

// #include <unordered_map>
#include <unordered_set>
// #include <utility>
#include <vector>

namespace project_1 {

  using namespace boost;

  template <class Graph>
  using vertex_descriptor = typename graph_traits<Graph>::vertex_descriptor;

  // Helper functions

  template <class Graph>
  inline bool undirected() {
    using Cat = typename graph_traits<Graph>::directed_category;
    return !boost::detail::is_directed(Cat());
  }

  template <class Graph>
  inline void normalize(double &x, size_t k) {
    if (k < 2)
      return;
    x /= (k * (k - 1));
  }

  template <class Graph>
  size_t num_common_adjacent_vertices(vertex_descriptor<Graph> u,
                                      vertex_descriptor<Graph> v,
                                      const Graph &g) {
    typename graph_traits<Graph>::adjacency_iterator u_it, u_end, v_it, v_end;

    tie(u_it, u_end) = adjacent_vertices(u, g);
    tie(v_it, v_end) = adjacent_vertices(v, g);

    unordered_set<int> set(u_it, u_end);
    return count_if(v_it, v_end, [&](int k) {
        return set.find(k) != set.end();
      });
  }


  // Clustering coefficient


  // Computes the local clustering coefficient for nodes on unweighted graphs.
  template <class Graph>
  double clustering(vertex_descriptor<Graph> u, const Graph &g) {
    double score = 0.0;

    BGL_FORALL_ADJ_T(u, v, g, Graph) {
      score += num_common_adjacent_vertices<Graph>(u, v, g);
    }

    normalize<Graph>(score, out_degree(u, g));
    return score;
  }

  template <class Graph>
  std::vector<double> clusterings(const Graph &g) {
    std::vector<double> scores(num_vertices(g), 0.0);
    std::vector<size_t> degrees(num_vertices(g));

    BGL_FORALL_VERTICES_T(u, g, Graph) {
      degrees[u] = out_degree(u, g);
    }

    BGL_FORALL_EDGES_T(e, g, Graph) {
      vertex_descriptor<Graph> s = source(e, g), t = target(e, g);

      if (degrees[s] < 2)
        break;

      size_t common = num_common_adjacent_vertices<Graph>(s, t, g);
      scores[s] += common;

      if (undirected<Graph>()) {
        scores[t] += common;
      }
    }

    for (size_t i = 0; i < scores.size(); ++i) {
      normalize<Graph>(scores[i], degrees[i]);
    }

    return scores;
  }

  template <class Graph>
  double average_clustering(const Graph& g) {
    auto cs = clusterings(g);
    return std::accumulate(cs.begin(), cs.end(), 0.0) / num_vertices(g);
  }


};
