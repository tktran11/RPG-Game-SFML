#pragma once
#include "State.h"
#include "gui.h"
#include "Game.h"
class SettingsMenuState :
	public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	std::map<std::string, gui::DropDownMenu*> dropDown;
	std::map<std::string, gui::Button*> buttons;
	std::map<short unsigned, std::string> screenResolution;
	std::vector<unsigned> fpsLimits;
	bool hasVerticalSync;
	std::vector<sf::VideoMode> resolutionModes;
	sf::VideoMode mode;
	

	// Initializes the keybinds for the Game State, overriden from State.
	void initializeVariables();
	void initializeBackground();
	void initializeKeybinds();
	void initializeGUI();
public:
	SettingsMenuState(StateData* stateInfo);
	virtual ~SettingsMenuState();

	// Virtual Functions
	void updateButtons();
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);
	void renderGUI(sf::RenderTarget* target);
	void renderState(sf::RenderTarget* target = nullptr);
};

