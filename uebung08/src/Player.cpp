#include "Player.hpp"
#include <iostream>
#include <fstream>

Player::Player() : AnimatedRenderable() {
	animationLevels = 0;
	actLevel = 0;
}
Player::Player(Player& other) : AnimatedRenderable(other){

		this->animationLevels = other.animationLevels;
	
}
Player::Player(SDL_Renderer* renderer, std::string filename) : AnimatedRenderable(renderer){
	
	std::string texFileName;
	pos.setX(300);
	pos.setY(300);	
		
	
	std::ifstream in(filename.c_str());
	if(!in.good()){			
		std::cout << "Player: Unable to open file " << filename << std::endl;
		exit(1);	
	}
	
	in >> texFileName;
	in >> width;
	in >> height;
	in >> animationLevels;
	
	texture = loadTexture(texFileName);
 		
}


  
/* METHODS */


/* Player movement */
void Player::move (Pixel& offset){
	
	static int i = 0;
	pos += offset;
	if(i==15){
		increaseLevel();
		i=0;
	}
	i++;
	
	
}
void Player::render(){
	SDL_Rect target;
	SDL_Rect source;

	target.w = width;
	target.h = height;
	
	source.w = width;
	source.h = height;

	target.x = pos.x();
	target.y = pos.y();

	source.x = actLevel * width;
	source.y = 0;
	SDL_RenderCopy(renderer, texture, &source, &target);
	//SDL_Delay(10);
}



int Player::numberOfLevels(){
	return animationLevels;
}

int Player::actLevelNumber(){
	return actLevel;
}
void Player::increaseLevel(){
	if(actLevelNumber() < numberOfLevels()-1){
		actLevel++;
	}else{
		actLevel = 0;
	}
}




/* OPERATORS */

Player& Player::operator=(const Player& other){
	if(this != &other){
		this->animationLevels = other.animationLevels;
		this->actLevel = other.actLevel;
		copy(other);	
	}
	return *this;		
}


///destr.
Player::~Player(){
	//nothing here
}


