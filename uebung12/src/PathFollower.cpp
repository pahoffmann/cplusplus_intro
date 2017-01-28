/*
 * AutoPlayer.cpp
 *
 *  Created on: Jan 8, 2016
 *      Author: twiemann
 */

#include "PathFollower.hpp"

#include <iostream>
#include <math.h>
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
	Vector2f u;
	Vector2f v;
	Vector2f norm_vec;
	float square;
	//iterators
	std::list<Vector2f>::iterator it = m_path.begin();
	std::list<Vector2f>::iterator it1 = m_path.begin();
	it1++;
	//Stützvektor
	m_physicalProps.setPosition(*it);

	for(int i = 0; i < m_path.size()-1;i++){
		u = *it;
		v = *(it1);

		//normvec
		norm_vec = v+(u*(-1));
		square = sqrt(pow(norm_vec.x(),2)+pow(norm_vec.y(),2));
		norm_vec.setX(norm_vec.x()/square);
		norm_vec.setY(norm_vec.y()/square);
		
		//aiming add next vertex, if distance < 3 -> set position on vertex position
		while(true){
			nextFrame();
			//std::cout << "Position: " << m_physicalProps.position() << std::endl;
			m_physicalProps.position()+=norm_vec;
			if(m_physicalProps.position().distanceTo(v)<3){  /* dist < 3 ? */
				m_physicalProps.position() = v;
				break;
			}
			//sleep
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

		}
		it++;     /*incrementing iterators */
		it1++;

	}
}


PathFollower::~PathFollower()
{
	// TODO Auto-generated destructor stub
}

} /* namespace jumper */
