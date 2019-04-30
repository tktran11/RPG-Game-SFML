#include "stdafx.h"
#include "CombatMenu.h"

// Constructor
CombatMenu::CombatMenu(sf::RenderWindow & window)
{
	this->initializeMenu(window);
}

// Initializes the menu to the current window
void CombatMenu::initializeMenu(sf::RenderWindow & window)
{
	// sizing
	this->combatDock.setSize(
		sf::Vector2f
		(static_cast<float>(window.getSize().x / 2.5f),
			static_cast<float>(window.getSize().y / 3.f)));

	// Loads texture from a file, throws exception otherwise
	if (!this->dockTexture.loadFromFile("MenuTextures/CombatMenu/Panel.png"))
	{
		throw "ERROR::COMBAT_MENU:: FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->combatDock.setTexture(&this->dockTexture);
	this->combatDock.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->combatDock.getSize().x / 2.f, 0.f);
}

// Checks to see if a button is pressed
const bool & CombatMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

// Creates the butons for the combat menu
void CombatMenu::createButton(float x, float y, float width, float height, const std::string file, const std::string text, short unsigned charSize, const std::string key)
{
	this->buttons[key] = new gui::Button(x, y, width, height, file, text, charSize);
}

// Updates the menu
void CombatMenu::updateMenu(const sf::Vector2f & mousePosView)
{
	for (auto &iterator : this->buttons)
	{
		iterator.second->updateTextButton(mousePosView);
	}
}

// Renders the buttons to the target location
void CombatMenu::renderButtons(sf::RenderTarget * target)
{
	for (auto &iterator : this->buttons)
	{
		iterator.second->renderTextButton(*target);
	}
}

// Renders the combat menu to the screen
void CombatMenu::renderMenu(sf::RenderTarget * target)
{
	target->draw(this->combatDock);
	this->renderButtons(target);
}

// Destructor
CombatMenu::~CombatMenu()
{
	auto iterator = this->buttons.begin();
	for (iterator; iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
	}
}
