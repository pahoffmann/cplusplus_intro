/*
 * Bot.hpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#ifndef SRC_BOT_HPP_
#define SRC_BOT_HPP_

#include "Actor.hpp"
#include "Collision.hpp"
#include "Level.hpp"


namespace jumper
{

/***
 * @brief	An actor that moves autonomously in a level. The default
 * 			behavior is the change direction (bounce) if the bot hits
 * 			a vertical tile in the level.
 */
class Bot : public Actor
{
public:

	/// Creates a bot for the given renderer from the given filename
	Bot(SDL_Renderer* renderer, std::string filename);

	/// Creates a bot from the given texture and animation information
	Bot(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);

	/// Destrcutor
	virtual ~Bot();

	/// Moves the bot in the level. Overwrite to change behavior.
	virtual void move(Level& level);

private:

	/// Changes the moving direction
	void bounce();

	/// Position where a collision with a vertical tile
	/// occurred.
	Vector2f m_bouncePos;
};

} /* namespace jumper */

#endif /* SRC_BOT_HPP_ */
