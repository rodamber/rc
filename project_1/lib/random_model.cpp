#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>

namespace project_1 {
	using namespace boost;

	mt19937 randomGen(static_cast<unsigned int>(std::time(0)));
	random::uniform_real_distribution<double> getRandomBetweenZeroAndOne(0, 1);



	template <class Graph>
	  bool is_directed() {
	    using Cat = typename graph_traits<Graph>::directed_category;
	    return boost::detail::is_directed(Cat());
	  }


	template <class Graph>
	Graph getRandomModel(int nrVertex, double probability) {
		if (probability > 1 || probability < 0) {
			throw "Probability must be between 0 and 1";
		}

		// declare a graph object
		Graph g(nrVertex);

		double randomNr;
		if (project_1::is_directed<Graph>()) {
			// If Graph directed repeat operation for all nodes
			for (int i = 0; i < nrVertex; i++) {
				for (int j = 0; j < nrVertex; j++) {
					randomNr = (getRandomBetweenZeroAndOne(randomGen));
					if (randomNr < probability && (i != j))
						add_edge(i, j, g);
				}
			}
		}
		else {
			// If Graph undirected, randomize only for forward nodes
			for (int i = 0; i < nrVertex - 1; i++) {
				for (int j = i + 1; j < nrVertex; j++) {
					randomNr = (getRandomBetweenZeroAndOne(randomGen));
					if (randomNr < probability)
						add_edge(i, j, g);
				}
			}
		}
		return g;
	}


}

int main() {
	using namespace boost;
	using namespace project_1;

	// create a typedef for the Graph type
	typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;

	//print_graph_in_adjacency_list_format(getRandomModel(5, 50.0));
	int nrVertex = 6;
	double probability = 0.7;
	getRandomModel<Graph>(nrVertex, probability);

	int i;
	std::cin >> i;
	return 0;
}
