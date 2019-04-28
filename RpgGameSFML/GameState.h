#pragma once
#include "State.h"
#include "PauseMenu.h"
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
protected:
	PauseMenu* pauseMenu;
	// Key for chosen character (mage or knight)
	std::string chosenCharacter;
	// Player character knight or mage
	PlayerCharacter* player;
	Enemy* boss;
	CharacterGUI* playerGUI;

	std::string backgroundFile;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	// Initialization Functions used to set default values and other important set ups for things like keybinds
	// and visual images

	virtual void initializeTextures() = 0;
	virtual void initializeBoss() = 0;
	void initializeKeybinds(std::string configFile);
	void initializeBackground(std::string backgroundFile);
	void initializePauseMenu();
	void initializePlayer(unsigned playerLevel);
	void initializePlayerGUI();
public:
	// Constructor
	GameState(StateData* stateInfo, std::string playerType, unsigned playerLevel, std::string backgroundFile);

	// State Updating
	void updatePlayerGUI(const float& deltaTime);
	void updateInput(const float& deltaTime);
	virtual void updatePlayerInput(const float& deltaTime) = 0;
	virtual void updateState(const float& deltaTime) = 0;

	// State Rendering
	virtual void renderState(sf::RenderTarget* target = nullptr) = 0;

	// Destructor
	virtual ~GameState();

};

