#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include <vector>
#include <list>

#include "PathPlanner.hpp"

namespace jumper
{


struct location { 
public:
	int x,y;
};

template<class Graph, class CostType, class Location>
class Heuristic : public boost::astar_heuristic<Graph,CostType> {
	public:
		typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
		Heuristic(Location l, Vertex goal) : m_loc(l), m_goal(goal){
			//nothing here
		}

		CostType operator()(Vertex v){
			//return m_loc[m_goal].distanceTo(m_loc[v]);
			CostType dx = m_loc[m_goal].x - m_loc[v].x;
    		CostType dy = m_loc[m_goal].y - m_loc[v].y;
    		return sqrt(dx * dx + dy * dy);
		}
	private:
		Vertex m_goal;
		Location m_loc;

};

struct found {}; //except if the foal was found

// visitor
template <class Vertex>
class astar_visitor : public boost::default_astar_visitor
{
public:
  astar_visitor(Vertex goal) : m_goal(goal) {}
  template <class Graph>
  void examine_vertex(Vertex u, Graph& g) {
    if(u == m_goal)
      throw found();
  }
private:
  Vertex m_goal;
};




void PathPlanner::planPath(int s, int e)
{	

	location locs[nodes.size()];
	for(int i = 0; i<nodes.size() ; i++){
		locs[i].x = nodes[i].x();
		locs[i].y = nodes[i].y();
	}

    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
    Vertex end;
    end = indices.find(e)->second;

    //vectors for predecassor map & distance map
    vector<Graph::vertex_descriptor> pre(num_vertices(g));
  	vector<float> dist(num_vertices(g));
  	std::cout << "Vertices: " << boost::num_vertices(g) << " Edges: " << boost::num_edges(g) << std::endl;

  	//try finding the goal with astar search
  	try {
    	// call astar
    	boost::astar_search(g, s, Heuristic<Graph, float, location*>(locs, e),
                            boost::predecessor_map(&pre[0]).distance_map(&dist[0]).
       						visitor(astar_visitor<Vertex>(indices.find(e)->second)));
  
  
  	} catch(found f) { // found a path to the goal
    	std::list<Vertex> path;
   	    for(Vertex v = end;; v = pre[v]) {
      	path.push_front(v);
      	if(pre[v] == v)
        	break;
    }
    int value;
    // finding vertex in map and getting index of it
    // pushning it into the list
    for(Vertex v : path){
    	value = indices.find(v)->first;
    	Vector2f vec(nodes[value].x(),nodes[value].y());
    	m_solutionPath.push_back(vec);
    }
    std::cout << "Shortest path from " << s << " to "
         << e << ": ";
    std::list<Vertex>::iterator spi = path.begin();
    std::cout << s;
    for(++spi; spi != path.end(); ++spi)
      std::cout << " -> " << indices.find(*spi)->first;
    std::cout << std::endl << "Total travel time: " << dist[end] << std::endl;
    
  }
}



PathPlanner::PathPlanner (Network* net)
{	
	//getting network nodes & edges
	nodes = net->getNodes();
	edges = net->getEdges(); 


	boost::property_map<Graph,boost::edge_weight_t>::type weight_map = boost::get(boost::edge_weight, g);
 
	typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
	typedef boost::graph_traits<Graph>::edge_descriptor Edge;
	

	for(int i = 0; i < edges.size(); i++){
		int start = edges[i].first;
		int end = edges[i].second;
		Vertex v1;
		Vertex v2;
		Edge e;
		bool inserted;
		IndexVertexMap::iterator pos;
		boost::tie(pos,inserted) = indices.insert(std::make_pair(start, Vertex()));
		if(inserted){
			v1 = boost::add_vertex(g);
			pos->second = v1;
		} else{
			v1 = pos->second;
		}
		boost::tie(pos,inserted) = indices.insert(std::make_pair(end, Vertex()));
		if(inserted){
			v2 = boost::add_vertex(g);
			//index_map[v2] = end;
			pos->second = v2;
		} else{
			v2 = pos->second;
		}
		
		boost::tie(e, inserted) = boost::add_edge(v1,v2,g);
		if(inserted){
			weight_map[e] = nodes[start].distanceTo(nodes[end]);
		}

	}
	



}

const std::list<Vector2f>& PathPlanner::getSolution(){
    return m_solutionPath;
}


}
