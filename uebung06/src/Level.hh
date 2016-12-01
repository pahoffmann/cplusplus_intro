#include <SDL2/SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <string>
#include <fstream>
#include "Camera.hh"




class Level{
	
	struct jmprLevel
	{
		int tile_width;			/* With of the tiles within the tile set bitmap  */
		int tile_height;		/* Height of the tile within the tile set bitmap */
		int tile_offset;		/* Offset between the tiles (in pixels)          */
		int num_rows;			/* Number of tile rows in the bitmap 			 */
		unsigned char key_r;	/* R component of the keying color               */
		unsigned char key_g;	/* G component of the keying color               */
		unsigned char key_b;	/* B component of the keying color               */
		int tiles_per_row;		/* Number of tiles per row                       */
		int level_width;		/* Number of tiles per row in the tile array     */
		int level_height;		/* Number of rows in the tile array              */
		SDL_Texture* texture;   /* A SDL_Texture struct containing the bitmap    */
		int** tiles;            /* An array containing tile indices              */
	};
	
	SDL_Renderer *pRenderer;
	struct jmprLevel *tileset;

	public:
		// Constructs a new Level from the .lvl file specified by filename.
		// The Renderer is used to render the tiles
		Level(SDL_Renderer* renderer, std::string filename);
		
		// Renders the level
		void render();
		
		// Renders a different segment of the level given by the camera
		void render(Camera &cam);

		// Frees all resources
		~Level();
		// Loads a texture from the given file
		SDL_Texture* loadTexture(std::string texFileName);
		
};