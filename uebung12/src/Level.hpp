/*
 * Level.hpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#ifndef SRC_LEVEL_HPP_
#define SRC_LEVEL_HPP_

#include <string>
#include <SDL.h>


#include "Camera.hpp"
#include "StaticRenderable.hpp"
#include "SparseMatrix.hpp"
#include "Vector.hpp"
#include "WorldProperty.hpp"
#include "TileTree.hpp"
#include "Collision.hpp"

namespace jumper
{

class Actor;
class Player;

/***
 * Represents a level in the jumper game.
 */
class Level : public StaticRenderable
{
public:

	/***
	 * Loads a level from the given file
	 *
	 * @param filename
	 */
	Level(SDL_Renderer* renderer, std::string filename);

	/***
	 * Renders the level to the given renderer
	 *
	 * @param renderer		A SDL_Renderer to render the tiles
	 */
	virtual void render();

	/// The width of the level
	int levelHeight() const;

	/// The height of the level
	int levelWidth() const;

	/// The tile width
	int tileWidth() const;

	/// The tile height
	int tileHeight() const;

	/// A tile tree to manage tile rendering and collision
	TileTree<int>& tiles();

	/// World properties within the level
	WorldProperty physics() const;
	/***
	 * Destructor
	 */
	virtual ~Level();

	/// Implements collision checking and resolving for
	/// Player object
	Collision resolveCollision(Actor* player);

	/// Updates the current player position according to
	/// the physics model determined by the levels world
	/// properties and the physical properties of the player
	void updatePlayerPosition(int move, bool jump, double dt);

private:

	/// Gets the surrounding tiles to the player's position
	/// according the the needed priority order needed for
	/// consistant collision resolving
	void getSurroundingTiles(Vector2f pos, int width, int height, Vector2i *tiles);


	/// Tile width
	int					m_tileWidth;

	/// Tile height
	int					m_tileHeight;

	/// Offset between the tiles in the tile sheet
	int					m_tileOffset;

	/// Number of rows in the tile sheet
	int 				m_numRows;

	/// Key color red component
	unsigned char	 	m_keyR;

	/// Key color green component
	unsigned char		m_keyG;

	/// Key color blue component
	unsigned char		m_keyB;

	/// Number of tiles per row
	int					m_tilesPerRow;

	/// Level width
	int					m_levelWidth;

	/// Level height
	int					m_levelHeight;

	///Physical properties of level
	WorldProperty		m_levelPhysics;

	/// A tile tree to represent and manage the
	/// tileset of the level
	TileTree<int>*		m_tiles;
};

} /* namespace jumper */

#endif /* SRC_LEVEL_HPP_ */
