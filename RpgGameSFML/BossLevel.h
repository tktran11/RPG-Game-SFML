#pragma once
#include "GameState.h"
#include "MainMenuState.h"
#include "EndGameScreen.h"
#include "EnemyUI.h"

/*
BossLevel.h is the header for the boss level, which handles the resources for
the specific state. It houses textures, actions, combat, etc. for the main portion of the game.
*/

class BossLevel :
	public GameState
{
private:
	// Creates the boss's UI for the level
	EnemyUI* bossUI;

	// Boolean checks
	bool playerActed = false;
	bool bossDead;

public:
	// Constructor
	BossLevel(StateData* stateInfo, std::string playerType, unsigned playerLevel, 
		std::string backgroundFile = "MenuTextures/GameBackground/Map3.png");

	// Initializer functions
	void initializeTextures();
	void initializeBoss();
	void initializeBossUI();

	// Updates both menus
	void updatePauseMenuButtons();
	void updateCombatMenuButtons();

	// Updates other aspects of the state
	void updatePlayerInput(const float& deltaTime);
	void updateEnemyUI(const float& deltaTime);
	void updateState(const float& deltaTime);

	// Renders the state to the window
	void renderState(sf::RenderTarget* target = nullptr);
};