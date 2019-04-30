#include "stdafx.h"
#include "CombatMenu.h"


CombatMenu::CombatMenu(sf::RenderWindow & window)
{
	this->initializeMenu(window);
}

void CombatMenu::initializeMenu(sf::RenderWindow & window)
{
	this->combatDock.setSize(
		sf::Vector2f
		(static_cast<float>(window.getSize().x / 2.5f),
			static_cast<float>(window.getSize().y / 3.f)));


	if (!this->dockTexture.loadFromFile("MenuTextures/CombatMenu/Panel.png"))
	{
		throw "ERROR::COMBAT_MENU:: FAILED TO LOAD BACKGROUND TEXTURE";
	}
	this->combatDock.setTexture(&this->dockTexture);
	this->combatDock.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->combatDock.getSize().x / 2.f, 0.f);

}

const bool & CombatMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}


void CombatMenu::createButton(float x, float y, float width, float height, const std::string file, const std::string text, short unsigned charSize, const std::string key)
{
	this->buttons[key] = new gui::Button(x, y, width, height, file, text, charSize);
}

void CombatMenu::updateMenu(const sf::Vector2f & mousePosView)
{
	for (auto &iterator : this->buttons)
	{
		iterator.second->updateTextButton(mousePosView);
	}
}

void CombatMenu::renderButtons(sf::RenderTarget * target)
{
	for (auto &iterator : this->buttons)
	{
		iterator.second->renderTextButton(*target);
	}
}

void CombatMenu::renderMenu(sf::RenderTarget * target)
{

	target->draw(this->combatDock);
	this->renderButtons(target);
}

CombatMenu::~CombatMenu()
{
	auto iterator = this->buttons.begin();
	for (iterator; iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
	}
}
