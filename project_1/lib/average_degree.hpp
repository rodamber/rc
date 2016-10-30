#pragma once

#include <boost/graph/adjacency_list.hpp>
#include "all_vertex_degree.hpp"


template<class Graph>
float average_degree(Graph& g)
{
  float aux1,aux2;
  std::vector<unsigned> dl = all_vertex_degree(g);
  aux1 = (float) accumulate(dl.begin(), dl.end(), 0);
  aux2 = (float) dl.size();

  return aux1/aux2;
}

