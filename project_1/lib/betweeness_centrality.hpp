// Here we find an implementation of Brande's algorithm for finding the
// betweeness centrality of vertices of an unweighted graph.
//
// Source:
//   Ulrik Brandes, A Faster Algorithm for Betweenness Centrality
//   Journal of Mathematical Sociology 25(2):163-177, (2001)
//   http://algo.uni-konstanz.de/publications/b-fabc-01.pdf

// TODO: Generalize to weighted graphs

#pragma once

#include <boost/graph/graph_traits.hpp>
#include <vector>

namespace project_1 {

  using namespace boost;


  // Helper functions

  template <class Graph>
  bool is_directed() {
    using Cat = typename graph_traits<Graph>::directed_category;
    return boost::detail::is_directed(Cat());
  }

  template <class Graph>
  void betweeness_normalize(const Graph& g, std::vector<double>& xs) {
    const auto V = num_vertices(g);
    const double factor = is_directed<Graph>() ? 1 : 2;

    for (auto &x: xs) {
      x /= (V - 1) * (V - 2);
      x *= factor;
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
    using vertex = vertex_descriptor<Graph>;
    using std::vector;

    const auto V = num_vertices(g);
    const auto index = get(vertex_index, g);
    vector<double> scores(V, 0); // betweeness values

    BGL_FORALL_VERTICES_T(s, g, Graph) {
      vector<vertex> stack(V);

      std::queue<vertex> queue;
      queue.push(s);

      vector<vector<vertex>> predecessors(V);

      vector<double> sigma(V, 0);
      sigma.at(index[s]) = 1;

      vector<double> d(V, -1);
      d.at(index[s]) = 0;

      while (!queue.empty()) {
        vertex v = queue.front();

        queue.pop();
        stack.push_back(v);

        BGL_FORALL_ADJ_T(v, w, g, Graph) {
          if (d.at(index[w]) < 0) { // w found for the first time?
            queue.push(w);
            d.at(index[w]) = d.at(index[v]) + 1;
          }

          if (d.at(index[w]) == d.at(index[v]) + 1) { // shortest path to w via v?
            sigma.at(index[w]) += sigma.at(index[v]);
            predecessors.at(index[w]).push_back(v);
          }
        }
      }
      vector<double> delta(V, 0);

      // stack returns vertices in order of non-increasing distance from s
      while (!stack.empty()) {
        vertex w = stack.back(); stack.pop_back();

        for (auto &v : predecessors.at(index[w])) {
          delta.at(index[v]) +=
            (sigma.at(index[v]) / sigma.at(index[w])) * (1 + delta.at(index[w]));
        }

        if (w != s) {
          scores.at(index[w]) += delta.at(index[w]);
        }
      }
    }

    if (!is_directed<Graph>()) {
      std::for_each(scores.begin(), scores.end(), [](double &b) { b /= 2; });
    }
    if (normalized) {
      betweeness_normalize<Graph>(g, scores);
    }
    return scores;
  }

  // Returns the betweeness centrality of vertex v on the graph g.
  template <class Graph>
  double betweeness_centrality(vertex_descriptor<Graph> v, const Graph& g,
                               bool normalized = true) {
    // TODO: there must be a better way to do this
    return betweeness_centrality<Graph>(g, normalized).at(get(vertex_index, g, v));
  }



};
