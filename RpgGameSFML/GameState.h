#pragma once
#include "State.h"
#include "PauseMenu.h"
#include "CombatMenu.h"
#include "CharacterGUI.h"
#include "AnimationComponent.h"

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
	// Different menus
	PauseMenu* pauseMenu;
	CombatMenu* combatMenu;

	// Key for chosen character (mage or knight)
	std::string chosenCharacter;

	// Player character knight or mage
	PlayerCharacter* player;
	Enemy* boss;
	CharacterGUI* playerGUI;

	// Background loading
	std::string backgroundFile;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	// Timers for animation control
	float playerActionTimer;
	float playerActionTimerMax;
	float enemyActionTimer;
	float enemyActionTimerMax;
	float deathTimer;
	float deathTimeMax;

	// Timers for stalling animations
	const bool getPlayerActionTimer();
	const bool getEnemyActionTimer();
	const bool getDeathTimer();


	// Initialization Functions used to set default values and other important set ups for things like keybinds
	// and visual images
	virtual void initializeTextures() = 0;
	virtual void initializeBoss() = 0;
	void initializeKeybinds(std::string configFile);
	void initializeBackground(std::string backgroundFile);
	void initializePauseMenu();
	void initializeCombatMenu();
	void initializePlayer(unsigned playerLevel);
	void initializePlayerGUI();

public:
	// Constructor
	GameState(StateData* stateInfo, std::string playerType, unsigned playerLevel, std::string backgroundFile);

	// State Updating
	void updatePlayerGUI(const float& deltaTime);

	// Updates fuctions
	void updateInput(const float& deltaTime);
	void updateCombat(const float& deltaTime);
	virtual void updatePlayerInput(const float& deltaTime) = 0;
	virtual void updatePlayerActionTimer(const float& deltaTime);
	virtual void updateEnemyActionTime(const float& deltaTime);
	virtual void updateDeathTime(const float& deltaTime);
	virtual void updateState(const float& deltaTime) = 0;

	// State Rendering
	virtual void renderState(sf::RenderTarget* target = nullptr) = 0;

	// Destructor
	virtual ~GameState();
};