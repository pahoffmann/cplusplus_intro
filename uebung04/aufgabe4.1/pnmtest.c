#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "jmprPNMIO.h"


SDL_Surface* jmpr_surfaceFromImage(jmpr_Image* img){
        SDL_Surface* surface;
        int width;
        int hight;
        int pitch;
        Uint32 rmask;
        Uint32 gmask;
        Uint32 bmask;
        Uint32 amask;
        unsigned char *pixels;
        int i;
        int j;
        int k;

        k=0;


        width = img->w;
        hight = img->h;
        pitch = width * 3;
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
        pixels = (unsigned char *)malloc(hight*width*3*sizeof(unsigned char*));


        for(i=0; i < hight; i++){
                for(j=0; j < width; j++){
                        pixels[k] = (unsigned char) img->pixels[i][j].r;
                        k++;
                        pixels[k] = (unsigned char) img->pixels[i][j].g;
                        k++;
                        pixels[k] = (unsigned char) img->pixels[i][j].b;
                        k++;
                }
        }

        surface = SDL_CreateRGBSurfaceFrom(pixels,width,hight,24,pitch,rmask,gmask,bmask,amask);

        return surface;
}


int main(int argc, char *argv[]){
	

	char* filename;
        jmpr_Image* image;
        SDL_Surface* surface;
        SDL_Window* window;
        SDL_Texture* texture;
        SDL_Renderer* renderer;

        filename = "panorama1.pnm";
        printf("%s\n",filename);
        image = jmpr_readImage(filename);
        if((SDL_Init(SDL_INIT_VIDEO)) != 0){
        fprintf(stderr, "%s\n", SDL_GetError());
                return -1;
        }

        window = SDL_CreateWindow("TEST", 0, 0, (image->w)/3,1133/3, SDL_WINDOW_SHOWN);

        if(NULL == window){
            fprintf(stderr, "%s\n", SDL_GetError());
            return -1;
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if(NULL == renderer){
            fprintf(stderr, "%s\n", SDL_GetError());
            return -1;
        }

        surface = jmpr_surfaceFromImage(image);
        texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_RenderCopy(renderer,texture,0,0);
        SDL_RenderPresent(renderer);
        SDL_Delay(10000);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
	jmpr_freeImage(image);
        SDL_Quit();


        return 0;
	

}

