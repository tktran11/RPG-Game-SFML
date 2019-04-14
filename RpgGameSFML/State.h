#pragma once
#include "PlayerCharacter.h"
#include "GraphicsSettings.h"

/*
State.h is the header for the state class, which handles the resources for
each game state. It houses textures and such for each menu or screen. 
Each state is essentially a screen in the game and its encapuslated logic and
graphics
*/

class State
{
protected:

	// State Stack to keep track of all the possible states that the game has, top state is the one in use
	std::stack<State*>* states;

	// Variables for single state management 
	
	bool askedForQuit;
	bool isPaused;
	float keyboardTimer;
	float maxKeyboardTime;
	sf::RenderWindow* window;

	// Storage for input and visual features

	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keyBinds;
	std::map<std::string, sf::Texture> stateTextures;

	// SFML Mouse Monitoring

	sf::Vector2i mousePositScreen;
	sf::Vector2i mousePositWindow;
	sf::Vector2f mousPositView;

	// Needed to initialize keybinds
	virtual void initializeKeybinds() = 0;

public:
	// Constructor
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);

	// Assessor for 
	const bool& getQuit() const;
	const bool getKeyboardTimer();
	
	void pauseState();
	void unPauseState();
	void endState();

	// Virtual Functions for State Input and Management
	virtual void updateMousePositions();
	virtual void updateInput(const float& deltaTime) = 0;
	virtual void updateKeyboardtime(const float& deltaTime);
	virtual void updateState(const float& deltaTime) = 0;
	virtual void renderState(sf::RenderTarget* target = nullptr) = 0;
};

