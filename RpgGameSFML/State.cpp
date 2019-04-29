#include "stdafx.h"
#include "State.h"
#include "math.h"

/*
State.cpp is the body for the state class, which handles the resources for
each game state. It houses textures and such for each menu or screen.
Each state is essentially a screen in the game and its encapuslated logic and
graphics
*/

// Constructor for the State Class, initializes its general features
State::State(StateData* stateInfo)
{
	this->stateInfo = stateInfo;
	this->window = stateInfo->gameWindow;
	this->supportedKeys = stateInfo->supportedKeys;
	this->states = stateInfo->states;
	this->isPaused = false;
	this->askedForQuit = false;
	this->keyboardTimer = 0.f;
	this->maxKeyboardTime = 20.f;
	this->deathTimer = 0.f;
	this->deathTimeMax = 9.f;
	
}

// Returns the state's askedForQuit, indicating if the state has shown it should transition to the next state
const bool & State::getQuit() const
{
	return this->askedForQuit;
}

// Key Timer so that one key press doesn't register on more than one state at a time
const bool State::getKeyboardTimer()
{
	if (this->keyboardTimer >= this->maxKeyboardTime)
	{
		this->keyboardTimer = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

const bool State::getDeathTimer()
{
	if (this->deathTimer >= this->deathTimeMax)
	{
		this->deathTimer = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

// pauseState() is for the pause screen ill be finishing or flusing out later
void State::pauseState()
{
	this->isPaused = true;
}

void State::unPauseState()
{
	this->isPaused = false;
}

void State::endState()
{
	this->askedForQuit = true;
}

// updateMousePositions() checks the position of the mouse 
void State::updateMousePositions()
{
	this->mousePositScreen = sf::Mouse::getPosition();
	this->mousePositWindow = sf::Mouse::getPosition(*this->window);
	this->mousPositView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

// Reset and keytime based on deltaTime
void State::updateKeyboardtime(const float& deltaTime)
{
	if (this->keyboardTimer < this->maxKeyboardTime)
	{
		this->keyboardTimer += 100.f * deltaTime;
	}
}

// Timer to control how fast death animations happen in a state
void State::updateDeathTime(const float & deltaTime)
{
	if (this->deathTimer < this->deathTimeMax)
	{
		this->deathTimer += 100.f * deltaTime;
	}
}



