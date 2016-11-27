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
#include <fstream>
#include <iostream>
#include <SDL.h>
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



/**
 * Loads a tileset from the given file.
 *
 * @param       filename        A file defining a tile set.
 * @return      A pointer to jmprTileSet struct (if loaded successfully)
 *                      or a null pointer if the given file could not be
 *                      parsed.
 */

struct jmprLevel* jmprLoadTileDefinitions(const char* filename)
{	
 	int key_r;
        int key_g;
        int key_b;
	
	int i,j;

        jmprLevel* level;
	int** tiles;
        SDL_Texture* texture;
        const char* tilefile;
        std::string tilefilename;
        std::ifstream in;
        
	/* opening file */
	in.open(filename);
        if(!in.good()){
                exit(1);
        }


        /* getting and setting level parameters */
        level = (jmprLevel*)malloc(sizeof(jmprLevel));


        std::getline(in,tilefilename);                   /*getting the first line of test.lvl */
        tilefile = tilefilename.c_str();                 /* converting string to const char* */
        std::cout << tilefile << std::endl;              /* printing for test */
        in>>(level->tile_width)                          /* tile width */
          >>(level->tile_height)                         /* tile height */
          >>(level->tiles_per_row)                       /* tile tiles_per_row */
          >>(level->num_rows)                            /* tile num_rows */
          >>(level->tile_offset)                         /* tile tile_offset */
          >>(key_r)                                      /* key_r keycolor */
          >>(key_g)                                      /* key_g keycolor */
          >>(key_b)                                      /* key_b keycolor */
          >>(level->level_width)                         /* level-width */
          >>(level->level_height);                       /* level-height */

        level->key_r = (unsigned char)key_r;
        level->key_g = (unsigned char)key_g;
        level->key_b = (unsigned char)key_b;

        /*printtest! */
        std::cout << level -> tile_width << " " << level -> tile_height << " " <<level -> num_rows <<
                     " " << level -> tiles_per_row << " " << level -> tile_offset << " " <<(int)(level -> key_r) <<
                     " " << (int)(level -> key_g) << " " <<(int)(level -> key_b) << " " << level->level_width <<
                     " " <<level -> level_height<<std::endl;

        texture = jmprLoadTextureWithKey(tilefile,level->key_r,level->key_g,level->key_b);
	level->texture = texture;
	
        tiles = (int**)malloc((level->level_height)*sizeof(int));
        for(i=0;i<(level->level_height);i++){
                tiles[i]=(int*)malloc((level->level_width)*sizeof(int));
        }


        for(i=0;i<(level->level_height) && in;i++){
                for(j=0;j<(level->level_width) && in; j++){
                        in>>tiles[i][j];
                }
        }
        level -> tiles = tiles;
	in.clear();
	in.close();


        return level;    /* returning the loaded level*/
}


/***
 * Renders a tileset.
 * @param       tileset A tileset to render.
 */
void jmprRenderTiles(struct jmprLevel* t){
	SDL_Rect* source;
	SDL_Rect* target;
	
	int i,j;
	int tmp;
	int row;
	int column;

	source = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	target = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	
	source->w = 16;
	source->h = 16;

	target->w = 16;
	target->h = 16;
	
	for(i=0 ; i < t->level_height ; i++){
		for(j=0 ; j < t->level_width ; j++){
			
			tmp = t->tiles[i][j]-1;
		
			if( tmp != -1 ){
				column = (tmp % (t -> tiles_per_row));
				row = ((tmp / (t-> tiles_per_row)));
				source->x = column*16 + (column * t->tile_offset) ;
				source->y = row * 16  + (row * t->tile_offset) ;
				target->y = i*(t->tile_height ); //passt
				target->x = j*(t->tile_width );  //passt

				SDL_RenderCopy(pRenderer,t->texture,source,target);
			}
		}
	}

	free(source);
	free(target);


}





