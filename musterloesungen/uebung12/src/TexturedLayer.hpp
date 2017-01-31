/*
 * TexturedLayer.hpp
 *
 *  Created on: Jan 2, 2016
 *      Author: twiemann
 */

#ifndef SRC_TEXTUREDLAYER_HPP_
#define SRC_TEXTUREDLAYER_HPP_

#include "StaticRenderable.hpp"

namespace jumper
{

/// A class to represent a layer that is repeatedly rendered in the background
class TexturedLayer: public StaticRenderable
{
public:

	/// Creates a layer for the given renderer
	TexturedLayer(SDL_Renderer* renderer);

	/// Creates a layer for the given renderer from the given file
	TexturedLayer(SDL_Renderer* renderer, SDL_Texture* texture);

	/// Renders the layer
	virtual void render();

	/// Destructor
	virtual ~TexturedLayer();

	/// Sets the scroll speed of the layer
	void setScrollSpeed(float speed);

protected:

	/// Scrolling speed
	float		m_scrollSpeed;
};

} /* namespace jumper */

#endif /* SRC_TEXTUREDLAYER_HPP_ */
