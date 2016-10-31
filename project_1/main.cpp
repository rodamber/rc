#include <lib/all_vertex_degree.hpp>
#include <lib/average_degree.hpp>
#include <lib/average_path_length.hpp>
#include <lib/barabasi_albert.hpp>
#include <lib/betweeness.hpp>
#include <lib/closeness.hpp>
#include <lib/clustering.hpp>
#include <lib/random.hpp>
#include <lib/small_world.hpp>
#include <lib/util.hpp>

#include <betweeness_analysis.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

int main() {
  const size_t num_graphs = 20;
  const size_t num_nodes = 1000;

  std::ostringstream file_name;
  // file_name << "results/barabasi_albert-" << num_graphs << "-" << num_nodes << ".csv";
  file_name << "results/random-" << num_graphs << "-" << num_nodes << ".csv";

  std::ofstream outfile(file_name.str());
  analysis(num_graphs, num_nodes, outfile);

  return 0;
}
