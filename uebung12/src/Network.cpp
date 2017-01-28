/*
 * Network.cpp
 *
 *  Created on: Jan 8, 2016
 *      Author: twiemann
 */

#include "Network.hpp"

#include <fstream>
#include <iostream>
using std::ifstream;
using std::cout;
using std::endl;

namespace jumper
{

Network::Network(SDL_Renderer* renderer, string graphFile)
	: StaticRenderable(renderer)
{
	m_start = 0;
	m_goal = 0;
	parseGraphFile(graphFile);
}

void Network::render()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	for(const pair<unsigned int, unsigned int>& p: m_edges)
	{
		unsigned int start = p.first;
		unsigned int end = p.second;
		if(start < m_nodes.size() && end < m_nodes.size())
		{
			// Get tile indices and map to global coordinates
			Vector2i s_node = m_nodes[start];
			Vector2i e_node = m_nodes[end];

			int sx = s_node.x();
			int sy = s_node.y();

			int ex = e_node.x();
			int ey = e_node.y();

			shiftPosition(sx, sy);
			shiftPosition(ex, ey);

			SDL_RenderDrawLine(m_renderer, sx, sy, ex, ey);

		}
	}

	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 0);
	for(const Vector2i &i : m_nodes )
	{
		SDL_Rect rect;

		// Positions are in tile-coordinates!!!
		rect.x = i.x() - 4;
		rect.y = i.y() - 4;
		rect.w = 8;
		rect.h = 8;

		shiftTargetRect(rect);

		SDL_RenderDrawRect(m_renderer, &rect);
	}

}

Network::~Network()
{
	// TODO Auto-generated destructor stub
}

void Network::parseGraphFile(string file)
{
	cout << "Parsing graph file " << file << endl;
	ifstream in(file.c_str());

	int num_nodes, x, y;

	// Parse file if existing
	if(in.good())
	{
		in >> num_nodes;

		// Read node definitions
		for(int i = 0; i < num_nodes; i++ )
		{
			in >> x >> y;
			//std::cout << "Node coords: " <<i << ": "<< x << " " << y << std::endl;
			m_nodes.push_back(Vector2i(x,y));
		}

		// Read edge definitions
		while(in.good())
		{
			in >> x >> y;
			//std::cout << "Edge: " << x << " "<< y << std::endl;


			// Check if stream is still valid after last
			// read attempt
			if(in.good())
			{
				pair<unsigned int, unsigned int> e((unsigned int)x,(unsigned int)y);
				m_edges.push_back(e);
			}
		}
	}
	cout << "Graph contains " << m_nodes.size() << " nodes and " << m_edges.size() << " edges." << endl;
}

} /* namespace jumper */
