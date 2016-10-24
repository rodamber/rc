#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <iostream>
#include <ctime>
#include <iomanip>      
#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <boost/graph/adjacency_list.hpp>

namespace project_1 {
	using namespace boost;
	
	typedef adjacency_list<vecS, vecS, undirectedS> Graph;
	mt19937 randgen(static_cast<unsigned int>(std::time(0)));
	random::uniform_real_distribution<float> noise(0, 100);

	Graph getRandomModel(int nrVertex, float probability) {
		if (probability >= 100) {
			throw "Probability must be equal or lower than 100!";
		}

		// declare a graph object
		Graph g(nrVertex);

		// Generate edge array with given probability
		// Also add them to the graph
		typedef std::pair<int, int> Edge;
		std::vector<Edge> edge_array;

		for (int i = 0; i < nrVertex; i++) {
			for (int j = 0; j < nrVertex; j++) {
				float testNr = (floorf(noise(randgen) * 10) / 10);
				
				// boost::edge(u,v,g) returns pair<edge_descriptor, bool> 
				// where the bool is whether the edge exists
				if (testNr < probability) {
					if ((i != j) && !(boost::edge(j, i, g).second));
					add_edge(i, j, g);
				}
			}
		}
		return g;
	}
}