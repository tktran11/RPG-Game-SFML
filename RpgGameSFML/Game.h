#pragma once
#include "TitleScreenState.h"


/*
Game.h is the header for the Game class, which handles the overall window. 
It checks for updates to the window and loads any changes.
*/
class Game
{
private:
	// Variables

	sf::RenderWindow *gameWindow;
	sf::Event event;
	GraphicsSettings graphicsSettings;
	StateData stateData;

	// Delta Time for making gameplay framerate independant
	sf::Clock deltaClock;
	float deltaTime;

	// State Management

	std::stack<State*> states;

	// Map for supported keys, stores key name and SFML reference number
	std::map<std::string, int> supportedKeys;

	//Window and Game Initializations

	void startWindow();
	void startStates();
	void initializeStateData();
	void initializeGraphicsSettings();
	void initializeVariables();
	void initializeKeyboard();
	
public:

	// Constructor

	Game();

	// Updates

	void updateDeltaTime();
	void updateEvents();
	void updateGame();

	// Rendering to the Game

	void renderToWindow();
	void runGame();

	// Virtual Destructor
	virtual ~Game();
};


