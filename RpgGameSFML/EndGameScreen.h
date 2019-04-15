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
	bool wonGame;
	// Initializations
	void initializeBackground();
	void initializeKeybinds();
	void initializeButtons();
public:
	EndGameScreen(StateData* stateInfo, bool wonGame);
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);
	void updateButtons();
	void renderButtons(sf::RenderTarget* target);
	void renderState(sf::RenderTarget* target = nullptr);
	virtual	~EndGameScreen();
};

