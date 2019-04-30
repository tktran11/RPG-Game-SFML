#pragma once
#include "gui.h"

/* 
PauseMenu.h is the header file for the pause menu. This is a classic feature of most games that allows the user
to pause all functionality so that they may return to the game after a quick break. As such it holds features to render
the pause menu and handle player input.
*/

class PauseMenu
{
private:
	// SFML created objects
	sf::RectangleShape background;
	sf::RectangleShape buttonHolder;
	sf::Texture menuTexture;

	// Map of buttons
	std::map<std::string, gui::Button*> buttons;

	// Initialize and render functions
	void initializeBackground(sf::RenderWindow& window);
	void renderButtons(sf::RenderTarget* target);
public:
	// Constructor
	PauseMenu(sf::RenderWindow& window);

	// Map of buttons
	std::map<std::string, gui::Button*>& getButtons();

	// Button creation + checks for the pause menu
	const bool& isButtonPressed(const std::string key);
	void createButton(float y, float width, float height, const std::string file, const std::string key);

	// Render and update the pause menu
	void updateMenu(const sf::Vector2f& mousePosView);
	void renderMenu(sf::RenderTarget* target);

	// Virtual destructor
	virtual ~PauseMenu();
};