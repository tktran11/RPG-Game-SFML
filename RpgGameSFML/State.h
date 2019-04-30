#pragma once
#include "PlayerCharacter.h"
#include "Enemy.h"
#include "Knight.h"
#include "Mage.h"
#include "Shade.h"
#include "Slime.h"
#include "IceGolem.h"
#include "StoneGolem.h"
#include "FireGolem.h"
#include "Minotaur.h"
#include "GraphicsSettings.h"
/*
State.h is the header for the state class, which handles the resources for
each game state. It houses textures and such for each menu or screen. 
Each state is essentially a screen in the game and its encapuslated logic and
graphics
*/

// Forward Declarations (tells compiler that this thing exists to save compile time), used like function prototypes
class Player;
class GraphicsSettings;
class State;

class StateData
{
public:
	StateData() {};

	//Variables
	sf::RenderWindow* gameWindow;
	GraphicsSettings* graphicsSettings;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
};

// Beginning of the State class
class State
{
protected:

	// State Stack to keep track of all the possible states that the game has, top state is the one in use
	std::stack<State*>* states;
	// State Data Holder
	StateData* stateInfo;

	// Variables for single state management 
	bool askedForQuit;
	bool isPaused;
	bool isInCombat;
	float keyboardTimer;
	float maxKeyboardTime;

	// Pointer to game window
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
	virtual void initializeKeybinds(std::string configFile) = 0;

public:
	// Constructor
	State(StateData* stateInfo);

	// Assessor for 
	const bool& getQuit() const;
	const bool getKeyboardTimer();
	// State Handling
	void pauseState();
	void unPauseState();
	void endState();
	void enterCombatState();
	void exitCombatState();

	// Virtual Functions for State Input and Management
	virtual void updateMousePositions();
	virtual void updateInput(const float& deltaTime) = 0;
	virtual void updateKeyboardtime(const float& deltaTime);
	virtual void updateState(const float& deltaTime) = 0;
	virtual void renderState(sf::RenderTarget* target = nullptr) = 0;
};

