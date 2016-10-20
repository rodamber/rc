#pragma once

#include <boost/graph/graph_traits.hpp>
#include <vector>

// Here we find an implementation of Brande's algorithm for finding the
// betweeness centrality of vertices of an unweighted graph.

namespace project_1 {

  using namespace boost;


  // Helper functions

  template <class Graph>
  void betweeness_normalize(const Graph& g, std::vector<double> xs) {
    using Cat = typename graph_traits<Graph>::directed_category;

    const auto V = num_vertices(g);
    const double factor = boost::detail::is_directed(Cat()) ? 1 : 2;

    for (auto &x: xs) {
      x /= (V - 1) * (V - 2);
      x /= factor;
    }
  }


  // Betweeness Centrality functions

  template <class Graph>
  using vertex_descriptor = typename graph_traits<Graph>::vertex_descriptor;

  // Calculates the betweeness centrality distribution for all vertices on graph
  // g by using Brande's algorithm for unweighted graphs.
  //
  // If normalized = true, then the betweeness values are normalized by
  // 2 / ((n - 1) * (n - 2)) for undirected graphs, and 1 / ((n - 1) * (n - 2))
  // for directed graphs where n is the number of nodes in G.
  template <class Graph>
  std::vector<double> betweeness_centrality(const Graph& g, bool normalized = true) {
    const auto V = num_vertices(g);
    const auto index = get(vertex_index, g);

    std::vector<double> bs(V, 0); // betweeness values

    BGL_FORALL_VERTICES_T(s, g, Graph) {
      std::vector<vertex_descriptor<Graph>> stack(V);

      std::queue<vertex_descriptor<Graph>> queue;
      queue.push(s);

      // predecessors of vertex s
      std::vector<std::vector<vertex_descriptor<Graph>>> preds(V);

      std::vector<double> sigma(V, 0);
      sigma.at(index[s]) = 1;

      std::vector<double> d(V, -1);
      d.at(index[s]) = 0;

      while (!queue.empty()) {
        vertex_descriptor<Graph> v = queue.front();
        queue.pop();
        stack.push_back(v);

        BGL_FORALL_ADJ_T(v, w, g, Graph) {
          if (d.at(index[w]) < 0) { // w found for the first time?
            queue.push(w);
            d.at(index[w]) = d.at(index[v]) + 1;
          }

          if (d.at(index[w]) == d.at(index[v]) + 1) { // shortest path to w via v?
            sigma.at(index[w]) += sigma.at(index[v]);
            preds.at(index[w]).push_back(v);
          }
        }
      }

      std::vector<double> delta(V, 0);

      // stack returns vertices in order of non-increasing distance from s
      while (!stack.empty()) {
        vertex_descriptor<Graph> w = stack.back(); stack.pop_back();

        for (auto &v : preds.at(index[w])) {
          delta.at(index[v]) +=
            (sigma.at(index[v]) / sigma.at(index[w])) * (1 + delta.at(index[w]));
        }

        if (w != s) {
          bs.at(index[w]) += delta.at(index[w]);
        }
      }
    }

    if (normalized) {
      betweeness_normalize<Graph>(g, bs);
    }
    return bs;
  }

  // Returns the betweeness centrality of vertex v on the graph g.
  template <class Graph>
  double betweeness_centrality(vertex_descriptor<Graph> v, const Graph& g,
                               bool normalized = true) {
    // FIXME: C'mon there must be a better way to do this than this obvious way
    return betweeness_centrality<Graph>(g, normalized).at(get(vertex_index, g, v));
  }



};
