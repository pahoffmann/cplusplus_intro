#include <SDL2/SDL.h>
#include "MainWindow.hh"


int main(int argc, char* argv[]){
	
	
	MainWindow mainwin("Test Window", 800, 600);
	
	Level level(mainwin.getRenderer(), argv[1]);
	mainwin.setLevel(&level);
	mainwin.mainLoop();
	
	return 0;
}