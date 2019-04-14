#pragma once
#include "MainMenuState.h"
#include "State.h"
class EndGameScreen :
	public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	gui::Button* mainMenuButton;

	// Initializations
	void initializeBackground();
	void initializeKeybinds();
	void initializeButtons();
public:
	EndGameScreen(StateData* stateInfo, bool win);
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);
	void renderButtons(sf::RenderTarget* target);
	void renderState(sf::RenderTarget* target = nullptr);
	virtual	~EndGameScreen();
};

