/*
 * Item.hpp
 *
 *  Created on: Jan 1, 2016
 *      Author: twiemann
 */

#ifndef SRC_ITEM_HPP_
#define SRC_ITEM_HPP_

#include "Actor.hpp"

namespace jumper
{

/***
 * An Item is a special actor that stays at it's given
 * position and performs an animation. In constrast to
 * an AnimatedRenderable it can perform collision tests.
 */
class Item: public jumper::Actor
{
public:

	/// Creates an item for the renderer from the given filename
	Item(SDL_Renderer* renderer, std::string filename);

	/// Creates an item for the given renderes using a loaded texture and
	/// frame information
	Item(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);

	/// Moves the item in the level
	virtual void move(Level& level);

	/// Destructor
	virtual ~Item();
};

} // namespace jumper
#endif /* SRC_ITEM_HPP_ */
