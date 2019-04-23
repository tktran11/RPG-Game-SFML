#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "MainMenuState.h"
/*
CombatState.h is the header for the CombatState class, which handles the resources for
the specific state called CombatState. It houses textures and such for the main portion of
the game.
*/
class CombatState :	public State
{
private:
	PauseMenu* pauseMenu;
	// Key for chosen character (mage or knight)
	std::string chosenCharacter;
	// Player character knight or mage
	PlayerCharacter* player;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	// Initialization Functions used to set default values and other important set ups for things like keybinds
	// and visual images
	void initializeKeybinds();
	void initializeTextures();
	void initializeBackground();
	void initializePauseMenu();
	void initializePlayer();
	void initializeEnemy();
public:
	// Constructor
	CombatState(StateData* stateInfo, std::string playerType);
	// Destructor
	virtual ~CombatState();
	
	// Virtual Functions
	void updatePlayerInput(const float& deltaTime);
	void updatePauseMenuButtons();
	//void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);
	void renderState(sf::RenderTarget* target = nullptr);
};

