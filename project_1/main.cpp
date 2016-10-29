#include <iostream>

#include <boost/graph/adjacency_list.hpp>

#include <clustering.hpp>
#include <betweeness.hpp>
#include <barabasi_albert.hpp>
#include <util.hpp>


using namespace boost;
using namespace project_1;

using std::cout;
using std::cin;
using std::endl;

using Graph = adjacency_list<vecS, vecS, undirectedS>;

void barabasi_albert_example();

int main() {
  barabasi_albert_example();
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
