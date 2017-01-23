/*
 * Path.cpp
 *
 *  Created on: Jan 8, 2016
 *      Author: twiemann
 */

#include "Path.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace jumper
{

Path::Path(SDL_Renderer* renderer, std::list<Vector2f> path)
	: StaticRenderable(renderer), m_path(path)
{

}

void Path::render()
{
	// Set color to yellow
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 0);

	bool first = true;
	Vector2f prev;

	// Render line segments
	for(const Vector2f v : m_path)
	{
		if(first == false)
		{
			int sx = prev.x();
			int sy = prev.y();
			int ex = v.x();
			int ey = v.y();

			shiftPosition(sx, sy);
			shiftPosition(ex, ey);

			SDL_RenderDrawLine(m_renderer, sx, sy, ex, ey);
		}
		else
		{
			first = false;
		}
		prev = v;
	}
}

Path::~Path()
{
	// TODO Auto-generated destructor stub
}

} /* namespace jumper */
