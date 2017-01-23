/*
 * Path.hpp
 *
 *  Created on: Jan 8, 2016
 *      Author: twiemann
 */

#ifndef SRC_PATH_HPP_
#define SRC_PATH_HPP_

#include "StaticRenderable.hpp"

#include <list>
using std::list;

namespace jumper
{

/***
 *	A class that renders a path
 */
class Path: public StaticRenderable
{
public:

	/// Creates a path renderer object for the given vertices in \ref path
	Path(SDL_Renderer* renderer, std::list<Vector2f> path);

	/// Renders the path
	virtual void render();

	/// Destructor
	virtual ~Path();
private:

	// A list of 2D path nodes
	std::list<Vector2f> m_path;
};

} /* namespace jumper */

#endif /* SRC_PATH_HPP_ */
