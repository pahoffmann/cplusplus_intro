#include "jmprPNMIO.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>


SDL_Surface* jmpr_surfaceFromImage(jmpr_Image* img){
        SDL_Surface* surface;
        int width;
        int height;
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
        height = img->h;
        pitch = width * 3;
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
	printf("PETER1");
        pixels = (unsigned char *)malloc(height*width*3*sizeof(unsigned char));


        for(i=0; i < height; i++){
                for(j=0; j < width; j++){
                        pixels[k] = (unsigned char) img->pixels[i][j].r;
                        k++;
                        pixels[k] = (unsigned char) img->pixels[i][j].g;
                        k++;
                        pixels[k] = (unsigned char) img->pixels[i][j].b;
                        k++;
                }
        }
	printf("PETER2");
        surface = SDL_CreateRGBSurfaceFrom(pixels,width,height,24,pitch,rmask,gmask,bmask,amask);

        return surface;
}








void jmpr_savePNM(char* filename, jmpr_Image* img, enum jmpr_PNMMode mode){
}


void printTest(jmpr_Pixel** image,int h,int w){
	printf("{%d, %d, %d}!!!!\n",image[h-1][w-1].r,image[h-1][w-1].g,image[h-1][w-1].b);
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			printf("{%d, %d, %d} ",image[i][j].r,image[i][j].g,image[i][j].b);
		}
		printf("\n");
	}
}

/**
* @brief reads an image from an PNM file
*
* @param filename name of the target file
*
*/

jmpr_Image* jmpr_readImage(char* filename){
	
	/**variables
	*/
	FILE* file;
	jmpr_Image* image;
	int width;
	int height;
	char magic[2];
	char buffer[120];
	jmpr_Pixel** pixels;
	int tmp;
	unsigned char* a;
	
	/**counters
	*/
	int i;
	int j;
	
	/**trying to open the file
	*/
	file = fopen(filename, "r");
	if(NULL==file){
		fputs("error",stderr);
		return NULL;
	}
	/**fetting parameters, skipping whitespace
	*/
	fscanf(file,"%s",magic);
	fgets(buffer,sizeof(buffer),file);
	printf("%s\n", buffer);
	fgets(buffer,sizeof(buffer),file);
	printf("%s\n", buffer);
	fscanf(file,"%d",&width);
	fscanf(file,"%d",&height);
	printf("%s, %d, %d\n",magic,width,height);
	fgets(buffer,sizeof(buffer),file);
	printf("%s\n", buffer);
	fgets(buffer,sizeof(buffer),file);
	printf("%s\n", buffer);

	/**allocating space for pixels array
	*/
	pixels = (jmpr_Pixel**)malloc(height* sizeof(jmpr_Pixel*));
	for(i = 0; i < height; i++){
                pixels[i] = (jmpr_Pixel*)malloc(width * sizeof(jmpr_Pixel));
        }
	
	/**if magic number is P2
	*/
	if(!strcmp(magic,"P2")){
		printf("Kekseee!!!!");
		for(i = 0; i < height ; i++){
			for(j=0;j<width;j++){
				fscanf(file,"%d",&tmp);
		  		pixels[i][j].r=(unsigned char)tmp;
				pixels[i][j].g=(unsigned char)tmp;
				pixels[i][j].b=(unsigned char)tmp;
			}
		}

	}
	/** if magic number is P3
	*/
	else if(!strcmp(magic,"P3")){
		
		for(i = 0; i < height ; i++){
			for(j=0;j<width;j++){
				fscanf(file,"%d",&tmp);
		  		pixels[i][j].r=(unsigned char)tmp;
				fscanf(file,"%d",&tmp);
				pixels[i][j].g=(unsigned char)tmp;
				fscanf(file,"%d",&tmp);
				pixels[i][j].b=(unsigned char)tmp;
			}
		}

	}
	/** if magic number is P5
	*/
	else if(!strcmp(magic,"P5")){
		a=(unsigned char*)malloc(width*height*sizeof(unsigned char));
		fread(a,1,width*height,file);
		for(i=0;i<height;i++){
			for(j=0;j<width;j++){
				pixels[i][j].r=a[(i*width+j)];
				pixels[i][j].g=a[(i*width+j)];
				pixels[i][j].b=a[(i*width+j)];
			}
		}

	}
	/** if magic number is P6
	*/
	else if(!strcmp(magic,"P6")){
		a=(unsigned char*)malloc(width*height*3*sizeof(unsigned char));
		fread(a,1,width*height*3,file);
		for(i=0;i<height;i++){
			for(j=0;j<width;j++){
				pixels[i][j].r=a[(i*width+j)*3];
				pixels[i][j].g=a[(i*width+j)*3+1];
				pixels[i][j].b=a[(i*width+j)*3+2];
			}
		}
		

	} else {
		fputs("Error",stderr);
		return NULL;
	} 
	
	image = (jmpr_Image*)malloc(sizeof(jmpr_Image));
	image->w = width;
	image->h = height;
	printf("WAZZUPP");
	//printTest(pixels,height,width);
	printf("ENDEEEE");
	fclose(file);
	return image;
	

	
}


void jmpr_freeImage(jmpr_Image* img){
	
	
}

int main(int argc, char* argv[]){
	
	char* filename;
	jmpr_Image* image;
        SDL_Surface* surface;
        SDL_Window* window;
        SDL_Texture* texture;
        SDL_Renderer* renderer;
	
	filename = "/home/patrick/UniOsnabrück/c++/uebungen/uebung4/panorama2.pnm";
	printf("%s\n",filename);
	printf("MAIN1");
	image = jmpr_readImage(filename);
	printf("MAIN2");
        if((SDL_Init(SDL_INIT_VIDEO)) != 0){
        fprintf(stderr, "%s\n", SDL_GetError());
                return -1;
        }

        window = SDL_CreateWindow("TEST", 0, 0, 5390,1133, SDL_WINDOW_SHOWN);

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
        SDL_Quit();
	
	
	return 0;
}
