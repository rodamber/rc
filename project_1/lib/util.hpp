#pragma once

#include <boost/graph/graph_traits.hpp>

namespace project_1 {

  using namespace boost;

  template <class Graph>
  using vertex_descriptor = typename graph_traits<Graph>::vertex_descriptor;

  template <class Graph>
  inline bool undirected() {
    using Cat = typename graph_traits<Graph>::directed_category;
    return !boost::detail::is_directed(Cat());
  }

}; // namespace project_1
