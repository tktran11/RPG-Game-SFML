#pragma once
#include "MainMenuState.h"

/* TitleScreenState.h is the header file for the Title Screen which is the intro screen the player sees when entering the game */

class TitleScreenState :
	public State
{
private:

	// Visuals and Texture storage
	GraphicsSettings& graphicsSettings;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	gui::Button *playButton;

	
	// Initializations

	void initializeBackground();
	void initializeKeybinds();
	void initializeButtons();


public:
	// Constructor
	TitleScreenState(sf::RenderWindow* window, GraphicsSettings& graphics, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);

	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);
	void renderButtons(sf::RenderTarget* target);
	void renderState(sf::RenderTarget* target = nullptr);
	
	// Destructor
	virtual ~TitleScreenState();
};

