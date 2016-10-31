#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/iteration_macros.hpp>
#include "boost/tuple/tuple.hpp"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>

#include <all_vertex_degree.hpp>
#include <betweeness.hpp>
#include <barabasi_albert.hpp>
#include <random.hpp>

using namespace boost;
using namespace project_1;

template<class Graph>
std::vector<Graph> make_graphs_barabasi_albert(int num_graphs, int num_nodes) {
  std::vector<Graph> graphs;

  for (int i = 0; i < num_graphs; ++i) {
    Graph g;
    barabasi_albert(num_nodes, g);
    graphs.push_back(g);
  }

  return graphs;
}

template<class Graph>
std::vector<Graph> make_graphs_random(int num_graphs, int num_nodes) {
  std::vector<Graph> graphs;
  double p = 0.0;

  for (int i = 0; i < num_graphs; ++i) {
    p += 0.05;
    Graph g = random_model<Graph>(num_nodes, p);
    graphs.push_back(g);
  }

  return graphs;
}


template<class Graph>
size_t all_graphs_max_degree(const std::vector<Graph>& graphs) {
  size_t max = 0;

  for (const auto& graph : graphs) {
    const std::vector<size_t> degree = all_vertex_degree(graph);
    max = std::max(max, *std::max_element(degree.begin(), degree.end()));
  }

  return max;
}

// template<class Graph>
// std::pair<std::vector<double>, std::vector<double>>
// analyze_buckets(const std::vector<Graph>& graphs) {

//   const size_t max_degree = all_graphs_max_degree<>(graphs);
//   const size_t bucket_size = 5;
//   const size_t num_buckets = max_degree / bucket_size + 1;

//   // Here we store the sums of scores for nodes with degrees in a certain
//   // interval. For each node, if its degree is k, then we sum its score to the
//   // value in the bucket of index floor(k/y).
//   std::vector<double> bucket(num_buckets, 0.0);
//   // Here we store how many node scores we added to each bucket. We will use
//   // this to take the average of each bucket.
//   std::vector<size_t> bucket_count(num_buckets, 0);

//   for (const auto& graph : graphs) {
//     // This is the map that maps nodes to their indices.
//     const auto index = get(vertex_index, graph);
//     // We store the degrees of each node. For the node of index i its degree
//     // will be degree[i].
//     const std::vector<size_t> degree = all_vertex_degree(graph);
//     // We compute the normalized betweeness centrality scores for each node...
//     const std::vector<double> score = betweeness(graph);
//     // And then we place them in their buckets.
//     BGL_FORALL_VERTICES_T(v, graph, Graph) {
//       const size_t bucket_index = degree.at(index[v]) / bucket_size;
//       bucket.at(bucket_index) += score.at(index[v]);
//       ++bucket_count.at(bucket_index);
//     }
//   }

//   // We compute the averages for each bucket (the y axis)
//   std::vector<double> bucket_average;
//   std::transform(bucket.begin(), bucket.end(), bucket_count.begin(),
//                  std::back_inserter(bucket_average),
//                  [](double sum, size_t count) { return sum / std::max(count, (size_t)1); });
//   // Then we calculate the start of each bucket (the x axis)
//   int k = -1 * (int)bucket_size;
//   std::vector<double> degree(num_buckets);
//   std::generate(degree.begin(), degree.end(),
//                 [&k]() { return (double)(k += bucket_size); });

//   // return {degree, bucket_average};
//   return std::make_pair<>(degree, bucket_average);
// }

template<class Graph>
std::vector<std::pair<double, double>> analyze(const std::vector<Graph>& graphs) {
  std::vector<std::pair<double,double>> points;

  for (const auto& graph : graphs) {
    const auto index = get(vertex_index, graph);
    const auto score = betweeness(graph);
    const auto degree = all_vertex_degree(graph);

    BGL_FORALL_VERTICES_T(v, graph, Graph) {
      points.push_back({degree.at(index[v]), score.at(index[v])});
    }
  }

  std::sort(points.begin(), points.end(),
            [](std::pair<double,double> p1, std::pair<double,double> p2) {
              return p1.first < p2.first;
            });
  return points;
}


void analysis(size_t num_graphs, size_t num_nodes, std::ostream& os) {
  using Graph = adjacency_list<vecS, vecS, undirectedS>;

  // Start recording.
  std::clock_t c_start = std::clock();

  std::cout << "Making graphs..." << std::flush;
  auto graphs = make_graphs_random<Graph>(num_graphs, num_nodes);
  std::cout << "done." << std::endl;

  // Stop recording.
  std::clock_t c_end = std::clock();
  std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
            << (c_end - c_start) / CLOCKS_PER_SEC << " s" << std::endl;

  // Start recording.
  c_start = std::clock();

  std::cout << "Analyzing..." << std::flush;

  std::vector<double> xx, yy;
  // tie(xx, yy) = analyze<>(graphs);
  auto points = analyze<>(graphs);

  // Stop recording.
  std::cout << "done." << std::endl;
  c_end = std::clock();
  std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
            << (c_end - c_start) / CLOCKS_PER_SEC << " s" << std::endl;

  std::cout << "Exporting..." << std::flush;
  // util::print::to_csv(xx, yy, os);
  util::print::to_csv(points, os);
  std::cout << "done." << std::endl;

}
