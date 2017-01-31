/*
 * Camera.hpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Vector.hpp"

#include <SDL.h>

namespace jumper
{

/***
 * A camera object to scroll within a level
 */
class Camera
{
public:

	/// Constructs a camera at (0,0)
	Camera() : Camera(Vector2i(0,0), 0, 0) {}

	/// Constructs a camera at the given position (x,y) with given field of view (w,h)
	Camera(int x, int y, int w, int h) : Camera(Vector2i(x,y), w, h) {}

	/// Constructs a camera at (0,0) with given field of view (w,h)
	Camera(int w, int h) : Camera(Vector2i(0, 0), w, h) {}

	/***
	 * Constructs a camera with the given \ref pixel offset and
	 * width \ref w and height \h
	 */
	Camera(const Vector2i& pixel, int w, int h);

	/***
	 * Moves the camera according to the given offset
	 * @param offset	A pixel offset for camera movement
	 */
	void move(const Vector2i& offset);

	/// Returns the current x-position
	int x() const;

	/// Returns the current y-position
	int y() const;

	/// Returns the current position
	Vector2i& position();

	/// Destructor
	virtual ~Camera();

	/// Returns the width of the current view
	int w() const;

	/// Returns the height of the current view
	int h() const;

	/// Returns a SDL_Rect representation of the current view
	SDL_Rect getRect() const;

private:

	/// Current camera position
	Vector2i	m_position;

	/// Width of view
	int			m_width;

	/// Height of view
	int 		m_height;


};

} /* namespace jumper */

#endif /* CAMERA_HPP_ */
