#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>

template <class Vertex,class Graph>
float closeness_centrality(const Vertex& v, const Graph& g) {
  typename boost::property_map<Graph, boost::vertex_index_t>::type index = get(boost::vertex_index, g);
  typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
  typename boost::graph_traits<Graph>::vertices_size_type *d;

  std::vector<int> distances(num_vertices(g));
  int vertex_dist = 0;

  d = new typename boost::graph_traits<Graph>::vertices_size_type[num_vertices(g)];
  std::fill_n(d, num_vertices(g), 0);

  breadth_first_search(g, v, boost::visitor(boost::make_bfs_visitor(
                                            boost::record_distances(d, boost::on_tree_edge()))));

  std::copy(d, d + num_vertices(g), distances.begin());

  free(d);

  for(int n : distances){
	vertex_dist += n;
  }
  return (float)(num_vertices(g) - 1) / (float)vertex_dist;
}
