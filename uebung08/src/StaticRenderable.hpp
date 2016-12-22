#include "Renderable.hpp"
#include "string"

class StaticRenderable : public Renderable{

public:
	StaticRenderable();
	StaticRenderable(SDL_Renderer* renderer);
	StaticRenderable(SDL_Renderer* renderer, std::string filename);
	//~StaticRenderable();
	void render();

		

};
