#pragma once
#include "gui.h"
#include "State.h"
#include "GameState.h"

/* CharacterSelectState.h is the header file for the Character Selection Menu. Here the player
   will select which of the two characters they would like to begin the game as */
class CharacterSelectState :
	public State
{
private:
	GraphicsSettings& graphicsSettings;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	std::string characterChoice;
	// Going to need to add sf::text here

	std::map<std::string, gui::Button*> buttons;

	// Initialization for the Character Select
	void initializeBackground();
	void initializeVariables();
	void initializeKeybinds();
	void initializeButtons();
public:
	// Constructor
	CharacterSelectState(sf::RenderWindow* window, GraphicsSettings& graphicsSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
 	// Storage for character choice --> after adding animations, store this as a Sprite pointer and pass that instead.
	std::string getCharacterChoice();
	// Character Select Updating and Rendering
	void updateButtons();
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);
	void renderButtons(sf::RenderTarget* target);
	void renderState(sf::RenderTarget* target = nullptr);
	virtual ~CharacterSelectState();
};



