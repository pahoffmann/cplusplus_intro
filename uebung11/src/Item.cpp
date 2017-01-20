/*
 * Item.cpp
 *
 *  Created on: Jan 1, 2016
 *      Author: twiemann
 */

#include "Item.hpp"

namespace jumper
{

Item::Item(SDL_Renderer* renderer, std::string filename)
	: Actor(renderer, filename)
{

}

Item::Item(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth,
		int frameHeight, int numFrames)
	: Actor(renderer, texture, frameWidth, frameHeight, numFrames)
{
}

void Item::move(Level& level)
{
	while(true){
		nextFrame();
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}
	
}

Item::~Item()
{
	// TODO Auto-generated destructor stub
}

} // namespace jumper
