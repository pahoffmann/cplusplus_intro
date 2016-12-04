#include "MainWindow.hh"

int main(int argc, char* argv[]){
	MainWindow window("VisualCam",1200,800);
	Level level(window.getRenderer(),argv[1]);
	window.setLevel(&level);
	window.mainLoop();
	
	return 0;	
}
