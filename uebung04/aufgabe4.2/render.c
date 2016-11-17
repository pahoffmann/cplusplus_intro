#include <SDL2/SDL.h>
#include <stdio.h>
#include "jmprImageFake.h"
#include <stdint.h>

SDL_Surface *surface;



SDL_Surface* jmpr_surfaceFromImage(jmpr_Image* img){
	int k;
	int width;
	int height;
	Uint32 rmask;
	Uint32 gmask;
	Uint32 bmask;
	Uint32 amask;
	int pitch;
	
	k = 0;
	width = img->w;
	height = img->h;
	
	unsigned char *pixel = (unsigned char *)malloc(width * height * 3 * sizeof(unsigned char *));
	
	
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			pixel[k] = (unsigned char)img->pixels[i][j].r;
			k++;
			pixel[k] = (unsigned char)img->pixels[i][j].g;
			k++;
			pixel[k] = (unsigned char)img->pixels[i][j].b;
			k++;
		}
	}
	
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
	pitch = width * 3;
	
	surface = SDL_CreateRGBSurfaceFrom(pixel, width, height, 24, pitch, rmask, gmask, bmask, amask);
	
	return surface;
	
}



int main(void){
	
    SDL_Window*			window;
    SDL_Renderer* 		renderer;
	jmpr_Image* image;
	SDL_Texture* tex;
    
    window 		= 0;
    renderer 	= 0;
	image = 0;
	
    if((SDL_Init(SDL_INIT_VIDEO)) != 0){
    	fprintf(stderr, "%s\n", SDL_GetError());
		return -1;
	}
	
	window = SDL_CreateWindow("TEST", 0, 0, 800, 600, SDL_WINDOW_SHOWN);
	
	if(NULL == window){
	    fprintf(stderr, "%s\n", SDL_GetError());
	    return -1;
	}
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(NULL == renderer){
	    fprintf(stderr, "%s\n", SDL_GetError());
	    return -1;
	}

	image = jmpr_getFakeImage();
	surface = jmpr_surfaceFromImage(image);
	
	tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, tex, 0, 0);

	SDL_RenderPresent(renderer);
	SDL_Delay(10000);
	SDL_DestroyWindow(window);
	SDL_Quit();
				   
	
	return 0;
}