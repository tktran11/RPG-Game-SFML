#pragma once
#include "State.h"
#include "gui.h"
#include "Game.h"

/* SettingsMenu.h is the header file for the settings menu, which houses options for the player to choose from
including screen size, video mode, and even frame rate options. 
*/
class SettingsMenuState :
	public State
{
private:
	// Interface and background art handling
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
	// Constructor
	SettingsMenuState(StateData* stateInfo);

	// State Updating
	void updateButtons();
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);

	// State Rendering
	void renderGUI(sf::RenderTarget* target);
	void renderState(sf::RenderTarget* target = nullptr);

	virtual ~SettingsMenuState();
};

