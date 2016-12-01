#include "MainWindow.hh"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>



/**
* @brief initializes window and Renderer
* @param title title of the window
* 		 w width of window
*		 h height of window
*/
MainWindow::MainWindow(std::string title, int w, int h) {
	pWindow = 0;
	pRenderer = 0;
	
	
	/* Init SDL */
	if(SDL_Init( SDL_INIT_VIDEO ) < 0)
	{
		std::cout << "SDL could not initialize: " << SDL_GetError() << std::endl;
	}

	/* Generate SDL main window */
	pWindow = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			w,
			h,
			SDL_WINDOW_SHOWN );

	if(pWindow == NULL)
	{
		std::cout << "SDL window could not be generated: " << SDL_GetError() << std::endl;
	}

	/* Create renderer for the SDL main window */
	pRenderer = SDL_CreateRenderer( pWindow, -1, SDL_RENDERER_ACCELERATED );

	if(pRenderer == NULL)
	{
		std::cout << "SDL could not generate renderer: " << SDL_GetError() << std::endl;
	}

	 //Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
	}


	/* Set background color for renderer */
	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 0);
	
	
}

/**
 * @brief returns the renderer
 */
SDL_Renderer* MainWindow::getRenderer(){
	return pRenderer;
}


/**
*	@brief opens a window and renders it
*/
void MainWindow::mainLoop(){
	SDL_Event e;
	int quit = 0;
	Camera cam;
	
	
	
	while(!quit)
	{
		/* Processs events, detect quit signal for window closing */
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				quit = 1;
			}
			
			if(e.type == SDL_KEYDOWN){
				
				if(e.key.keysym.sym == SDLK_UP){
					cam.moveY(-5);
					myLevel->render(cam);
				}
				
				if(e.key.keysym.sym == SDLK_DOWN){
					cam.moveY(5);
					myLevel->render(cam);
				}
				
				if(e.key.keysym.sym == SDLK_LEFT){
					cam.moveX(-5);
					myLevel->render(cam);
				}
				
				if(e.key.keysym.sym == SDLK_RIGHT){
					cam.moveX(5);
					myLevel->render(cam);
				}
			}
		}
		
		/* Clear screen */
		SDL_RenderClear( pRenderer );
		
		myLevel->render(cam);
			
		
		/* Update screen */
		SDL_RenderPresent( pRenderer );
	}
	
	

	SDL_DestroyRenderer(pRenderer);
	pRenderer = NULL;

	SDL_DestroyWindow(pWindow);
	pWindow = NULL;

	IMG_Quit();
	SDL_Quit();
	
}

MainWindow::~MainWindow(){
	
}

void MainWindow::setLevel(Level* level){
	
	myLevel = level;
	
}
