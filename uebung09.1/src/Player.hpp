//
// Created by isaak on 26.11.15.
//

#ifndef JUMPER_PLAYER_H
#define JUMPER_PLAYER_H

#include <fstream>
#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "AnimatedRenderable.hpp"
#include "Vector.hpp"

namespace jumper
{

/***
 * A class to represent an animated sprite controlled
 * by the user.
 */
class Player : public AnimatedRenderable
{
public:

	/***
	 * Constructor.
	 *
	 * @param renderer	A pointer to a valid SDL_Renderer struct that is
	 * 					used for rendering
	 * @param filename	The name of a file with sprite definitions
	 */
    Player(SDL_Renderer* renderer, std::string filename);

    /***
     * Renders the player at current position with current frame
     */
    virtual void render();

    /***
     * Moves the player in the given \ref direction with given \ref speed
     */
    void move(int direction, float speed);

    /**
     * Sets the player's position
     */
    void setPosition(Vector2f pos);

    /***
     * Returns the player's current position
     */
    Vector2f position();

    /// Enum to define move directions
    enum direction {UP, DOWN, LEFT, RIGHT};

    /// Prints the player's position to the given stream
    template<typename T>
    friend std::ostream& operator<< (std::ostream& stream, const Vector2<T> & vec);
private:

    /// Screen position of the player
    Vector2f 		m_position;
};

}

#endif //JUMPER_PLAYER_H
