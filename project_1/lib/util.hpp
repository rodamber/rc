#pragma once

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/properties.hpp>

#include <iomanip>
#include <iostream>

#include <random>


namespace project_1 { namespace util {

  using namespace boost;

  namespace graph {
    template<class Graph>
    using vertex_descriptor = typename graph_traits<Graph>::vertex_descriptor;

    template<class Graph>
    using edge_descriptor = typename graph_traits<Graph>::edge_descriptor;

    template<class Graph>
    using adjacency_iterator = typename graph_traits<Graph>::adjacency_iterator;

    template<class Graph>
    using vertex_iterator = typename graph_traits<Graph>::vertex_iterator;

    template<class Graph>
    using edge_iterator = typename graph_traits<Graph>::edge_iterator;

    template<class Graph>
    using vertex_size = typename graph_traits<Graph>::vertex_size_type;

    template<class Graph>
    inline bool directed() {
      using Cat = typename graph_traits<Graph>::directed_category;
      return boost::detail::is_directed(Cat());
    }

    template<class Graph>
    inline bool undirected() {
      return !directed<Graph>();
    }

  };

  namespace random {

    std::random_device r;
    std::default_random_engine random_engine(r());

    bool random_bool(double probability) {
      return std::bernoulli_distribution(probability)(random_engine);
    }

  };

  namespace print {

    template <class T>
    size_t digit_count(T number) {
      size_t digits = 0;

      if (number <= 0) {
        digits = 1;
      }
      while (number) {
        number /= 10;
        digits++;
      }
      return digits;
    }

    std::string pad(size_t max, size_t n) {
      return std::string(max - digit_count(n), ' ');
    }

    template <class Graph>
    void print_graph_in_adjacency_list_format(const Graph& g) {
      const auto V = num_vertices(g);
      const auto max_num_digits = digit_count(V - 1);

      const auto index = get(vertex_index, g);

      BGL_FORALL_VERTICES_T(u, g, Graph) {
        std::string pad0 = pad(max_num_digits, index[u]);
        std::cout << pad0 << index[u] << " | ";

        BGL_FORALL_ADJ_T(u, v, g, Graph) {
          std::string pad1 = pad(max_num_digits, index[v]);
          std::cout << pad1 << index[v] << " -> ";
        }
        std::cout << "." << std::endl;
      }
    }

    template<class T, class X>
    void to_csv(const std::vector<T> &xs, const std::vector<X> &ys, std::ostream &os) {
      if (xs.size() != ys.size()) {
        throw std::runtime_error("xs must have the same size as ys");
      }
      for (size_t i = 0; i < xs.size(); ++i) {
        os << std::setprecision(2) << xs[i] << "\t" << ys[i] << "\n";
      }
    }

    template<class X, class Y>
    void to_csv(const std::vector<std::pair<X,Y>>& points, std::ostream& os) {
      for (const auto& point : points) {
        os << std::setprecision(10) << point.first << "\t" << point.second << "\n";
      }
    }


  }; // namespace print


}; }; // namespace project_1::util
