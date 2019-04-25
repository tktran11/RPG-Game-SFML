#pragma once
#include "GameState.h"
#include "MainMenuState.h"
class BossLevel :
	public GameState
{
private:
	void initializeTextures();
	void initializeBoss();
public:
	BossLevel(StateData* stateInfo, std::string playerType, unsigned playerLevel, 
		std::string backgroundFile = "MenuTextures/GameBackground/Map3.png");

	void updatePauseMenuButtons();
	void updatePlayerInput(const float& deltaTime);
	void updateState(const float& deltaTime);

	void renderState(sf::RenderTarget* target = nullptr);
};

