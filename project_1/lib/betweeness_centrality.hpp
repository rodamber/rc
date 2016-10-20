#pragma once

#include <boost/graph/graph_traits.hpp>
#include <vector>

// Here we find an implementation of Brande's algorithm for finding the
// betweeness centrality of vertices of an unweighted graph.

namespace project_1 {

  using namespace boost;

  // Helper functions

  // Given a vector of doubles, returns their distribution.
  //
  // For example,
  //
  // // 2 zeros, 5 ones, 2 twos, 4 threes, 3 fours, 4 fives, 20 in total
  // auto dist = distribution({ 0, 0, 1, 1, 1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4,
  //       5, 5, 5, 5 });
  //
  // for (size_t i = 0; i < dist.size(); ++i)
  //   std::cout << "distribution[" << i << "] = " << dist.at(i) << std::endl;
  //
  // prints
  //
  //   distribution[0] = 0.1
  //   distribution[1] = 0.25
  //   distribution[2] = 0.1
  //   distribution[3] = 0.2
  //   distribution[4] = 0.15
  //   distribution[5] = 0.2
  std::vector<double> distribution(const std::vector<double> vs) {
    const size_t dist_size = std::floor(*std::max_element(vs.begin(), vs.end())) + 1;
    std::vector<double> dist(dist_size, 0.0);

    for (auto v: vs) {
      dist.at(std::floor(v))++;
    }
    const double sum = std::accumulate(dist.begin(), dist.end(), 0.0);

    for (auto &x: dist) {
      x /= sum;
    }
    return dist;
  }

  // Betweeness Centrality functions

  template <class Graph>
  using vertex_descriptor = typename graph_traits<Graph>::vertex_descriptor;

  // Returns the betweeness centrality of vertex v on the graph g.
  template <class Graph>
  double betweeness_centrality(vertex_descriptor<Graph> s, const Graph& g);


  // Returns the betweeness centrality of the vertex v on the graph g divided by
  //  the total number of pairs of vertices not including v. The resulting value
  //  will be in [0,1].
  template <class Graph>
  double normalized_betweeness_centrality(vertex_descriptor<Graph> v, const Graph& g);

  // Calculates the betweeness centrality distribution of the vertex v on the
  // graph g by using Brande's algorithm for unweighted graphs.
  template <class Graph>
  std::vector<double> betweeness_centrality_distribution(const Graph& g) {
    const auto V = num_vertices(g);
    const auto index = get(vertex_index, g);

    std::vector<double> C_b(V, 0);

    BGL_FORALL_VERTICES_T(s, g, Graph) {
      std::vector<vertex_descriptor<Graph>> S(V);
      std::queue<vertex_descriptor<Graph>> Q; Q.push(s);

      std::vector<std::vector<vertex_descriptor<Graph>>> P(V);
      std::vector<double> sigma(V, 0); sigma[index[s]] = 1;
      std::vector<double> d(V, -1); d[index[s]] = 0;

      while (!Q.empty()) {
        vertex_descriptor<Graph> v = Q.front(); Q.pop();
        S.push_back(v);

        BGL_FORALL_ADJ_T(v, w, g, Graph) {
          // w found for the first time?
          if (d[index[w]] < 0) {
            Q.push(w);
            d[index[w]] = d[index[v]] + 1;
          }
          // shortest path to w via v?
          if (d[index[w]] == d[index[v]] + 1) {
            sigma[index[w]] += sigma[index[v]];
            P[index[w]].push_back(v);
          }
        }
      }

      std::vector<double> delta(V, 0);

      // S returns vertices in order of non-increasing distance from s
      while (!S.empty()) {
        vertex_descriptor<Graph> w = S.back(); S.pop_back();

        for (auto &v : P[index[w]]) {
          delta[index[v]] +=
            (sigma[index[v]] / sigma[index[w]]) * (1 + delta[index[w]]);
        }

        if (w != s) {
          C_b[index[w]] += delta[index[w]];
        }
      }
    }

    // typedef typename graph_traits<Graph>::directed_category Cat;
    // if(boost::detail::is_directed(Cat())) {
    //   std::for_each(C_b.begin(), C_b.end(), [&V](double &b) {
    //       b /= ((V - 1) * (V - 2));
    //     });
    // } else {
    //   std::for_each(C_b.begin(), C_b.end(), [&V](double &b) {
    //       b /= ((V - 1) * (V - 2) / 2);
    //     });
    // }

    return distribution(C_b);

  }


};
