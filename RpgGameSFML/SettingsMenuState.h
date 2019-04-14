#pragma once
#include "State.h"
#include "gui.h"
#include "Game.h"
class SettingsMenuState :
	public State
{
private:
	GraphicsSettings& graphicsSettings;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	std::map<std::string, gui::DropDownMenu*> dropDown;
	std::map<std::string, gui::Button*> buttons;
	std::map<short unsigned, std::string> screenResolution;


	std::vector<sf::VideoMode> screenModes;
	sf::VideoMode mode;
	

	// Initializes the keybinds for the Game State, overriden from State.
	void initializeVariables();
	void initializeBackground();
	void initializeKeybinds();
	void initializeGUI();
public:
	SettingsMenuState(sf::RenderWindow* window, GraphicsSettings& graphics, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SettingsMenuState();

	// Virtual Functions
	void updateButtons();
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);
	void renderGUI(sf::RenderTarget* target);
	void renderState(sf::RenderTarget* target = nullptr);
};

