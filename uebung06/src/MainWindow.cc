#include "MainWindow.hh"



// Erstellt ein Hauptfenster mit Title title, width w und height h
MainWindow::MainWindow(std::string title, int w, int h){	
	renderer = 0; /*initialize private variable*/
	window = 0;
	
	/* Init SDL */
        if(SDL_Init( SDL_INIT_VIDEO ) < 0)
        {
                std::cout << "SDL could not initialize: " << SDL_GetError() << std::endl;
                exit(1);
        }

        /* Generate SDL main window */
        window = SDL_CreateWindow(
                        title.c_str(),
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        w,
                        h,
                        SDL_WINDOW_SHOWN );

        if(window == NULL)
        {
                std::cout << "SDL window could not be generated: " << SDL_GetError() << std::endl;
                exit(1);
        }

        /* Create renderer for the SDL main window */
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

        if(renderer == NULL)
        {
                std::cout << "SDL could not generate renderer: " << SDL_GetError() << std::endl;
                exit(1);
        }
         
         //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {       
                std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                exit(1);
        }


        /* Set background color for renderer */
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		


	

}


// Returns a pointer to the internal SDL-Renderer
SDL_Renderer* MainWindow::getRenderer(){
	return renderer;
}


// Main loop: Renders contends and handles events
void MainWindow::mainLoop(){
	int quit = 0;
	SDL_Event e;
	
	Camera cam;        

	/* Start main loop and event handling */
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
                                levelX->render(cam);
                        }

                        if(e.key.keysym.sym == SDLK_DOWN){
                	        cam.moveY(5);
                                levelX->render(cam);
                        }

                        if(e.key.keysym.sym == SDLK_LEFT){
                      		cam.moveX(-5);
                                levelX->render(cam);
                        }

                        if(e.key.keysym.sym == SDLK_RIGHT){
                        	cam.moveX(5);
                                levelX->render(cam);
                        }
                  }
	    }

            /* Clear screen */
            SDL_RenderClear( renderer );


           /* Render tiles and sprite */
           levelX->render(cam);
	   /* Update screen */
           SDL_RenderPresent( renderer );
        }
	
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	
	SDL_DestroyWindow(window);
	window = NULL;
	
	IMG_Quit();
	SDL_Quit();


	
}


// Frees all resources
MainWindow::~MainWindow(){


}
void MainWindow::setLevel(Level* level){
	levelX=level;
}
