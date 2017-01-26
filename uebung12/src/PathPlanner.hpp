#ifndef PATH_H_
#define PATH_H_

#include <string>
#include <list>
#include <cassert>
#include <vector>
#include <map>

#include "Network.hpp"
#include "Vector.hpp"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphml.hpp>
#include <boost/graph/astar_search.hpp>

using namespace boost;

namespace jumper
{

/***
 * A class to plan shortest paths in a graph using the A* algorithm
 */
class PathPlanner
{
  public:

	/// Creates a path planner instance for the given graph
    PathPlanner(Network* net);

    /// Plans a path from \ref startIndex to \ref endIndex.
    /// The generated path can by extracted with \ref getSolution().
    void planPath(int startIndex, int endIndex);

    /// Returns the computed solution path
    const std::list<Vector2f>& getSolution();

  private:

    /// TODO: Add graph structure etc.
    std::list<Vector2f> m_solutionPath;
    typedef adjacency_list<vecS, vecS, undirectedS,/*property<vertex_index2_t, int>*/ boost::no_property, property<edge_weight_t, float>> Graph;
    Graph g;
    std::vector<Vector2i> nodes;
	std::vector<pair<unsigned int, unsigned int>> edges;
	
	typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
	typedef std::map<int, Vertex> IndexVertexMap;
	IndexVertexMap indices;
};

    
}

#endif
