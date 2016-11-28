/*
 * main.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: Thomas Wiemann
 *
 *  Copyright (c) 2015 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include <SDL.h>
#include <iostream>
#include "jmpr.hpp"


int main(int argc, char** argv)
{
	SDL_Event e;
	int quit = 0;
	struct jmprLevel* tileset = 0;

	if(jmprInitSDL())
	{
		/* Load tiles and sprites */
		tileset = jmprLoadTileDefinitions(argv[1]);
		if(tileset == NULL)
		{
			std::cout << "jmprMain: Unable to load tileset " << argv[1] << std::endl;
			exit(-1);
		}


		/* Start main loop and event handling */
		while(!quit)
		{
			/* Processs events, detect quit signal for window closing */
			while(SDL_PollEvent(&e))
			{
				if(e.type == SDL_QUIT)
				{
					quit = 1;
				}
			}

			/* Clear screen */
			SDL_RenderClear( pRenderer );

			/* Render tiles and sprite */
			jmprRenderTiles(tileset);

			/* Update screen */
			SDL_RenderPresent( pRenderer );
		}
	}

	for(int i = 0; i < tileset->level_height; i++)
	{
		delete[] tileset->tiles[i];
	}
	delete[] tileset->tiles;
	delete tileset;
	jmprClearSDL();

    return 0;
}
