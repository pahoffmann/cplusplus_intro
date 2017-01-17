/*
 * Game.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: twiemann
 */

#include "Game.hpp"

#include <iostream>
using std::cout;
using std::endl;

namespace jumper
{

Game::Game(MainWindow* mainWindow)
{
	m_player = 0;
	m_level = 0;
	m_layer = 0;
	m_renderer = mainWindow->getRenderer();
	m_scoreBoard = 0;

	m_windowWidth = mainWindow->w();
	m_windowHeight = mainWindow->h();

	SDL_SetRenderDrawColor(m_renderer, 0, 102, 204, 255);
}

Game::~Game()
{
	// TODO Auto-generated destructor stub
}

void Game::setPlayer(Player* player)
{
	m_player = player;
	m_actors.push_back(player);
	m_renderables.push_back(player);
}

void Game::setLevel(Level* level)
{
	m_level = level;
	m_renderables.push_back(level);
}

void Game::addActor(Actor* actor)
{
	m_actors.push_back(actor);
	m_renderables.push_back(actor);
}

void Game::update(const Uint8* &currentKeyStates)
{
	// Reset forces and jump flags
	m_player->physics().setMoveForce(Vector2f(0.0, 0.0));
	m_player->wantsToJump(false);

	if( currentKeyStates[ SDL_SCANCODE_UP ] )
	{

	}
	if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
	{

	}
	if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
	{
		m_player->physics().setMoveForce(Vector2f(-800.0, 0.0));

	}
	if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
	{
		m_player->physics().setMoveForce(Vector2f(800.0, 0.0));
	}
	if( currentKeyStates[ SDL_SCANCODE_SPACE ])
	{
		m_player->wantsToJump(true);
	}

	SDL_RenderClear(m_renderer);

	if(m_layer)
	{
		m_layer->render();
	}

	if(m_scoreBoard)
	{
		m_scoreBoard->setScore(m_player->physics().position().x());
		m_scoreBoard->render();
	}

	for(size_t i = 0; i < m_renderables.size(); i++)
	{
		m_renderables[i]->render();
	}

	updateCameraPosition();

	// Update screen
	SDL_RenderPresent(m_renderer);

}

void Game::start()
{

}

void Game::updateCameraPosition()
{
	Renderable::m_camera.position().setX(m_player->position().x());
	Renderable::m_camera.position().setY(300);
}

} /* namespace jumper */

