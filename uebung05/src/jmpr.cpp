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
	SDL_DestroyWindow(pWindow);
	pWindow = NULL;

	SDL_DestroyRenderer(pRenderer);
	pRenderer = NULL;

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
	return 0;
}

void jmprRenderTiles(struct jmprLevel* t)
{

}


