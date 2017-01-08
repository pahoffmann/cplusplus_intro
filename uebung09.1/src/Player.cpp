//
// Created by isaak on 26.11.15.
//


#include "Player.hpp"
namespace jumper
{

Player::Player(SDL_Renderer *renderer, std::string filename)
	: AnimatedRenderable(renderer, filename)
{

	m_position.setX(100);
	m_position.setY(100);
}

void Player::render()
{
    SDL_Rect target;
    SDL_RendererFlip flip;
    if(0)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else
    {
        flip = SDL_FLIP_NONE;
    }

    target.x = m_position.x();
    target.y = m_position.y();
    target.w = m_frameWidth;
    target.h = m_frameHeight;

    /* Render current animation frame */
    SDL_RenderCopyEx( getRenderer(), m_texture, &m_sourceRect, &target, 0, NULL, flip);
}

Vector2f Player::position()
{
    return m_position;
}

void Player::move(int direction, float speed)
{
    switch(direction)
    {

        case UP 	:
            m_position += Vector2f(0, -speed);   break;
        case DOWN	:
            m_position += Vector2f(0, speed);    break;
        case LEFT	:
            m_position += Vector2f(-speed, 0);   break;
        case RIGHT  :
            m_position += Vector2f(speed, 0);    break;
    }
    nextFrame();
}

void Player::setPosition(Vector2f pos)
{
    m_position = pos;
}

}
