#pragma once
#include "MainMenuState.h"

// TitleScreenState.h is the header file for the Title Screen which is the intro screen the player sees when entering the game

class TitleScreenState :
	public State
{
private:
	// Visuals and Texture storage
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	gui::Button *playButton;

	// Initializer functions
	void initializeBackground();
	void initializeKeybinds(std::string configFile);
	void initializeButtons();

public:
	// Constructor
	TitleScreenState(StateData* stateInfo);

	// State Updating
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);

	// State Rendering
	void renderButtons(sf::RenderTarget* target);
	void renderState(sf::RenderTarget* target = nullptr);
	
	// Destructor
	virtual ~TitleScreenState();
};

