#include <SDL2/SDL.h>
#include <string>
#include "Level.hh"

class MainWindow{



SDL_Window* 	pWindow;
SDL_Renderer*	pRenderer;
Level *myLevel;

public:
	MainWindow(std::string title, int w, int h);
	~MainWindow();
	void mainLoop();
	SDL_Renderer* getRenderer();
	void setLevel(Level* level);
	
	

};