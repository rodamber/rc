#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <clustering.hpp>
#include <betweeness.hpp>
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

void barabasi_albert_example();
void small_world_example();
void random_model_example();

int main() {
  // barabasi_albert_example();
   small_world_example();
  //random_model_example();
  return 0;
}

void barabasi_albert_example() {
  int V = 0;

  cout << "V = "; cin >> V; cout << endl;

  Graph g;
  auto u = add_vertex(g);
  auto v = add_vertex(g);
  add_edge(u, v, g);

  barabasi_albert<Graph>(V - 2, g);

  util::print::print_graph_in_adjacency_list_format(g);
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