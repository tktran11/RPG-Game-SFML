#pragma once
#include "GameState.h"
#include "MainMenuState.h"
#include "EndGameScreen.h"
#include "EnemyUI.h"

class SlimeLevel :
	public GameState
{
private:
	EnemyUI* bossUI;
	EnemyUI* minionUI;

	Enemy* minion1;
	Enemy* minion2;
public:
	SlimeLevel(StateData* stateInfo, std::string playerType, unsigned playerLevel, std::string backgroundFile = "MenuTextures/GameBackground/Map1.png");
	
	void initializeTextures();
	void initializeBoss();
	void initializeMinions();
	void initializeBossUI();
	void initializeMinionUI();

	void updatePauseMenuButtons();
	void updatePlayerInput(const float& deltaTime);
	void updateEnemyUI(const float& deltaTime);
	void updateState(const float& deltaTime);

	void renderState(sf::RenderTarget* target = nullptr);
};

