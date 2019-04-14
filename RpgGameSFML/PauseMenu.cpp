#include "stdafx.h"
#include "PauseMenu.h"


void PauseMenu::initializeBackground(sf::RenderWindow& window)
{
		this->background.setSize(
			sf::Vector2f
			(static_cast<float>(window.getSize().x),
				static_cast<float>(window.getSize().y)));

		this->background.setFillColor(sf::Color(20, 20, 20, 100));
		if (!this->menuTexture.loadFromFile("MenuTextures/PauseMenu/Banner.png"))
		{
			throw "ERROR::PAUSE_MENU:: FAILED TO LOAD BACKGROUND TEXTURE";
		}

		this->buttonHolder.setSize(
			sf::Vector2f
			(static_cast<float>(window.getSize().x) / 2.f,
				static_cast<float>(window.getSize().y)));
		this->buttonHolder.setTexture(&this->menuTexture);
		this->buttonHolder.setPosition(static_cast<float>(window.getSize().x) /2.f - this->buttonHolder.getSize().x / 2.f, 0.f);
}

void PauseMenu::renderButtons(sf::RenderTarget * target)
{
	for (auto &iterator : this->buttons)
	{
		iterator.second->renderButton(*target);
	}
}

PauseMenu::PauseMenu(sf::RenderWindow& window)
{
	this->initializeBackground(window);
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

const bool & PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::createButton(float y, float width, float height, const std::string file, const std::string key)
{
	float xPos = this->buttonHolder.getPosition().x + this->buttonHolder.getSize().x / 2.f;
	this->buttons[key] = new gui::Button(xPos, y, width, height, file);
}

void PauseMenu::updateMenu(const sf::Vector2f& mousePositView)
{
	for (auto &iterator : this->buttons)
	{
		iterator.second->updateButton(mousePositView);
	}
}

void PauseMenu::renderMenu(sf::RenderTarget* target)
{
	target->draw(background);
	target->draw(buttonHolder);

	this->renderButtons(target);
}


PauseMenu::~PauseMenu()
{
	auto iterator = this->buttons.begin();
	for (iterator; iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
	}
}
