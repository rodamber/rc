#include <boost/graph/adjacency_list.hpp>

#include <chrono>
#include <iomanip>
#include <iostream>

#include <clustering.hpp>
#include <betweeness.hpp>
#include <betweeness_analysis.hpp>
#include <barabasi_albert.hpp>
#include <util.hpp>
#include <small_world_model.hpp>
#include <random_model.hpp>
#include <average_path.cpp>

using namespace boost;
using namespace project_1;

using std::cout;
using std::cin;
using std::endl;

using Graph = adjacency_list<vecS, vecS, undirectedS>;

void barabasi_albert_example(int);
void small_world_example();
void random_model_example();

int main() {
  // betweeness_analysis();
  // barabasi_albert_example();
  // small_world_example();
  //random_model_example();
  return 0;
}

void barabasi_albert_example(int V = 1000) {
  std::cout << "Barabasi-Albert model example" << std::endl;
  std::cout << "V = " << V << std::endl;

  std::clock_t c_start = std::clock();
  auto t_start = std::chrono::high_resolution_clock::now();

  Graph g;
  barabasi_albert<Graph>(V, g);

  std::clock_t c_end = std::clock();
  auto t_end = std::chrono::high_resolution_clock::now();

  std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
            << (c_end-c_start) / CLOCKS_PER_SEC << " s\n"
            << "Wall clock time passed: "
            << std::chrono::duration<double>(t_end-t_start).count()
            << " s\n";

  // util::print::print_graph_in_adjacency_list_format(g);
}

void small_world_example() {
  int V = 0, K = 0; 
  double P = 0;

  cout << "V = "; cin >> V;
  cout << "K = "; cin >> K;
  cout << "P = "; cin >> P; cout << endl;

  Graph g = watz_strogatz_small_word<Graph>(V, K, P);
  util::print::print_graph_in_adjacency_list_format(g);
}

void random_model_example() {
  int V = 0;
  double P = 0;

  cout << "V = "; cin >> V;
  cout << "P = "; cin >> P; cout << endl;

  Graph g = random_model<Graph>(V, P);
  util::print::print_graph_in_adjacency_list_format(g);
}
