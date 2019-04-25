#pragma once
#include "GameState.h"
#include "MainMenuState.h"
class GolemLevel :
	public GameState
{
private:
	Enemy* minion1;
	Enemy* minion2;
	void initializeTextures();
	void initializeBoss();
	void initializeMinions();
public:
	GolemLevel(StateData* stateInfo, std::string playerType, unsigned playerLevel,
		std::string backgroundFile = "MenuTextures/GameBackground/Map2.png");

	void updatePauseMenuButtons();
	void updatePlayerInput(const float& deltaTime);
	void updateState(const float& deltaTime);

	void renderState(sf::RenderTarget* target = nullptr);
};
