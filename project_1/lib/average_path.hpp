#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <boost/graph/breadth_first_search.hpp>
#include <util.hpp>

namespace project_1 {
	using namespace boost;

	//	Average Path Algorithm
	//
	//	This algorithm finds the average over all shortest paths between all
	// pairs of vertex in a graph
	//
	//  The shortest paths of a node is found using a BFS
	template <class Graph>
	double average_path(const Graph& g) {
		//Typedefs
		vertex_descriptor<Graph> u;
		typedef typename graph_traits<Graph>::vertex_iterator vi;
		typedef typename property_map<Graph, vertex_index_t>::type IndexMap;
		typedef typename graph_traits<Graph>::vertices_size_type vertexSize;

		// vector for storing distance property
		std::vector<int> distances(num_vertices(g));

		double totalSum = 0;

		IndexMap id = get(vertex_index, g);
		std::pair<vi, vi> vp;

		//Iterate through vertices
		for (vp = vertices(g); vp.first != vp.second; ++vp.first) {
			u = *vp.first;

			vertexSize *d;
			d = new vertexSize[num_vertices(g)];

			std::fill_n(d, num_vertices(g), 0);

			//BFS
			breadth_first_search(g, *vp.first, visitor(
				boost::make_bfs_visitor(boost::record_distances(d, boost::on_tree_edge()))));

			std::copy(d, d + num_vertices(g), distances.begin());

			double vertexSum = 0;
			//Sum all distance values
			for (std::vector<int>::iterator it = distances.begin(); it != distances.end(); ++it)
				vertexSum += *it;
			totalSum += vertexSum;

			std::cout << "Sum of shortest paths of vertex: " << id[u] << " is -> " << vertexSum << std::endl;

			free(d);
		}

		double avgPathLength = totalSum / (double)(num_vertices(g) * (num_vertices(g) - 1));
		std::cout << "Average Path Length: " << avgPathLength << std::endl;

		return avgPathLength;
	}
};