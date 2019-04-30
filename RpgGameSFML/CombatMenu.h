#pragma once
#include "gui.h"

/* CombatMenu.h is the header file for the combat menu. It allows the player to engage
in turn based combat with the enemies on screen.
*/

class CombatMenu
{
private:
	// SFML textures
	sf::RectangleShape combatDock;
	sf::Texture dockTexture;

	// Map of buttons
	std::map<std::string, gui::Button*> buttons;

	// Initialize and render functions for the menu/buttons
	void initializeMenu(sf::RenderWindow& window);
	void renderButtons(sf::RenderTarget* target);

public:
	// Constructor
	CombatMenu(sf::RenderWindow& window);

	// Accessors
	const bool& isButtonPressed(const std::string key);

	// Create/upate/render functions
	void createButton(float x, float y, float width, float height, const std::string file,
		const std::string text, short unsigned charSize, const std::string key);
	void updateMenu(const sf::Vector2f& mousePosView);
	void renderMenu(sf::RenderTarget* target);

	// Virtual destructor
	virtual ~CombatMenu();
};

