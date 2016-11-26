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

#include <stdio.h>
#include <SDL2/SDL.h>

#include "jmpr.hpp"


int main(int argc, char** argv)
{
	SDL_Event e;
	int quit = 0;
	struct jmprLevel* tileset = NULL;

	if(jmprInitSDL())
	{
		/* Load tiles and sprites */
		tileset = jmprLoadTileDefinitions(argv[1]);
		if(tileset == NULL)
		{
			printf("jmprMain: Unable to load tileset %s.\n", argv[1]);
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

        int i;

        for(i=0;i<tileset->level_height;i++){
			free(tileset->tiles[i]);
        }
        free(tileset->tiles);
	
	free(tileset);
	jmprClearSDL();

    return 0;
}
