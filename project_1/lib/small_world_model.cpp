#include <boost/random/uniform_real_distribution.hpp>
#include <iostream>
#include <random>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"
#include <ctime>
#include <iomanip>      
#include <stdlib.h>     /* srand, rand */
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/random.hpp>

namespace project_1 {
	using namespace boost;

	typedef adjacency_list<vecS, vecS, undirectedS> Graph;
	mt19937 randgen2(static_cast<unsigned int>(std::time(0)));
	random::uniform_real_distribution<float> noise2(0, 100);

	Graph getSmallWorldModel(int nrVertex, int degree, float probability) {
		if (probability >= 100) {
			throw "Probability must be equal or lower than 100!";
		}

		// declare a graph object
		Graph g(nrVertex);

		// Generate a k-degree regular graph
		// For upper vertices
		for (int i = 0; i < nrVertex; i++) {
			for (int j = i + 1; j <= (degree / 2) + i; j++) {
				//If reached upper limit
				if ((i + j) >= nrVertex) {
					add_edge(i, j - nrVertex, g);
				}
				else {
					add_edge(i, i + j, g);
				}
			}
		}

		//For lower vertices
		for (int i = nrVertex - 1; i >= 0; i--) {
			for (int j = nrVertex - 1; j >= i - (degree / 2); j--) {
				//If reached lower limit
				/*
				if ((i + j) >= nrVertex) {
					add_edge(i, j - nrVertex, g);
				}
				else {
					add_edge(i, i + j, g);
				}*/
			}
		}
		


		// Swap edges with give probability
		// TODO


		return g;
	}
	template <class Graph>
	void print_graph_in_adjacency_list_format(const Graph& g) {
		const auto V = boost::num_vertices(g);
		const auto max_num_digits = digit_count(V - 1);

		const auto index = boost::get(boost::vertex_index, g);

		BGL_FORALL_VERTICES_T(u, g, Graph) {
			std::string pad0 = pad(max_num_digits, index[u]);
			std::cout << pad0 << index[u] << " | ";

			BGL_FORALL_ADJ_T(u, v, g, Graph) {
				std::string pad1 = pad(max_num_digits, index[v]);
				std::cout << pad1 << index[v] << " -> ";
			}
			std::cout << "." << std::endl;
		}
	}

	template <class T>
	size_t digit_count(T number) {
		size_t digits = 0;

		if (number <= 0) {
			digits = 1;
		}
		while (number) {
			number /= 10;
			digits++;
		}
		return digits;
	}

	std::string pad(size_t max, size_t n) {
		return std::string(max - digit_count(n), ' ');
	}
}
int main() {
	using namespace boost;
	using namespace project_1;

	// create a typedef for the Graph type
	typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;

	//print_graph_in_adjacency_list_format(getRandomModel(5, 50.0));
	getSmallWorldModel(5, 3, 50.0);

	int i;
	std::cin >> i;
	return 0;
}