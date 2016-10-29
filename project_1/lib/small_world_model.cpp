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
#include <boost/random/uniform_int_distribution.hpp>
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

	// Check if graph is directed or not
	template <class Graph>
	bool isDirected() {
		using Cat = typename graph_traits<Graph>::directed_category;
		return boost::detail::is_directed(Cat());
	}

	mt19937 randgen2(static_cast<unsigned int>(std::time(0)));
	random::uniform_real_distribution<double> getRandomBetweenZeroAndOne(0, 1);

	template <class Graph>
	Graph generateEvenRegularGraph(int nrVertex, int degree){

		Graph g(nrVertex);
		for(int i=0; i < nrVertex ; i++){
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
		return g;
	}

	template <class Graph>
	Graph generateOddRegularGraph(int nrVertex, int degree, double probability){
		if(!isDirected<Graph>() && degree == 1){
			throw "Impossible to have undirected 1-degree regular graph";
		}
		Graph g(nrVertex);

		//First connect all vertices
		for(int i = 0; i < nrVertex; i++) {
			if(i == nrVertex - 1)
				add_edge(i, 0, g);
			else
				add_edge(i, i+1, g);
		}

		//Then connect opposite vertex
		for(int i = 0; i < (nrVertex/2); i++) {
			add_edge(i, i+(nrVertex/2), g);
		}

		// Then if degree > 3, and having a (x*2)+3 degree
		// for each x, add and edge to each node with x+1 distance to forward node
		int x = ((degree - 3) / 2);
		for(int xIterator = 1; xIterator < x; xIterator ++) {
			for(int i = 0; i< nrVertex; i++) {
				if((i + xIterator + 1) >= nrVertex) {
					add_edge(i, (i + xIterator + 1) - nrVertex, g);
				}
				add_edge(i, i+xIterator+1, g);
			}
		}
		return g;
	}

	template <class Graph>
	Graph getSmallWorldModel(int nrVertex, int degree, double probability) {
		if (probability > 1 || probability < 0) {
			throw "Probability must be between 0 and 1";
		}

		// declare a graph object
		Graph g(nrVertex);

		//First generate a k-degree regular graph
		if(degree % 2 == 0) {
			g = generateEvenRegularGraph<Graph>(nrVertex, degree);
		}
		else {
			if(nrVertex%2 == 0){
				g = generateOddRegularGraph<Graph>(nrVertex, degree, isDirected<Graph>());
			}
			else {
				throw "Impossibru!";
			}
		}

		random::uniform_int_distribution<int> getRandomBetweenZeroAndVertexNr(0, nrVertex-1);
		typename graph_traits<Graph>::adjacency_iterator edge_i;
		typename graph_traits<Graph>::adjacency_iterator edge_end;
		if (isDirected<Graph>()) {
			//If graph is directed, go through out-vertices
			for(int i = 0; i< nrVertex; i++){
				for (boost::tie(edge_i, edge_end) = out_edges(i, g);
						edge_i != edge_end; ++edge_i) {
					//index[*ai] representa o número do edge
					int endVertexNr = index[*edge_i];
					int randomNr = getRandomBetweenZeroAndOne(randomGen);
					if(randomNr < probability){
						//Ok time to swap some edges
						int chosenVertice = getRandomBetweenZeroAndVertexNr(randomGen);
						if(chosenVertice != endVertexNr && !(boost::edge(i, chosenVertice,g).second)){
							// If Random selected vertex is not the same end vertice that we started from
							// and the edge(i, chosenVertice) doesn't exist ->Swap it!!
							remove_edge(i, endVertexNr, g);
							add_edge(i, chosenVertice, g);
						}
					}
				}
			}
		} else {
			//If not go through adjacent vertices
			// Swap edges with given probability
			for(int i = 0; i< nrVertex; i++){
				 for (boost::tie(edge_i, edge_end) = adjacent_vertices(i, g);
						 edge_i != edge_end; ++edge_i) {
					 //index[*ai] representa o número do edge
					 int endVertexNr = index[*edge_i];
					 int randomNr = getRandomBetweenZeroAndOne(randomGen);
					 if(randomNr < probability){
						 //Ok time to swap some edges
						 int chosenVertice = getRandomBetweenZeroAndVertexNr(randomGen);
						 if(chosenVertice != endVertexNr && !(boost::edge(i, chosenVertice,g).second)){
							 // If Random selected vertex is not the same end vertice that we started from
							 // and the edge(i, chosenVertice) doesn't exist ->Swap it!!
							 remove_edge(i, endVertexNr, g);
							 add_edge(i, chosenVertice, g);
						 }
					 }

				 }
			}
		}
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
	getSmallWorldModel<Graph>(5, 3, 50.0);

	int i;
	std::cin >> i;
	return 0;
}
