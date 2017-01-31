/*
 * Level.cpp
 *
 *  Created on: Nov 13, 2015
 *      Author: twiemann
 */

#include "JumperTypes.hpp"
#include "Level.hpp"
#include "StaticRenderable.hpp"
#include "Actor.hpp"
#include "Player.hpp"
#include "TextureFactory.hpp"

#include <iostream>
#include <fstream>
#include <SDL_image.h>


namespace jumper
{


Level::Level(SDL_Renderer* renderer, std::string filename) : StaticRenderable(renderer)
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

	// Read meta data from level file
	std::ifstream in(filename.c_str());
	std::string texFileName;

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

    m_tiles = new TileTree<int>(0, 0, m_levelWidth, m_levelHeight, VERTICAL);
	TileTree<int>::TileHeight = m_tileHeight;
	TileTree<int>::TileWidth = m_tileWidth;

	// Cast keying colors manually!
	m_keyR = (unsigned char)ir;
	m_keyG = (unsigned char)ib;
	m_keyB = (unsigned char)ig;

	// Load texture
	std::size_t found = filename.find_last_of("/\\");
	string path = filename.substr(0,found);
	m_texture = TextureFactory::instance(m_renderer).getTexture(path + "/" + texFileName, m_keyR, m_keyG, m_keyB);

	if(!m_texture)
	{
		std::cout << "Unable to load texture " << texFileName << std::endl;
	}

	// Read tile indices
    for(int y = 0; y < m_levelHeight; y++)
	{
        for(int x = 0; x < m_levelWidth; x++)
		{
			int tileID;
			in >> tileID;
            m_tiles->insert(x, y, tileID);
		}
	}

	in.close();
}

void Level::render()
{
	TileList tiles;
	m_tiles->clip(Renderable::m_camera, tiles);

	if(m_texture)
	{

		int col, row;
		SDL_Rect target;
		SDL_Rect source;
        int x, y, tile_index;

		target.w = m_tileWidth;
		target.h = m_tileHeight;

		source.w = m_tileWidth;
		source.h = m_tileHeight;

		for(auto it : tiles)
		{

            y = std::get<1>(it);
            x = std::get<0>(it);
			tile_index = std::get<2>(it) - 1;

            target.x = x * m_tileWidth;
            target.y = y * m_tileHeight;

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

			// Render Level according to camera position
			shiftTargetRect(target);

			// Copy pixel date to correct position
			SDL_RenderCopy(getRenderer(), m_texture, &source, &target);

		}

	}
}

WorldProperty Level::physics() const
{
	return m_levelPhysics;
}

void Level::getSurroundingTiles(Vector2f pos, int width, int height, Vector2i *tiles)
{
    /* Determine x and y position of the sprite within the grid */
    Vector2i gridPos(floor((pos.x() + 0.5 * width) / m_tileWidth), floor((pos.y() + 0.5 * height) / m_tileHeight));

    /* Get the surrounding tiles in "priority" order, i.e., we want
     * check some collisions like left before we check the others
     */
    tiles[0].setX(gridPos.x() - 1);
    tiles[0].setY(gridPos.y() - 1);

    tiles[1].setX(gridPos.x());
    tiles[1].setY(gridPos.y() - 1);

    tiles[2].setX(gridPos.x() + 1);
    tiles[2].setY(gridPos.y() - 1);

    tiles[3].setX(gridPos.x() - 1);
    tiles[3].setY(gridPos.y());

    tiles[4].setX(gridPos.x() + 1);
    tiles[4].setY(gridPos.y());

    tiles[5].setX(gridPos.x() - 1);
    tiles[5].setY(gridPos.y() + 1);

    tiles[6].setX(gridPos.x());
    tiles[6].setY(gridPos.y() + 1);

    tiles[7].setX(gridPos.x() + 1);
    tiles[7].setY(gridPos.y() + 1);

}

int Level::levelHeight() const
{
    return m_levelHeight;
}

int Level::levelWidth() const
{
    return m_levelWidth;
}

TileTree<int>& Level::tiles()
{
    return *m_tiles;
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
}

Collision Level::resolveCollision(Actor* player)
{
	SDL_Rect tileRect;
	SDL_Rect spriteRect;
	SDL_Rect intersectionRect;
	Vector2f desiredPosition;
	Vector2i surroundingTiles[8];

	int dx = 0;
	int dy = 0;

	//Convert the player sprite's screen position to global position
	//Vector2f global_pos = m_player->position() + Vector2f(m_camera.position().x(), m_camera.position().y());

	Vector2f global_pos = player->position();

	// Set desired position to new position
	desiredPosition = global_pos;


	// Check if sprite intersects with one of its surrounding tiles
	getSurroundingTiles(global_pos, player->w(), player->h(), surroundingTiles);
    int d_y, d_x;
    int f_y, f_x;
	player->setOnGround(false);
    f_y = surroundingTiles[6].y();
    f_x = surroundingTiles[6].x();

	if(player->physics().velocity().x() > 0)
	{
        d_y = surroundingTiles[7].y();
        d_x = surroundingTiles[7].x();
	}
	else
	{
        d_y = surroundingTiles[5].y();
        d_x = surroundingTiles[5].x();
	}

    if(f_y < m_levelHeight && f_x < m_levelWidth)
	{
        if( (*m_tiles)[f_y][f_x] > 0) player->setOnGround(true);
	}


    if(d_y < m_levelHeight && d_x < m_levelWidth )
	{
        if( (*m_tiles)[d_y][d_x] > 0) player->setOnGround(true);
	}


    for(int n = 0; n < 8; n++)
	{
        int x = surroundingTiles[n].x();
        int y = surroundingTiles[n].y();

		// Check, if tile coordinates are valid
        if((y >= 0) && (y < m_levelHeight) && (x >= 0) && (x < m_levelWidth) )
		{


            if((*m_tiles)[y][x] > 0)
			{

				// Get SDL rect for current tile and sprite and check intersection
                tileRect.y = y * m_tileHeight;
                tileRect.x = x * m_tileWidth;
				tileRect.w = m_tileWidth;
				tileRect.h = m_tileHeight;

				spriteRect.x = desiredPosition.x();
				spriteRect.y = desiredPosition.y();
				spriteRect.w = player->w();
				spriteRect.h = player->h();

				if(SDL_IntersectRect(&tileRect, &spriteRect, &intersectionRect))
				{

					if(n == 3)
					{
						dx = 100;
					}

					if(n == 6)
					{
						player->setOnGround(true);
					}

					// Handle pose correction cases
					if(n == 4)
					{
						dx = 100;
						desiredPosition.setX(desiredPosition.x() - intersectionRect.w);
					}
					else if(n == 1)
					{
						desiredPosition.setY(desiredPosition.y() + intersectionRect.h);
						player->setJumping(false);
					}
					else if(n == 3)
					{
						desiredPosition.setX(desiredPosition.x() + intersectionRect.w);
					}
					else if(n == 6)
					{
						desiredPosition.setY(desiredPosition.y() - intersectionRect.h);
					}
					else
					{
						if(intersectionRect.w >= 2 && intersectionRect.h >= 2)
						{
							if(intersectionRect.w > intersectionRect.h)
							{
								if( (n == 5) || (n == 7))
								{
									desiredPosition.setY(desiredPosition.y() - intersectionRect.h);
								}
								else
								{
									desiredPosition.setY(desiredPosition.y() + intersectionRect.h);
								}
							}
							else
							{
								if( (n == 2) || (n == 7))
								{
									desiredPosition.setX(desiredPosition.x() - intersectionRect.w);
								}
								else
								{
									desiredPosition.setX(desiredPosition.x() + intersectionRect.w);
								}
								if( (n == 0) || (n == 2) )
								{
									player->setJumping(false);
								}
							}
						}
					}

				}
			}
		}
	}

    player->setPosition(Vector2f(desiredPosition.x(), desiredPosition.y()));
	return Collision(Vector2i(dx, dy));
}

void Level::updatePlayerPosition(int move, bool jump, double dt)
{
//	cout << "DO NOT USE THIS" << endl;
//	m_player->nextFrame();
//	if(dt > 0)
//	{
//
//		if(dt > 0 && jump && m_player->onGround())
//		{
//			m_player->setJumping(true);
//		}
//
//		Vector2f d_gravity;
//		Vector2f d_move;
//
//		d_gravity = m_levelPhysics.gravity() * dt;
//
//		if(move != 0)
//		{
//			d_move = (m_player->physics().moveForce() * dt) * move;
//		}
//		else
//		{
//			d_move.setX(0);
//			d_move.setY(0);
//		}
//
//		// Update velocity
//		m_player->physics().setVelocity(m_player->physics().velocity() + d_move + d_gravity);
//
//		// Add jumping momentum
//		if(m_player->jumping())
//		{
//			m_player->physics().velocity().setY(
//					m_player->physics().velocity().y() + (m_player->physics().jumpForce().y() * dt) );
//		}
//
//		// Damp velocity according to extrinsic level damping
//		m_player->physics().setVelocity(m_player->physics().velocity() * m_levelPhysics.damping());
//
//		// Clamp velocities
//		if(m_player->physics().velocity().x() > m_player->physics().maxRunVelocity() * dt)
//		{
//			m_player->physics().setVelocity(Vector2f(m_player->physics().maxRunVelocity() * dt,
//													 m_player->physics().velocity().y()));
//		}
//
//		if(m_player->physics().velocity().x() < -m_player->physics().maxRunVelocity() * dt)
//		{
//			m_player->physics().setVelocity(Vector2f(-m_player->physics().maxRunVelocity() * dt,
//													 m_player->physics().velocity().y()));
//		}
//
//		if(m_player->physics().velocity().y() > m_player->physics().maxFallVelocity() * dt)
//		{
//			m_player->physics().setVelocity(
//					Vector2f(m_player->physics().velocity().x(), m_player->physics().maxFallVelocity() * dt));
//		}
//
//		if(m_player->physics().velocity().y() < -m_player->physics().maxJumpVelocity() * dt)
//		{
//			m_player->physics().setVelocity(
//					Vector2f(m_player->physics().velocity().x(), -m_player->physics().maxJumpVelocity() * dt));
//		}
//
//		// Set new player position
//		m_player->physics().setPosition(m_player->physics().position() + m_player->physics().velocity());
//
//		m_camera.position().setX(m_player->position().x());
//		m_camera.position().setY(300);
//		//m_camera.position().setY(m_player->position().y());
//		// Stop jumping at maximum jumping height
//		if(fabs(m_player->physics().position().y() - m_player->jumpStart()) >= m_player->physics().maxJumpHeight())
//		{
//			m_player->setJumping(false);
//		}
//
//	}
}




} /* namespace jumper */
