#pragma once
#include"CharacterSelectState.h"
#include "SettingsMenuState.h"
#include "gui.h"
/*
MainMenuState.h is the header for the MainMenuState class, which handles the resources for
the specific state called Main Menu. It houses textures and such for that state.
*/
class MainMenuState : public State
{
private:
	GraphicsSettings& graphicsSettings;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	std::map<std::string, gui::Button*> buttons;

	// Initializes the keybinds for the Game State, overriden from State.
	void initializeBackground();
	void initializeKeybinds();
	void initializeButtons();
public:
	// Constructor
	MainMenuState(sf::RenderWindow* window, GraphicsSettings& graphics,
		std::map<std::string, int>* supportedKeys, std::stack<State*>* states);

	// Virtual Functions
	void updateButtons();
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);
	void renderButtons(sf::RenderTarget* target);
	void renderState(sf::RenderTarget* target = nullptr);

	// Destructor
	virtual ~MainMenuState();
};

