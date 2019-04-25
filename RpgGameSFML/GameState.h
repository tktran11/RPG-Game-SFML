#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "MainMenuState.h"
#include "CharacterGUI.h"
/*
GameState.h is the header for the Gamestate class, which handles the resources for
the specific state called GameState. It houses textures and such for the main portion of
the game.
*/

// Forward Declarations
class PauseMenu;
class PlayerCharacter;
class CharacterGUI;

class GameState : public State
{
private:
	PauseMenu* pauseMenu;
	// Key for chosen character (mage or knight)
	std::string chosenCharacter;
	// Player character knight or mage
	PlayerCharacter* player;
	Enemy* enemy1;
	Enemy* enemy2;
	Enemy* enemy3;
	CharacterGUI* playerGUI;

	std::string backgroundFile;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	// Initialization Functions used to set default values and other important set ups for things like keybinds
	// and visual images
	void initializeKeybinds();
	void initializeTextures();
	void initializeBackground(std::string backgroundFile);
	void initializePauseMenu();
	void initializePlayer(unsigned playerLevel);
	void initializeShade();
	void initializeSlime();
	void initializePlayerGUI();
public:
	// Constructor
	GameState(StateData* stateInfo, std::string playerType, unsigned playerLevel,  std::string backgroundFile = "MenuTextures/GameBackground/Map1.png");

	// State Updating
	void updatePlayerInput(const float& deltaTime);
	void updatePlayerGUI(const float& deltaTime);
	void updatePauseMenuButtons();
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);

	// State Rendering
	void renderState(sf::RenderTarget* target = nullptr);

	// Destructor
	virtual ~GameState();

};

