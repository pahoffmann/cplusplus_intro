/*
 * AutoPlayer.cpp
 *
 *  Created on: Jan 8, 2016
 *      Author: twiemann
 */

#include "PathFollower.hpp"

#include <iostream>
using std::cout;
using std::endl;
namespace jumper
{

PathFollower::PathFollower(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames)
	: Actor(renderer, texture, frameWidth, frameHeight, numFrames)
{

}

void PathFollower::render()
{
	SDL_Rect target;

	target.x = floor(m_physicalProps.position().x()) - m_sourceRect.w / 2;
	target.y = floor(m_physicalProps.position().y()) - m_sourceRect.h / 2;
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

void PathFollower::move(Level& l)
{
	// TODO: Implement move logic
}


PathFollower::~PathFollower()
{
	// TODO Auto-generated destructor stub
}

} /* namespace jumper */
