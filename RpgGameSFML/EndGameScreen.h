#pragma once
#include "MainMenuState.h"
#include "State.h"

/* EndGameScreen.h is the header file for the end game screen. This screen represents
the victory or death screen for the player depending on the outcome of the game
*/

class EndGameScreen :
	public State
{
private:
	// Texture and art
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	gui::Button* mainMenuButton;

	// Check to see if game was won or not
	bool wonGame;

	// Initializations
	void initializeBackground();
	void initializeKeybinds(std::string configFile);
	void initializeButtons();

public:
	// Constructor
	EndGameScreen(StateData* stateInfo, bool wonGame);
	
	// State Updating
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);
	void updateButtons();

	// State Rendering
	void renderButtons(sf::RenderTarget* target);
	void renderState(sf::RenderTarget* target = nullptr);

	// Destructor
	virtual	~EndGameScreen();
};

