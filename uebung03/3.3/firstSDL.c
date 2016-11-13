#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


printUsage(){
	printf("Ungültige Eingabe!\n");
	printf("Bitte [min_size] [max_size] [n] als parameter angeben!\n");
	printf("n*max_size darf 600 nicht überschreiten!\n");
	printf("es müssen n werte zwischen min und max passen!\n");
}


//random values
randomValues(SDL_Rect array[],int min, int max, int n){
	int i;
	SDL_Rect rect;
	for(i=0;i<n;i++){
		rect.w = (int)(double)min+(double)(max-min)*((double)rand()/RAND_MAX);
		usleep(1000);
		rect.h = (int)(double)min+(double)(max-min)*((double)rand()/RAND_MAX);
		array[i]=rect;
		usleep(1000);
	}
}
printArray(SDL_Rect array[],int n){
	int i;
	for(i=0;i<n;i++){
	 	printf("%d | %d , ",array[i].w,array[i].h);
	}
	printf("\n");
}

printArray1(SDL_Rect array[],int n){
	int i;
	for(i=0;i<n;i++){
	 	printf("%d | %d , ",array[i].x,array[i].y);
	}
	printf("\n");
}

int cmpfunc ( const void * a, const void *b){
	SDL_Rect *rectA = (SDL_Rect *)a;
	SDL_Rect *rectB = (SDL_Rect *)b;
	return ( rectA->w-rectB->w );
}

getX(SDL_Rect rect[],int n){
	int i;
	for(i=0;i<n; i++){
		rect[i].x = SCREEN_WIDTH/2-rect[i].w/2;
	}
}

getY(SDL_Rect rect[],int n){
	int i;
	int j;
	int sum=0;
	rect[0].y = 0; 
	for(i=0;i<n;i++){
		for(j=0;j<i;j++){
			sum+=rect[j].h;
		}
		rect[i].y=sum;
		sum=0;
	}
	
}

rendering(SDL_Rect rect[],int n,SDL_Renderer* renderer){
	int i;
	for(i=0;i<n;i++){
		SDL_RenderDrawRect(renderer,&rect[i]);
	}
}



int main(int argc, char* argv[]){
	

	//variables
  	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
 	int i; 
	int min_size;
	int max_size;
	struct timeval time;
	gettimeofday(&time,NULL);

	srand((time.tv_sec * 1000) + (time.tv_usec / 1000));


	//getting parameters + checking
	if(argc!=4){
		printUsage();
		return 1;
	}
	min_size = strtol(argv[1],NULL,10);
	max_size = strtol(argv[2],NULL,10);
	const int n = strtol(argv[3],NULL,10);	


	
	if(min_size > max_size || n > max_size - min_size || max_size > 800 || max_size <0 || min_size < 0 || n*max_size > SCREEN_HEIGHT){
		printUsage();
		return 1;
	}


  	if( SDL_Init(SDL_INIT_VIDEO) < 0){
    		printf("Mistake! SDL_Error: %s\n",SDL_GetError());
	}else{
		window = SDL_CreateWindow("SDL-Klötzchen",0,0,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
		if(window == NULL){
			printf("Mistake at creating Window! SDL_Errror: %s\n",SDL_GetError());
		}
	}
	
	
	SDL_Rect rect[n];

	randomValues(rect,min_size,max_size,n);
	printArray(rect,n);
        //quicksorting arrays
	qsort(rect, n , sizeof(SDL_Rect), cmpfunc);
       	getX(rect,n);
	getY(rect,n);
	printArray(rect,n);
	printArray1(rect,n);
        //creating renderer
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer,0,255,0,255);
	rendering(rect,n,renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(10000);
	//SDL_UpdateWindowSurface(window);
	//SDL_Delay(2000);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("cookie!\n");

	return 0;

		

			
	
  


}
