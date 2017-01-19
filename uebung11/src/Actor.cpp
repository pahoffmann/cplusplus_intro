/*
 * Actor.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#include <SDL.h>
#include "Actor.hpp"
#include <thread>
#include <functional>

namespace jumper
{

Actor::Actor(SDL_Renderer* renderer, std::string filename)
	: AnimatedRenderable(renderer, filename)
{
	m_jumping = 0;
	m_wantsToJump = false;
	m_onGround = false;
	m_focus = false;
	m_jumpStart = 0;
	m_physicalProps.setPosition(Vector2f(100, 0));
	m_startTicks = 0;
}

Actor::Actor(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
	: AnimatedRenderable(renderer, texture, frameWidth, frameHeight, numFrames)
{
	m_jumping = 0;
	m_wantsToJump = false;
	m_onGround = false;
	m_focus = false;
	m_jumpStart = 0;
	m_physicalProps.setPosition(Vector2f(100, 0));
	m_startTicks = 0;
}

void Actor::setPhysics(PlayerProperty p)
{
	m_physicalProps = p;
}

Actor::~Actor()
{

}

void Actor::wantsToJump(bool j)
{
	m_wantsToJump = j;
}

float Actor::getElapsedTime()
{
	if(m_startTicks == 0)
	{
		m_startTicks = SDL_GetTicks();
	}

	Uint32 ticks = SDL_GetTicks();
	float time =  (ticks - m_startTicks) / 1000.0;
	m_startTicks = ticks;
	return time;
}

void Actor::render()
{
    SDL_Rect target;

    target.x = floor(m_physicalProps.position().x());
    target.y = floor(m_physicalProps.position().y());
    target.w = m_frameWidth;
    target.h = m_frameHeight;

    // Do not render if actor is outside frustrum
    //if(target.x + target.h > 0 && target.x + target.h < m_camera.w())
    {
    	SDL_RendererFlip flip;
    	if(m_physicalProps.velocity().x() > 0)
    	{
    		flip = SDL_FLIP_HORIZONTAL;
    	}
    	else
    	{
    		flip = SDL_FLIP_NONE;
    	}

    	shiftTargetRect(target);

    	// Render current animation frame
    	SDL_RenderCopyEx( getRenderer(), m_texture, &m_sourceRect, &target, 0, NULL, flip);
    }

}

void Actor::start(Level& l){
	auto var = std::ref(l);
	std::thread thread2(&jumper::Actor::move, this , var);
	m_thread.swap(thread2);

	m_thread.join();

}

void Actor::setPosition(Vector2f pos)
{
    m_physicalProps.position() = pos;
}

bool Actor::onGround() const
{
    return m_onGround;
}

void Actor::setOnGround(bool onGround)
{
    m_onGround = onGround;
}

PlayerProperty& Actor::physics()
{
    return m_physicalProps;
}

bool Actor::jumping()
{
    return m_jumping;
}

void Actor::setJumping(bool jump)
{
    if(jump) m_jumpStart = m_physicalProps.position().y();
    m_jumping = jump;
}

int Actor::jumpStart()
{
    return m_jumpStart;
}

Vector2f Actor:: position()
{
	return m_physicalProps.position();
}

void Actor::getCollision(Actor& other)
{

}

void jumper::Actor::setFocus(bool focus)
{
	m_focus = focus;
}

bool jumper::Actor::hasFocus()
{
	return m_focus;
}


} /* namespace jumper */

