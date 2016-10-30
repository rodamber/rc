// Here we find an implementation of Brande's algorithm for finding the
// betweeness centrality of vertices of an unweighted graph.
//
// Source:
//   Ulrik Brandes, A Faster Algorithm for Betweenness Centrality
//   Journal of Mathematical Sociology 25(2):163-177, (2001)
//   http://algo.uni-konstanz.de/publications/b-fabc-01.pdf

#pragma once

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/properties.hpp>

#include <queue>
#include <vector>

#include <util.hpp>

namespace project_1 {

  using namespace boost;
  using namespace util::graph;

  // ---------------------------------------------------------------------------
  // Helper functions
  // ---------------------------------------------------------------------------

  template <class Graph>
  void betweeness_normalize(const Graph& g, std::vector<double>& xs) {
    const auto V = num_vertices(g);
    const double factor = directed<Graph>() ? 1 : 2;

    for (auto &x: xs) {
      x /= (V - 1) * (V - 2);
      x *= factor;
    }
  }


  // ---------------------------------------------------------------------------
  // Betweeness Centrality functions
  // ---------------------------------------------------------------------------

  // Calculates the betweeness centrality distribution for all vertices on graph
  // g by using Brande's algorithm for unweighted graphs.
  //
  // If normalized = true, then the betweeness values are normalized by
  // 2 / ((n - 1) * (n - 2)) for undirected graphs, and 1 / ((n - 1) * (n - 2))
  // for directed graphs where n is the number of nodes in G.
  template <class Graph>
  std::vector<double> betweeness(const Graph& g, bool normalized = true) {
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

    if (undirected<Graph>()) {
      std::for_each(scores.begin(), scores.end(), [](double &b) { b /= 2; });
    }
    if (normalized) {
      betweeness_normalize<Graph>(g, scores);
    }
    return scores;
  }

}; // namespace project_1
