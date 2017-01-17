/*
 * ScoreBoard.hpp
 *
 *  Created on: Jan 2, 2016
 *      Author: twiemann
 */

#ifndef SRC_SCOREBOARD_HPP_
#define SRC_SCOREBOARD_HPP_

#include "StaticRenderable.hpp"

namespace jumper
{

/// Renders a score board at the upper left corner of the
/// given renderer
class ScoreBoard : public StaticRenderable
{
public:

	/// Creates a score bord for the given renderer using a texture and information about
	/// the digits (with, height) in it
	ScoreBoard(SDL_Renderer* renderer, SDL_Texture* texture, int digitWidth, int digitHeight);

	/// Creates an empty score board
	ScoreBoard(SDL_Renderer* renderer);

	/// Sets the rendered number
	void setScore(int score);

	/// Gets the current score
	int getScore() const;

	/// Sets the upper left corner of the score board in display coordinates
	void setPosition(const Vector2i& position);

	/// Renders the score board
	virtual void render();

	/// Destructor
	virtual ~ScoreBoard();

private:

	/// The current score
	int 					m_score;

	/// Digit with in the texture
	int						m_digitWidth;

	/// Digit height in the texture
	int						m_digitHeight;

	/// Rendering position
	Vector2i				m_position;

	/// The maximum score that can be displayed by this board
	const static int 		m_maxScore;
};

} /* namespace jumper */

#endif /* SRC_SCOREBOARD_HPP_ */
