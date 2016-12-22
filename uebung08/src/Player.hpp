#ifndef SRC_PLAYER_
#define SRC_PLAYER_

#include "AnimatedRenderable.hpp"
#include "Pixel.hpp"
#include <string>
#include <SDL2/SDL.h>

class Player : public AnimatedRenderable{


private:
	
	int animationLevels;
	int actLevel;
	inline int numberOfLevels();
	inline int actLevelNumber();
	inline void increaseLevel();


public:

	/* constr. */
	Player();
	Player(Player& other);
	Player(SDL_Renderer* renderer, std::string filename);	
	
	/* METHODS */
	

	/* Player movement */
	void move (Pixel& offset);
	void render();
	

	
	/* OPERATORS */
	Player& operator = (const Player& other);
	
	

	///destr.
	~Player();

};

#endif /* SRC_PLAYER_ */
