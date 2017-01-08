/*
 * Level.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#include "Level.hpp"
#include "StaticRenderable.hpp"

#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>


namespace jumper
{


Level::Level(SDL_Renderer* renderer, std::string filename, Camera & camera) :
		StaticRenderable(renderer), m_camera(camera)
{
	// Set all default values
	m_texture 		= 0;
	m_tileWidth 	= 0;
	m_tileHeight	= 0;
	m_tileOffset 	= 0;
	m_numRows = 0;
	m_keyR = 0;
	m_keyG = 0;
	m_keyB = 0;
	m_tilesPerRow = 0;
	m_levelWidth = 0;
	m_levelHeight = 0;
	m_player = 0;

	// Read meta data from level file
	std::ifstream in(filename.c_str());
	std::string texFileName;
	std::cout << filename << std::endl;
	int ir, ig, ib;

	if(in.good())
	{
		in >> texFileName;
		in >> m_tileWidth >> m_tileHeight >> m_tilesPerRow >> m_numRows;
		in >> m_tileOffset >> ir >> ig >> ib;
		in >> m_levelWidth >> m_levelHeight;
	}
	else
	{
		std::cout << "Unable to open file " << filename << std::endl;
	}

	/*SparseMatrix tiles(m_levelWidth, m_levelHeight);
	m_tiles = tiles;*/

	m_tiles = new TileTree(0, 0, m_tileWidth * m_levelWidth, m_tileHeight * m_levelHeight, VERTICAL); //<- TILE TREE VERSION
	TileTree::m_tileWidth = m_tileWidth;
	TileTree::m_tileHeight = m_tileHeight;

	// Cast keying colors manually!
	m_keyR = (unsigned char)ir;
	m_keyG = (unsigned char)ib;
	m_keyB = (unsigned char)ig;

	// Load texture
	std::cout << texFileName << std::endl;
	m_texture = loadTexture(texFileName, m_keyR, m_keyG, m_keyB);

	if(!m_texture)
	{
		std::cout << "Unable to load texture " << texFileName << std::endl;
	}

	// Read tile indices
	for(int i = 0; i < m_levelHeight; i++)
	{
		for(int j = 0; j < m_levelWidth; j++)
		{
			int tileID;
			in >> tileID;
			//m_tiles.insert(j, i, tileID);
			m_tiles->insert(j, i, tileID); // <- TILE TREE VERSION
		}
	}

	in.close();
}

void Level::setPlayer(Player* player)
{
	m_player = player;
}

Player* Level::getPlayer()
{
	return m_player;
}

void Level::render()
{
	if(getRenderer() && m_texture)
	{
		int i;
		int j;
		int tile_index;
		int col, row;
		SDL_Rect target;
		SDL_Rect source;


		target.w = m_tileWidth;
		target.h = m_tileHeight;

		source.w = m_tileWidth;
		source.h = m_tileHeight;


		for(i = 0; i < m_levelHeight; i++)
		{
			for(j = 0; j < m_levelWidth; j++)
			{
				tile_index = m_tiles->get(j,i) - 1;  	//<- TILE TREE VERSION

				/* tile_index = m_tiles[j][i] - 1; */
				if(tile_index >= 0)
				{
					//Compute the position of the target on the screen
					target.x = j * m_tileWidth - m_camera.x();
					target.y = i * m_tileHeight - m_camera.y();


					row = tile_index / m_tilesPerRow;
					col = tile_index % m_tilesPerRow;

					source.x = col * m_tileWidth;
					if(col > 0)
					{
						source.x += col * m_tileOffset;
					}

					source.y = row * m_tileHeight;
					if(row > 0)
					{
						source.y += row * m_tileOffset;
					}

					// Copy pixel date to correct position
					SDL_RenderCopy(getRenderer(), m_texture, &source, &target);
				}
			}
		}
	}
	if(m_player)
	{
		m_player->render();
	}
}


int Level::levelHeight() const
{
    return m_levelHeight;
}

int Level::levelWidth() const
{
    return m_levelWidth;
}

int Level::tileWidth() const
{
    return m_tileWidth;
}

int Level::tileHeight() const
{
    return m_tileHeight;
}

Level::~Level()
{
    // Free texture resources
    SDL_DestroyTexture(m_texture);

    delete m_tiles; //<- TILE TREE VERSION
}




} /* namespace jumper */
