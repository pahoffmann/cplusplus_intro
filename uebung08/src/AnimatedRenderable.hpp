#include "Renderable.hpp"
#include "string"

class AnimatedRenderable : public Renderable{

public:
	AnimatedRenderable();
	AnimatedRenderable(SDL_Renderer* renderer);
	AnimatedRenderable(SDL_Renderer* renderer, std::string filename);
	AnimatedRenderable(AnimatedRenderable& other);
	//~AnimatedRenderable();
	void render();
	

};
