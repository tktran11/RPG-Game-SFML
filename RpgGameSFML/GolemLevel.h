#pragma once
#include "GameState.h"
#include "MainMenuState.h"
#include "EndGameScreen.h"
#include "EnemyUI.h"
#include "BossLevel.h"

class GolemLevel :
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
	bool minion2Dead = false;
public:
	GolemLevel(StateData* stateInfo, std::string playerType, unsigned playerLevel, std::string backgroundFile = "MenuTextures/GameBackground/Map2.png");

	void initializeTextures();
	void initializeBoss();
	void initializeBossUI();
	void initializeMinions();
	void initializeMinionUI();
	void initializeNextLevelButton();

	void updatePauseMenuButtons();
	void updateCombatMenuButtons();

	void updateNextLevelButton();
	void updatePlayerInput(const float& deltaTime);
	void updateEnemyUI(const float& deltaTime);
	void updateState(const float& deltaTime);

	void renderState(sf::RenderTarget* target = nullptr);
};

