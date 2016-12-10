#include "MainWindow.hpp"



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
	const Uint8* currentKeyStates;
	Pixel offset1(-1,0);
	Pixel offset2(1,0);
	Pixel offset3(0,-1);
	Pixel offset4(0,1);
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
	    }	

	    currentKeyStates = SDL_GetKeyboardState( NULL );

 	  	if( currentKeyStates[ SDL_SCANCODE_UP ] )
	  	{
       	   		cam.move(offset4);
         	}
		if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
		{
			cam.move(offset3);
		}
		if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
		{
			cam.move(offset2);
		}
		if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
		{
			cam.move(offset1);
		}	
	    

            /* Clear screen */
            SDL_RenderClear( renderer );


           /* Render tiles and sprite */
           levelX->render(cam);
	   /* Update screen */
	   SDL_Delay(10);
           SDL_RenderPresent( renderer );
        }
	
	
	


	
}


// Frees all resources
MainWindow::~MainWindow(){



	SDL_DestroyRenderer(renderer);
        renderer = NULL;

        SDL_DestroyWindow(window);
        window = NULL;

        IMG_Quit();
        SDL_Quit();

}

void MainWindow::setLevel(Level* level){
	levelX=level;
}


