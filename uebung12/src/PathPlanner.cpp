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
	float x,y;
};

template<class Graph, class Cost, class Location>
class Heuristic : public boost::astar_heuristic<Graph,Cost> {
	public:
		typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
		Heuristic(Location l, Vertex goal) : m_loc(l), m_goal(goal){
			//nothing here
		}

		Cost operator()(Vertex v){
			Cost dx = m_loc[m_goal].x - m_loc[v].x;
    		Cost dy = m_loc[m_goal].y - m_loc[v].y;
    		//std::cout << "Dist: " << sqrt(dx * dx + dy * dy) << std::endl; 
    		return sqrt(dx * dx + dy * dy);
		}
	private:
		Location m_loc;
		Vertex m_goal;
		

};

struct found {}; //except if the goal was found

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


    std::map<int,Vertex>:: iterator it = indices.begin();

    //it=it+(e-1);
    for(int i =0; i< e; i++) it++;

    end = (*it).second;//indices.find(e)->second;
    std::cout << "End-index-test: " << e << " == " << (*it).first<< std::endl;

    //vectors for predecassor map & distance map
    vector<Graph::vertex_descriptor> pre(num_vertices(g));
  	vector<float> dist(num_vertices(g));
  	std::cout << "Vertices: " << boost::num_vertices(g) << " Edges: " << boost::num_edges(g) << std::endl;

  	//try finding the goal with astar search
  	std::list<Vertex> path;
  	try {
    	// call astar
    	boost::astar_search(g, indices.find(s)->second, Heuristic<Graph, float, location*>(locs, end), //ASTAR with these parameters is bad.
                            boost::predecessor_map(&pre[0]).distance_map(&dist[0]).
       						visitor(astar_visitor<Vertex>(end)));
  
  
  	} catch(found f) {		 // found a path to the goal
    	
   	    for(Vertex v = end;pre[v] != v; v = pre[v]) {
      		path.push_front(v);
    	}
    	path.push_front(indices.find(s)->second);
    }

   	/* finding vertex in map and getting index of it
       pushing it into the list*/ 
    int value;
   
    for(Vertex v : path){
    	value = indices.find(v)->first;                       // BUG HERE
    	Vector2f vec(nodes[value].x(),nodes[value].y()); 
    	m_solutionPath.push_back(vec);
    }
    std::cout << "Shortest path from " << s << " to "
         << e << ": ";
    std::list<Vertex>::iterator it1 = path.begin();
    std::cout << s;
    for(++it1; it1 != path.end(); ++it1){
      	std::cout << " -> " << indices.find(*it1)->first;                                   //BUGGY HERE
  	}
  	std::cout << std::endl << "Total travel time: " << dist[end] << std::endl;
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
