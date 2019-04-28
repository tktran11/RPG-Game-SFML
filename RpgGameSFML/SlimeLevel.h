#pragma once
#include "GameState.h"
#include "MainMenuState.h"
#include "EndGameScreen.h"

class SlimeLevel :
	public GameState
{
private:
	Enemy* minion1;
	Enemy* minion2;
public:
	SlimeLevel(StateData* stateInfo, std::string playerType, unsigned playerLevel, std::string backgroundFile = "MenuTextures/GameBackground/Map1.png");
	
	void initializeTextures();
	void initializeBoss();
	void initializeMinions();

	void updatePauseMenuButtons();
	void updatePlayerInput(const float& deltaTime);
	void updateState(const float& deltaTime);

	void renderState(sf::RenderTarget* target = nullptr);
};

