#pragma once
#include "GameState.h"
#include "MainMenuState.h"
#include "EndGameScreen.h"
#include "EnemyUI.h"

class GolemLevel :
	public GameState
{
private:
	EnemyUI* bossUI;
	EnemyUI* minionUI1;
	EnemyUI* minionUI2;

	Enemy* minion1;
	Enemy* minion2;
	void initializeTextures();
	void initializeBoss();
	void initializeBossUI();
	void initializeMinions();
	void initializeMinionUI();
public:
	GolemLevel(StateData* stateInfo, std::string playerType, unsigned playerLevel,
		std::string backgroundFile = "MenuTextures/GameBackground/Map2.png");

	void updatePauseMenuButtons();
	void updatePlayerInput(const float& deltaTime);
	void updateEnemyUI(const float& deltaTime);
	void updateState(const float& deltaTime);

	void renderState(sf::RenderTarget* target = nullptr);
};

