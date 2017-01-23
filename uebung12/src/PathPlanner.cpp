#include <iostream>
#include <map>
#include <math.h>
#include <string>

#include "PathPlanner.hpp"

namespace jumper
{



void PathPlanner::planPath(int s, int e)
{
    // TODO: Plan a path from s to e and add
    // path vertices to the list returned by
    // getSolution().
}


PathPlanner::PathPlanner (Network* net)
{
	// Get vertices and edges from network and build
    // a search graph for the A* search.
	  
}

const std::list<Vector2f>& PathPlanner::getSolution(){
    return m_solutionPath;
}


}
