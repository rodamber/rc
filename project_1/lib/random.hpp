#include <util.hpp>

namespace project_1 {
  using namespace boost;

  template <class Graph>
  Graph random_model(int num_vertices, double probability) {
    Graph g(num_vertices);

    vertex_iterator<Graph> v_it, v_end;
    for(tie(v_it, v_end) = vertices(g); v_it != v_end; ++v_it) {
      for (auto v_middle = v_it + 1; v_middle != v_end; ++v_middle){
        if(util::random::random_bool(probability)){
          add_edge(*v_it, *v_middle, g);
        }
      }
    }

    return g;
  }
}
