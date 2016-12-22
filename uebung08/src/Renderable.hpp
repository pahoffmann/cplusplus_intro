#ifndef SRC_RENDERABLE_
#define SRC_RENDERABLE_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Pixel.hpp"


class Renderable{
	
	protected:
	
	std::string filename;	
	Pixel pos;
	int width;
	int height;

	
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	
	void copy(const Renderable& other);
	void remove();
	
		
	public:

	Renderable();

	Renderable(SDL_Renderer* renderer);

	Renderable(SDL_Renderer* renderer,std::string filename);
	
	Renderable(Renderable& other);
	
	SDL_Texture* loadTexture(std::string texFileName);
	
	SDL_Texture* loadTextureWithKey(std::string texFileName, int r,int g,int b);

	virtual void render() = 0;
	
	virtual ~Renderable();
	

};

#endif /* SRC_RENDERABLE_ */
