#pragma once
#include "GameState.h"
#include "MainMenuState.h"
#include "EndGameScreen.h"
#include "EnemyUI.h"
#include "BossLevel.h"

/*
Golemlevel.h is the header for the golem level, which handles the resources for
the specific state. It houses textures, actions, combat, etc. for the main portion of the game.
*/

class GolemLevel :
	public GameState
{
private:
	// Creates enemies with their respective UI and buttons for the level
	EnemyUI* bossUI;
	EnemyUI* minionUI1;
	EnemyUI* minionUI2;

	Enemy* minion1;
	Enemy* minion2;

	gui::Button* nextLevel;

	// Boolean checks
	bool playerActed = false;
	bool allDead = false;
	bool bossDead = false;
	bool minion1Dead = false;
	bool minion2Dead = false;

public:
	// Constructor
	GolemLevel(StateData* stateInfo, std::string playerType, unsigned playerLevel,
		std::string backgroundFile = "MenuTextures/GameBackground/Map2.png");

	// Initializer functions
	void initializeTextures();
	void initializeBoss();
	void initializeBossUI();
	void initializeMinions();
	void initializeMinionUI();
	void initializeNextLevelButton();

	// Updates both menus
	void updatePauseMenuButtons();
	void updateCombatMenuButtons();

	// Updates other aspects of the state
	void updateNextLevelButton();
	void updatePlayerInput(const float& deltaTime);
	void updateEnemyUI(const float& deltaTime);
	void updateState(const float& deltaTime);

	// Renders the state to the window
	void renderState(sf::RenderTarget* target = nullptr);
};