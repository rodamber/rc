#include <util.hpp>

namespace project_1 {
	using namespace boost;

	template <class Graph>
	Graph random_model(int nrVertex, double probability) {
		// declare a graph object
		Graph g(nrVertex);
	    const auto V = num_vertices(g);

	    vertex_iterator<Graph> v_it, v_end;
	    vertex_descriptor<Graph> u, v;

	    for(tie(v_it, v_end) = vertices(g); v_it != v_end; ++v_it) {
  		    for ( vertex_iterator<Graph> v_middle = v_it + 1;
  		    							 v_middle != v_end;
  		    							 ++v_middle){

  		    	
  		    	if(util::random::random_bool(probability)){
  		    		add_edge(*v_it, *v_middle, g);
  		    	}
	        }
	    }
		return g;
	}
}
