#include <SDL2/SDL.h>
#include <string>
#include "Level.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>


class MainWindow{
	SDL_Renderer* renderer;
	SDL_Window* window;
	Level* levelX;

public:
	// Erstellt ein Hauptfenster mit Title title, width w und height h
	MainWindow(std::string tile, int w, int h);
		
		
	// Returns a pointer to the internal SDL-Renderer
	SDL_Renderer* getRenderer();
	
	// Main loop: Renders contends and handles events
	void mainLoop();
	
	void setLevel(Level* level);

	// Frees all resources
	~MainWindow();
};
