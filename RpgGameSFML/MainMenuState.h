#pragma once
#include"CharacterSelectState.h"
#include "SettingsMenuState.h"
#include "CreditScreenState.h"
#include "gui.h"

/*
MainMenuState.h is the header for the MainMenuState class, which handles the resources for
the specific state called Main Menu. It houses textures and such for that state.
*/

class MainMenuState : public State
{
private:
	// SFML textures
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	std::map<std::string, gui::Button*> buttons;

	// Initializes the keybinds for the Game State, overriden from State.
	void initializeBackground();
	void initializeKeybinds(std::string configFile);
	void initializeButtons();

public:
	// Constructor
	MainMenuState(StateData* stateData);

	// State Updating
	void updateButtons();
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);

	// State Rendering
	void renderButtons(sf::RenderTarget* target);
	void renderState(sf::RenderTarget* target = nullptr);

	// Virtual destructor
	virtual ~MainMenuState();
};

