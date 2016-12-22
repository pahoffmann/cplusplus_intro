#include "Renderable.hpp"
//Default-Konstruktor
Renderable::Renderable(){
	
	pos = 0;
	width = 0;
	height = 0;
	renderer = 0;
	texture = 0;
}

Renderable::Renderable(SDL_Renderer* renderer):Renderable(){
	this->renderer = renderer;
}

Renderable::Renderable(SDL_Renderer* renderer, std::string filename):Renderable(renderer){
	texture = loadTexture(filename);
}

Renderable::Renderable(Renderable& other){
	if(this != &other){
		copy(other);
	}
}

SDL_Texture* Renderable::loadTexture(std::string texFileName){

        /* The loaded texture */
        SDL_Texture* newTexture = NULL;

        /* Load image at specified path */
        SDL_Surface* loadedSurface = IMG_Load(texFileName.c_str());
        if( loadedSurface == NULL )
        {
                std::cout << "Unable to load image '" << texFileName << "': " << IMG_GetError() << std::endl;
		//exit(1);
        }
        else
        {

                //Create texture from surface pixels
                newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
                if( newTexture == NULL )
                {
                        std::cout << "Unable to generate texture from '" << texFileName << "': " << IMG_GetError() << std::endl;
                	exit(1);
		}
                //Get rid of old loaded surface
                SDL_FreeSurface( loadedSurface );
        }
        return newTexture;


}

SDL_Texture* Renderable::loadTextureWithKey(std::string texFileName, int r, int g, int b){
        
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
                SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format,r,g,b ));

                //Create texture from surface pixels
                newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
                if( newTexture == NULL )
                {
                        std::cout << "Unable to generate texture from '" << texFileName << "': " << IMG_GetError() << std::endl;
                	exit(1);
		}
                //Get rid of old loaded surface
                SDL_FreeSurface( loadedSurface );
        }
        return newTexture;


}

void Renderable::copy(const Renderable& other){
	pos.setX(other.pos.x());
	pos.setY(other.pos.y());
	height = other.height;
	width = other.width;
	texture = other.texture;
	renderer = other.renderer;
}
void Renderable::remove(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	
}

Renderable::~Renderable(){
	remove();
}
