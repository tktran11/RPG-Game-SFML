#pragma once
#include "gui.h"

/* PauseMenu.h is the header file for the pause menu. This is a classic feature of most games that allows the user
to pause all functionality so that they may return to the game after a quick break. As such it holds features to render
the pause menu and handle player input.

*/
class PauseMenu
{
private:

	sf::RectangleShape background;
	sf::RectangleShape buttonHolder;
	sf::Texture menuTexture;

	std::map<std::string, gui::Button*> buttons;

	void initializeBackground(sf::RenderWindow& window);
	void renderButtons(sf::RenderTarget* target);
public:
	PauseMenu(sf::RenderWindow& window);

	// Accessors
	std::map<std::string, gui::Button*>& getButtons();
	const bool& isButtonPressed(const std::string key);

	void createButton(float y, float width, float height, const std::string file, const std::string key);
	void updateMenu(const sf::Vector2f& mousePosView);
	void renderMenu(sf::RenderTarget* target);
	virtual ~PauseMenu();
};

