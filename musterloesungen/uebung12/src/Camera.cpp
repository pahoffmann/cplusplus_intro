/*
 * Camera.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#include "Camera.hpp"

namespace jumper
{



int Camera::w() const
{
	return m_width;
}

int Camera::h() const
{
	return m_height;
}

int Camera::x() const
{
	return m_position.x();
}

int Camera::y() const
{
	return m_position.y();
}

SDL_Rect Camera::getRect() const
{
	SDL_Rect r;
	r.x = m_position.x() - m_width / 2;
	r.y = m_position.y() - m_height / 2;
	r.w = m_width;
	r.h = m_height;

	return r;
}

void Camera::move(const Vector2i& p)
{
	m_position += p;
}

Camera::Camera(const Vector2i& Vector2i, int w, int h)
	: m_position(Vector2i), m_width(w), m_height(h)
{
}

Vector2i& Camera::position()
{
	return m_position;
}

Camera::~Camera()
{
	// Nothing to do yet
}

} /* namespace jumper */
