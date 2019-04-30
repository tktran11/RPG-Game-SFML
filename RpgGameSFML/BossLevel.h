#pragma once
#include "GameState.h"
#include "MainMenuState.h"
#include "EndGameScreen.h"
#include "EnemyUI.h"

class BossLevel :
	public GameState
{
private:
	EnemyUI* bossUI;

	// Boolean checks
	bool playerActed = false;
	bool bossDead;
public:
	BossLevel(StateData* stateInfo, std::string playerType, unsigned playerLevel, 
		std::string backgroundFile = "MenuTextures/GameBackground/Map3.png");

	void initializeTextures();
	void initializeBoss();
	void initializeBossUI();

	void updatePauseMenuButtons();
	void updateCombatMenuButtons();

	void updatePlayerInput(const float& deltaTime);
	void updateEnemyUI(const float& deltaTime);
	void updateState(const float& deltaTime);

	void renderState(sf::RenderTarget* target = nullptr);
};

