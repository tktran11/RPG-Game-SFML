#pragma once
#include "gui.h"
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

	// Accessor
	std::map<std::string, gui::Button*>& getButtons();
	const bool& isButtonPressed(const std::string key);
	void createButton(float y, float width, float height, const std::string file, const std::string key);
	void updateMenu(const sf::Vector2f& mousePosView);
	void renderMenu(sf::RenderTarget* target);
	virtual ~PauseMenu();
};

