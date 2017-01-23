/*
 * Game.hpp
 *
 *  Created on: Dec 11, 2015
 *      Author: twiemann
 */

#ifndef SRC_GAME_HPP_
#define SRC_GAME_HPP_

#include "MainWindow.hpp"
#include "Actor.hpp"
#include "Bot.hpp"
#include "Player.hpp"
#include "Level.hpp"
#include "TexturedLayer.hpp"
#include "ScoreBoard.hpp"
#include "Network.hpp"
#include "PathPlanner.hpp"
#include "PathFollower.hpp"
#include "Path.hpp"

#include <vector>
using std::vector;

namespace jumper
{

class MainWindow;

/*
 *
 */
class Game
{
public:

	/// Constructor
	Game(MainWindow* window);

	/// Destructor
	virtual ~Game();

	/// Sets the player object
	void setPlayer(Player* player);

	/// Sets the current level
	void setLevel(Level* level);

	/// Adds a new bot to the scene
	void addActor(Actor* actor);

	/// Updates the current state according to the given key states
	void update(const Uint8* &currentKeyStates);

	/// Starts a actors in the game
	void start();

	/// Sets a layer object for background rendering
	void setLayer(TexturedLayer* layer) { m_layer = layer;}	;

	/// Renders the score board
	void setScoreBoard(ScoreBoard* b) { m_scoreBoard = b;};

	/// Sets the network for the path follower
	void setNetwork(Network* n);

	// Sets the path follower
	void setPathFollower(PathFollower* p) { m_pathFollower = p;};

private:

	/// Updates the global camera position
	void updateCameraPosition();

	/// All renderables in the game
	vector<Renderable*> 	m_renderables;

	/// All actors
	vector<Actor*>			m_actors;

	/// The user controlled player
	Player*					m_player;

	/// The current level
	Level*					m_level;

	/// A Layer
	TexturedLayer*			m_layer;

	/// A score board
	ScoreBoard*				m_scoreBoard;

	/// Pointer to the main window of the game
	SDL_Renderer*			m_renderer;

	/// Graph for path follower
	Network*				m_network;

	/// The shortest path from start to goal
	Path*					m_path;

	/// A path planner
	PathPlanner*			m_pathPlanner;

	/// The path follower
	PathFollower*			m_pathFollower;

	/// Window width
	int						m_windowWidth;

	/// Window height
	int						m_windowHeight;


};

} /* namespace jumper */

#endif /* SRC_GAME_HPP_ */
