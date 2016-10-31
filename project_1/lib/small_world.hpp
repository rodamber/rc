#include <boost/graph/random.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <util.hpp>

namespace project_1 {
  using namespace boost;

  template<class Graph>
  Graph even_degree_regular_graph(Graph& g, int degree) {
    const auto V = num_vertices(g);
    const auto index = get(vertex_index, g);

    vertex_iterator<Graph> v_it, v_end;
    for (tie(v_it, v_end) = vertices(g); v_it != v_end; ++v_it) {
      size_t j = (index[*v_it] + 1) % V;

      for (int i = 0; i != degree / 2; i++){
        add_edge(*v_it, vertex(j, g), g);
        j = (j + 1) % V;
      }
    }

    return g;
  }

  template<class Graph>
  Graph odd_degree_regular_graph(Graph& g, int degree) {
    const auto V = num_vertices(g);

    vertex_iterator<Graph> v_it, v_end;
    tie(v_it, v_end) = vertices(g);

    // Connect each vertex to the opposite one.
    for(size_t x = 0; x < V / 2; ++v_it, ++x) {
      add_edge(*v_it, *(v_it + V / 2), g);
    }

    // Then do the same as for an even degree regular graph of degree k - 1.
    return even_degree_regular_graph(g, degree - 1);
  }

  template<class Graph>
  Graph regular_graph(size_t num_vertices, size_t degree) {
    Graph g(num_vertices);

    if (degree % 2 == 0) {
      return even_degree_regular_graph<Graph>(g, degree);
    } else {
      return odd_degree_regular_graph<Graph>(g, degree);
    }
  }

  // Randomly rewires graph edges with the given probability.
  template<class Graph>
  void rewire(Graph& g, double probability) {
    if (undirected<Graph>()) {
      probability /= 2;
    }

    BGL_FORALL_VERTICES_T(u, g, Graph) {
      BGL_FORALL_ADJ_T(u, v, g, Graph) {
        if (util::random::random_bool(probability)) {
          vertex_descriptor<Graph> w = u;

          // Pick a random vertex w until we find one such that:
          //   - is not the same as the one to which we want to connect to, v;
          //   - doesn't exist an edge between v and w;
          //   - is not the same one we had before, u;
          while (v == w || edge(u, w, g).second || u == w) {
            w = random_vertex<Graph>(g, util::random::random_engine);
          }
          remove_edge(u, v, g);
          add_edge(u, w, g);
        }
      }
    }
  }

  // Generates a graph with small-world properties using the Watz and Strogatz
  // algorithm.
  //
  // Preconditions:
  //   - 0 < probability < 1
  //   - nrVertex or degree must be even
  template <class Graph>
  Graph watz_strogatz_small_word(int nrVertex, int degree, double probability) {
    Graph g = regular_graph<Graph>(nrVertex, degree);
    rewire<Graph>(g, probability);
    return g;
  }

}; // namespace project_1
