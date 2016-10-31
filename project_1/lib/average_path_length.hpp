#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/iteration_macros.hpp>

#include <util.hpp>

namespace project_1 {
  using namespace boost;
  using namespace util::graph;

  //  Average Shortest Path Algorithm
  //
  // This algorithm finds the average over all shortest paths between all pairs
  // of a vertex in a graph
  template <class Graph>
  double average_path_length(const Graph& g) {
    const double V = num_vertices(g);
    double total_sum = 0.0;

    BGL_FORALL_VERTICES_T(v, g, Graph) {
      vertex_size<Graph> *d = new vertex_size<Graph>[V];
      std::fill_n(d, V, 0);

      auto visitor = boost::make_bfs_visitor(boost::record_distances(d, boost::on_tree_edge()));
      breadth_first_search(g, v, visitor(visitor));

      const double distance_sum = std::accumulate(d.begin(), d.end(), 0.0);
      delete d;

      total_sum += distance_sum;
    }

    return total_sum / (double)(V * (V - 1));
  }
};
