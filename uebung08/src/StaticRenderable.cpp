#include "StaticRenderable.hpp"
	
	//default konstruktor
	StaticRenderable::StaticRenderable(): Renderable(){}
	//one arg constr.
	StaticRenderable::StaticRenderable(SDL_Renderer* renderer) : Renderable(renderer) {}
	//two arg constr.
	StaticRenderable::StaticRenderable(SDL_Renderer *renderer, std::string filename) : Renderable(renderer, filename){}
	//destr.
	/*StaticRenderable::~StaticRenderable(){
		Renderable::~Renderable();
	}*/
	void StaticRenderable::render(){}
