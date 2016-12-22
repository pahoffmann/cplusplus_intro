#ifndef SRC_LEVEL_
#define SRC_LEVEL_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Camera.hpp"
#include "SparseMatrix.hpp"
#include "StaticRenderable.hpp"




class Level : public StaticRenderable{

private:

	struct jmprLevel {
       		int tile_width;                 /* With of the tiles within the tile set bitmap  */
       		int tile_height;                /* Height of the tile within the tile set bitmap */
     		int tile_offset;                /* Offset between the tiles (in pixels)          */
       		int num_rows;                   /* Number of tile rows in the bitmap             */
       		unsigned char key_r;    /* R component of the keying color               */
       		unsigned char key_g;    /* G component of the keying color               */
       		unsigned char key_b;    /* B component of the keying color               */
       		int tiles_per_row;              /* Number of tiles per row                       */
       		int level_width;                /* Number of tiles per row in the tile array     */
       		int level_height;               /* Number of rows in the tile array              */
       		SDL_Texture* texture;   /* A SDL_Texture struct containing the bitmap    */
       		SparseMatrix* matrix;            /* An array containing tile indices              */
	};
	
	//SDL_Renderer* renderer;
	struct jmprLevel* tileset;

public:

	

	/* Constructs a new Level from the .lvl file specified by filename.
	 The Renderer is used to render the tiles*/
	Level(SDL_Renderer* renderer, std::string filename);
	

	/* Renders the level */
	void render(Camera &cam);
	
	void render();	

	/* Frees all resources */
	~Level();
	

	/* Loads a texture from the given file */
	//SDL_Texture* loadTexture(std::string texFileName);

};

#endif /* SRC_LEVEL_ */






