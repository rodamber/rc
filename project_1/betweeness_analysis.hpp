#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/iteration_macros.hpp>

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <all_vertex_degree.hpp>
#include <betweeness.hpp>
#include <barabasi_albert.hpp>

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

void betweeness_analysis() {
  using Graph = adjacency_list<vecS, vecS, undirectedS>;

  const size_t num_graphs = 20;
  const size_t num_nodes = 1000;

  std::clock_t c_start_1 = std::clock();

  std::cout << "Making graphs..." << std::flush;
  auto graphs = make_graphs_barabasi_albert<Graph>(num_graphs, num_nodes);
  std::cout << "done." << std::endl;

  std::clock_t c_end_1 = std::clock();
  std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
            << (c_end_1 - c_start_1) / CLOCKS_PER_SEC << " s" << std::endl;
  std::clock_t c_start_2 = std::clock();

  // Here we will store the information of which degrees we have seen already,
  // i.e., the position k of the vector will be true iff there is node with
  // degree k in one of the graphs tested.
  std::vector<bool> degrees_found(num_nodes, false);

  std::cout << "Calculating averages..." << std::flush;
  // Here we will store the sums of the average betweeness centrality scores per
  // degree over all the tested graphs.
  std::vector<double> averages_sums(num_nodes, 0.0);

  for (auto &g : graphs) {
    // Here we have the degrees for each node. Position i has the degree of
    // node with index i.
    const std::vector<size_t> degrees = all_vertex_degree<Graph>(g);

    // Update the degrees found until now.
    for (auto d: degrees) {
      degrees_found.at(d) = true;
    }

    // Here we have the betweeness centrality scores for each node. At position
    // i we have the score for node with index i.
    std::vector<double> scores = betweeness(g);

    // We store the sums of the betweeness centrality scores in a vector indexed
    // by the degrees. So at position k we have the sum of the scores of nodes
    // with degree k.
    std::vector<double> bs(num_nodes, 0.0);

    const auto index = get(vertex_index, g);
    BGL_FORALL_VERTICES_T(v, g, Graph) {
      bs.at(out_degree(v, g)) += scores.at(index[v]);
    }

    // Then we get the averages of the scores per degree.
    for (size_t k = 0; k < bs.size(); ++k) {
      // How many nodes have degree k?
      const double n = std::count(degrees.begin(), degrees.end(), k);

      // std::cout << "k = " << k << std::endl;
      // std::cout << "n = " << n << std::endl;
      // std::cout << "before: bs.at("<<k<<") = " << bs.at(k) << std::endl;

      // And now we have the average betweeness centrality per degree.
      bs.at(k) /= std::max(n, 1.0);

      // std::cout << "after: bs.at("<<k<<") = " << bs.at(k) << std::endl;
    }

    for (size_t i = 0; i < averages_sums.size(); ++i) {
      averages_sums[i] += bs[i];
    }
  }

  std::vector<double> averages;
  std::transform(averages_sums.begin(), averages_sums.end(),
                 std::back_inserter(averages),
                 [](double s) { return s / (double) num_graphs; });

  std::cout << "done." << std::endl;
  std::clock_t c_end_2 = std::clock();
  std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
            << (c_end_2 - c_start_2) / CLOCKS_PER_SEC << " s" << std::endl;

  std::vector<size_t> degrees(num_nodes, 0);
  for (size_t i = 0; i < degrees.size(); ++i) {
    degrees.at(i) = i;
  }

  // Now we will remove unwanted data. We don't want data about degrees that we
  // did not find, i.e., if none of the tested graphs had nodes with degree k,
  // then we don't want averages(k) to be 0.
  degrees.erase(std::remove_if(degrees.begin(), degrees.end(),
                               [&](size_t k) { return !degrees_found[k]; }),
                degrees.end());

  // This is a little tricky because the vectors size is varying as we remove
  // elements, but the idea continues to be to eliminate the data about degrees
  // that we did not find.
  auto it = averages.begin();
  for (size_t k = 0, i = 0; i < averages.size(); ++k) {
    if(!degrees_found[k]) {
      averages.erase(it + i);
    } else {
      ++i;
    }
  }

  // Now all we have to do is to export the data.
  std::ostringstream oss;
  oss << "betweeness-barabasi-" << num_graphs << "-" << num_nodes << ".csv";
  std::ofstream out_file(oss.str());
  util::print::to_csv(degrees, averages, out_file);
  util::print::to_csv(degrees, averages, std::cout);
}
