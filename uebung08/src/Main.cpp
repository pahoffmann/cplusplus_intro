#include "MainWindow.hpp"
#include "Level.hpp"
// #include "Player.hpp" <-- Unkomment me!

#include <iostream>


using namespace jumper;

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		std::cout << "Please specify a level and a sprite to render" << std::endl;
		return -1;
	}

	MainWindow window("Jumper", 800, 600);
	Level level(window.getRenderer(), std::string(argv[1]));
	window.setLevel(&level);

/* Unomment me! 
	Player player(std::string(argv[2], window.getRenderer());
	window.setPlayer(&player);
*/
	window.run();
}
