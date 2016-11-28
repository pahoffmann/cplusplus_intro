/*
 * jmpr.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2015 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "jmpr.hpp"

#include <iostream>
#include <fstream>
#include <string>

/* SDL related global variables */
SDL_Window* 	pWindow 		= 0;
SDL_Renderer*	pRenderer		= 0;

int jmprInitSDL()
{
	/* Init SDL */
	if(SDL_Init( SDL_INIT_VIDEO ) < 0)
	{
		std::cout << "SDL could not initialize: " << SDL_GetError() << std::endl;
		return 0;
	}

	/* Generate SDL main window */
	pWindow = SDL_CreateWindow(
			"Jumper Main Window",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN );

	if(pWindow == NULL)
	{
		std::cout << "SDL window could not be generated: " << SDL_GetError() << std::endl;
		return 0;
	}

	/* Create renderer for the SDL main window */
	pRenderer = SDL_CreateRenderer( pWindow, -1, SDL_RENDERER_ACCELERATED );

	if(pRenderer == NULL)
	{
		std::cout << "SDL could not generate renderer: " << SDL_GetError() << std::endl;
		return 0;
	}

	 //Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		return 0;
	}


	/* Set background color for renderer */
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 0);

	return 1;
}

void jmprClearSDL()
{
	SDL_DestroyRenderer(pRenderer);
	pRenderer = NULL;

	SDL_DestroyWindow(pWindow);
	pWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* jmprLoadTexture(const char* filename)
{
	/* The loaded texture */
	SDL_Texture* newTexture = NULL;

	/* Load image at specified path */
	SDL_Surface* loadedSurface = IMG_Load(filename);
	if( loadedSurface == NULL )
	{
		std::cout << "Unable to load image '" << filename << "': " << IMG_GetError() << std::endl;
	}
	else
	{ //Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface( pRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			std::cout << "Unable to generate texture from '" << filename << "': " << IMG_GetError() << std::endl;
		}
		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	return newTexture;
}

SDL_Texture* jmprLoadTextureWithKey(const char* filename, unsigned char key_r, unsigned char key_g, unsigned char key_b)
{
	/* The loaded texture */
	SDL_Texture* newTexture = NULL;

	/* Load image at specified path */
	SDL_Surface* loadedSurface = IMG_Load(filename);
	if( loadedSurface == NULL )
	{
		std::cout << "Unable to load image '" << filename << "': " << IMG_GetError() << std::endl;;
	}
	else
	{
		/* Set keying color */
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, key_r, key_g, key_b ) );

		/* Create texture from surface pixels */
		newTexture = SDL_CreateTextureFromSurface( pRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			std::cout << "Unable to generate texture from '" << filename << "': " << IMG_GetError() << std::endl;
		}

		/* Get rid of old loaded surface */
		SDL_FreeSurface( loadedSurface );
	}
	return newTexture;
}


struct jmprLevel* jmprLoadTileDefinitions(const char* filename)
{
	struct jmprLevel* tileset = 0;
	std::string texture_filename;
	int r, g, b;

	// Alloc memory for tileset struct 
	tileset = new struct jmprLevel;

	if(tileset == 0)
	{
		std::cout << "jmprLoadTileDefinitions: Unable to alloc memory for tileset struct" << std::endl;
		return NULL;
	}

	std::ifstream in(filename);
	if(!in.good())
	{
		std::cout << "jmprLoadTileDefinitions: Unable to open file " << filename << std::endl;
		return NULL;
	}

	in >> texture_filename;

	// Read tile set meta information
	in >> tileset->tile_width >> tileset->tile_height;
	in >> tileset->tiles_per_row >> tileset->num_rows;
	in >> tileset->tile_offset;
	in >> r >> g >> b;
	tileset->key_r = r;
	tileset->key_b = b;
	tileset->key_g = g;

	// Read dimensions of tile grid
	in >> tileset->level_width >> tileset->level_height;

	// Allocate memory for tile grid
	tileset->tiles = new int*[tileset->level_height];
	for(int i = 0; i < tileset->level_height; i++)
	{
		tileset->tiles[i] = new int[tileset->level_width];
	}

	// Read tile numbers in grid
	for(int i = 0; i < tileset->level_height; i++)
	{
		for(int j = 0; j < tileset->level_width; j++)
		{
			in >> tileset->tiles[i][j];
		}
	}

	// Alloc texture
	tileset->texture = jmprLoadTextureWithKey(texture_filename.c_str(), tileset->key_r, tileset->key_g, tileset->key_b);

	return tileset;
}

void jmprRenderTiles(struct jmprLevel* t)
{
	int i;
	int j;
	int tile_index;
	int col, row;
	SDL_Rect target;
	SDL_Rect source;

	/* Set target / source width and height to tile size,
	 * they never change
	 */
	target.w = t->tile_width;
	target.h = t->tile_height;

	source.w = t->tile_width;
	source.h = t->tile_height;


	for(i = 0; i < t->level_height; i++)
	{
		for(j = 0; j < t->level_width; j++)
		{
			tile_index = t->tiles[i][j] - 1;
			if(tile_index >= 0)
			{
				/* Compute the position of the target on the screen */
				target.x = j * t->tile_width;
				target.y = i * t->tile_height;

				/* Compute the position of the source pixel data
				 * within the texture (no offset for first tiles)
				 */
				row = tile_index / t->tiles_per_row;
				col = tile_index % t->tiles_per_row;

				source.x = col * t->tile_width;
				if(col > 0)
				{
					source.x += col * t->tile_offset;
				}

				source.y = row * t->tile_height;
				if(row > 0)
				{
					source.y += row * t->tile_offset;
				}

				/* Copy pixel date to correct position */
				SDL_RenderCopy( pRenderer, t->texture, &source, &target);
			}
		}
	}
}


