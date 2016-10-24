#pragma once

#include <boost/graph/adjacency_list.hpp>

template <class Graph>
std::vector<unsigned> all_vertex_degree(const Graph& g)
{
  typename boost::graph_traits<Graph>::adjacency_iterator ai, ai_end;
  typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;

  std::vector<unsigned> degree_list;
  unsigned degree = 0;

  for(boost::tie(vi, vi_end) = vertices(g); vi != vi_end; vi++){
    for(boost::tie(ai, ai_end) = adjacent_vertices(*vi, g);ai != ai_end; ai++)
      degree++;
    degree_list.push_back(degree);
    degree = 0;
  }
  return degree_list;
}
