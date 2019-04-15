#pragma once
#include "gui.h"
#include "State.h"
class CreditScreenState :
	public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	gui::Button* backButton;

	// Initializations
	void initializeBackground();
	void initializeKeybinds();
	void initializeButtons();
public:
	CreditScreenState(StateData* stateInfo);

	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);
	void renderButtons(sf::RenderTarget* target);
	void renderState(sf::RenderTarget* target = nullptr);
	virtual ~CreditScreenState();
};

