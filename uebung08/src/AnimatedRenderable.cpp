#include "AnimatedRenderable.hpp"
	
	//default konstruktor
	AnimatedRenderable::AnimatedRenderable(): Renderable(){}
	//one arg constr.
	AnimatedRenderable::AnimatedRenderable(SDL_Renderer* renderer) : Renderable(renderer) {}
	//two arg constr.
	AnimatedRenderable::AnimatedRenderable(SDL_Renderer *renderer, std::string filename) : Renderable(renderer, filename){}
	
	AnimatedRenderable::AnimatedRenderable(AnimatedRenderable& other): Renderable(other) {}
	//destr.
	/*AnimatedRenderable::~AnimatedRenderable(){
		Renderable::~Renderable();
	}*/
	void AnimatedRenderable::render(){}
