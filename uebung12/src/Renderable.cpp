//
// Created by isaak on 25.11.15.
//

#include <SDL_image.h>
#include <iostream>

using std::cout;
using std::endl;

#include "Renderable.hpp"
namespace jumper
{

Camera Renderable::m_camera;

Renderable::Renderable(SDL_Renderer* renderer)
	: m_renderer(renderer), m_texture(0)
{
	m_sourceRect.x = 0;
	m_sourceRect.y = 0;
	m_sourceRect.w = 0;
	m_sourceRect.h = 0;
}

Renderable::Renderable(SDL_Renderer* renderer, SDL_Texture* texture)
	: m_renderer(renderer), m_texture(texture)
{
	int w, h;
	SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);

	m_sourceRect.x = 0;
	m_sourceRect.y = 0;
	m_sourceRect.w = w;
	m_sourceRect.h = h;
}

void Renderable::shiftTargetRect(SDL_Rect& r)
{
	r.x = r.x - m_camera.position().x() + m_camera.w() / 2;
	r.y = r.y - m_camera.position().y() + m_camera.h() / 2;
}

void Renderable::shiftPosition(int& x, int& y)
{
	x = x - m_camera.position().x() + m_camera.w() / 2;
	y = y - m_camera.position().y() + m_camera.h() / 2;
}

SDL_Renderer *Renderable::getRenderer() const
{
    return m_renderer;
}

SDL_Texture *Renderable::loadTexture(std::string texFileName,
                                     unsigned char keyR,
                                     unsigned char keyG,
                                     unsigned char keyB)
{
	// The loaded texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(texFileName.c_str());
    if( loadedSurface == NULL )
    {
        std::cout << "Unable to load image! SDL_image Error: " <<  IMG_GetError() << std::endl;
    }
    else
    {
        // Set keying color
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, keyR, keyG, keyB) );

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(getRenderer(), loadedSurface );
        if( newTexture == NULL )
        {
            std::cout <<  "Unable to create texture from! SDL Error: " << texFileName <<  SDL_GetError() << std::endl;
        }

        // Query texture to get width and height
        Uint32 format;
        int access, w, h;
        SDL_QueryTexture(newTexture, &format, &access, &w, &h);

        m_sourceRect.w = w;
        m_sourceRect.h = h;


        // Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}


SDL_Texture *Renderable::loadTexture(std::string texFileName)
{
    // The loaded texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(texFileName.c_str());
    if( loadedSurface == NULL )
    {
        std::cout << "Unable to load image! SDL_image Error: " <<  IMG_GetError() << std::endl;
    }
    else
    {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(getRenderer(), loadedSurface );
        if( newTexture == NULL )
        {
            std::cout <<  "Unable to create texture from! SDL Error: " << texFileName <<  SDL_GetError() << std::endl;
        }

        // Query texture to get width and height
        Uint32 format;
        int access, w, h;
        SDL_QueryTexture(newTexture, &format, &access, &w, &h);

        m_sourceRect.w = w;
        m_sourceRect.h = h;


        // Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

int Renderable::w() const
{
	return m_sourceRect.w;
}

int Renderable::h() const
{
	return m_sourceRect.h;
}


} /* namespace jumper */

