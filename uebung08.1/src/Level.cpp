#include "Level.hpp"


// Constructs a new Level from the .lvl file specified by filename.
// The Renderer is used to render the tiles
Level::Level(SDL_Renderer* prenderer, std::string filename){
	

	renderer = 0;
	tileset = 0;
        std::string texture_filename;
        int r, g, b;

        // Alloc memory for tileset struct 
        tileset = new struct jmprLevel;
	renderer = prenderer;

        if(tileset == 0)
        {
                std::cout << "jmprLoadTileDefinitions: Unable to alloc memory for tileset struct" << std::endl;      
                exit(1);
        }

        std::ifstream in(filename.c_str());
        if(!in.good())
        {
                std::cout << "jmprLoadTileDefinitions: Unable to open file " << filename << std::endl;        
                exit(1);
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
	tileset->matrix = new SparseMatrix(tileset->level_height, tileset->level_width);
	int tmp = 0;

        // Read tile numbers in grid
        for(int i = 0; i < tileset->level_height; i++)
        {
                for(int j = 0; j < tileset->level_width; j++)
                {
                        in >> tmp;
			tileset->matrix->insert(i,j,tmp);
                }
        }

        // Alloc texture 
        tileset->texture = loadTexture(texture_filename.c_str());
	in.close();
		
}
// Renders the level
void Level::render(Camera &cam){

	int i;
        int j;
        int tile_index;
        int col, row;
        SDL_Rect target;
        SDL_Rect source;

        /* Set target / source width and height to tile size,
         * they never change
         */
        target.w = tileset->tile_width;
        target.h = tileset->tile_height;

        source.w = tileset->tile_width;
        source.h = tileset->tile_height;


        for(i = 0; i < tileset->level_height; i++)
        {
                for(j = 0; j < tileset->level_width; j++)
                {
                        tile_index =(*tileset->matrix)[i][j];
			tile_index --;
                        if(tile_index >= 0)
                        {
                                /* Compute the position of the target on the screen */
                                target.x = j * tileset->tile_width + cam.x();
                                target.y = i * tileset->tile_height + cam.y();

                                /* Compute the position of the source pixel data
                                 * within the texture (no offset for first tiles)
                                 */
                                row = tile_index / tileset->tiles_per_row;
                                col = tile_index % tileset->tiles_per_row;

                                source.x = col * tileset->tile_width;
                                if(col > 0)
                                {
                                        source.x += col * tileset->tile_offset;
                                }

                                source.y = row * tileset->tile_height;
                                if(row > 0)
                                {
                                        source.y += row * tileset->tile_offset;
                                }

                                /* Copy pixel date to correct position */
                                SDL_RenderCopy( renderer, tileset->texture, &source, &target);
                        }
                }
        }


}
// Frees all resources
Level::~Level(){
	delete tileset->matrix;
	SDL_DestroyTexture(tileset->texture);
}
// Loads a texture from the given file
SDL_Texture* Level::loadTexture(std::string texFileName){
	


	/* The loaded texture */
        SDL_Texture* newTexture = NULL;

        /* Load image at specified path */
        SDL_Surface* loadedSurface = IMG_Load(texFileName.c_str());
        if( loadedSurface == NULL )
        {
                std::cout << "Unable to load image '" << texFileName << "': " << IMG_GetError() << std::endl;
        }
        else
        { 
		/* Set keying color */
                SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, tileset->key_r, tileset->key_g, tileset->key_b ) );

		//Create texture from surface pixels
                newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
                if( newTexture == NULL )
                {
                        std::cout << "Unable to generate texture from '" << texFileName << "': " << IMG_GetError() << std::endl;
                }
                //Get rid of old loaded surface
                SDL_FreeSurface( loadedSurface );
        }
        return newTexture;
}






