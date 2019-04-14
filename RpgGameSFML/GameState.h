#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "MainMenuState.h"
/*
GameState.h is the header for the Gamestate class, which handles the resources for
the specific state called GameState. It houses textures and such for the main portion of
the game.
*/
class GameState : public State
{
private:
	GraphicsSettings& graphicsSettings;
	PauseMenu* pauseMenu;
	// Key for chosen character (mage or knight)
	std::string chosenCharacter;
	// Player character knight or mage
	PlayerCharacter* player;

	// Initialization Functions used to set default values and other important set ups for things like keybinds
	// and visual images
	void initializeKeybinds();
	void initializeTextures();
	void initializePauseMenu();
	void initializePlayer();
public:
	// Constructor
	GameState(sf::RenderWindow* window, GraphicsSettings& graphics, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::string playerType);
	// Destructor
	virtual ~GameState();

	// Virtual Functions
	void updatePlayerInput(const float& deltaTime);
	void updatePauseMenuButtons();
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);
	void renderState(sf::RenderTarget* target = nullptr);
};

