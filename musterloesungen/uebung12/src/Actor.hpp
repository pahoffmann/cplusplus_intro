/*
 * Actor.hpp
 *
 *  Created on: Dec 9, 2015
 *      Author: twiemann
 */

#ifndef SRC_ACTOR_HPP_
#define SRC_ACTOR_HPP_

#include "AnimatedRenderable.hpp"
#include "PlayerProperty.hpp"
#include "WorldProperty.hpp"
#include "Level.hpp"

#include <string>
#include <thread>
#include <chrono>

namespace jumper
{

/***
 * @brief 	A class to represent an object, that moves in a level
 * 			and interacts (collides) with other objects
 */
class Actor : public AnimatedRenderable
{
public:

	/// Creates an actor for the given renderer from the given filename
	Actor(SDL_Renderer* renderer, std::string filename);

	/// Creates an actor from a texture and animation information
	Actor(SDL_Renderer* renderer, SDL_Texture* texture, int frameWidth, int frameHeight, int numFrames);

	/// Destructor
	virtual ~Actor();

	/// Moves the actor in the given level
	virtual void move(Level& level) = 0;

	/// Returns a collision object between two actors
	virtual void getCollision(Actor& other);

	/// Renders the actors
	virtual void render();

	void setPhysics(PlayerProperty p);
	/**
	 * Sets the player's position
	 */
	void setPosition(Vector2f pos);

	/***
	 * Returns the player's current position
	 */
	Vector2f position();

	/**
	 * Returns the player's physical properties
	 */
	PlayerProperty &physics();

	/**
	 * True, if the player touches ground
	 */
	bool onGround() const;

	/**
	 * Sets the on ground flag to the given status
	 */
	void setOnGround(bool m_onGround);

	/**
	 * Sets the jump state
	 */
	void setJumping(bool jump);

	/**
	 * Returns the jump state
	 */
	bool jumping();

	/**
	 * Retruns the pixel position at which jumping was started
	 */
	int jumpStart();

	/// True, if a jump command was given
	void wantsToJump(bool j);

	/// Starts moving
	void start(Level& level);

	/// Set to true, if the camera should follow the actor
	void setFocus(bool focus);

	/// Returns true if the camera is following this actor
	bool hasFocus();

	/// True, if the actor was started
	bool running() { return m_started;}

protected:

	/// Retruns the time elapsed since the last call of this function
	float getElapsedTime();

    /// True if the player touches ground
    bool     			m_onGround;

    /// True if the player is jumping
    bool     			m_jumping;

    /// Indicates if the actors wants to start jumping
    bool				m_wantsToJump;

    /// Pixel position where jumping has started
    int     			m_jumpStart;

    /// The physical properties of the player
    PlayerProperty 		m_physicalProps;

    /// Time counter at object creation time
    Uint32				m_startTicks;

    /// The thread that triggers movement
    std::thread			m_thread;

    /// True if the camera is following this actor
    bool				m_focus;

    /// True if the actor has been started
    bool				m_started;
};

} /* namespace jumper */

#endif /* SRC_ACTOR_HPP_ */
