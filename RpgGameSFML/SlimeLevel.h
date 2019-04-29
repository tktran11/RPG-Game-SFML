#pragma once
#include "GameState.h"
#include "MainMenuState.h"
#include "EndGameScreen.h"
#include "GolemLevel.h"
#include "EnemyUI.h"

class SlimeLevel :
	public GameState
{
private:
	gui::Button* nextLevel;
	EnemyUI* bossUI;
	EnemyUI* minionUI1;
	EnemyUI* minionUI2;

	Enemy* minion1;
	Enemy* minion2;

	bool allDead = false;
	bool bossDead = false;
	bool minion1Dead = false;
	bool minion2Dead= false;
public:
	SlimeLevel(StateData* stateInfo, std::string playerType, unsigned playerLevel, std::string backgroundFile = "MenuTextures/GameBackground/Map1.png");
	
	void initializeTextures();
	void initializeBoss();
	void initializeMinions();
	void initializeBossUI();
	void initializeMinionUI();
	void initializeNextLevelButton();

	void updatePauseMenuButtons();
	void updateNextLevelButton();
	void updatePlayerInput(const float& deltaTime);
	void updateEnemyUI(const float& deltaTime);
	void updateState(const float& deltaTime);

	void renderState(sf::RenderTarget* target = nullptr);
};

