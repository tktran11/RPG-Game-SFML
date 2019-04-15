#include "stdafx.h"
#include "CreditScreenState.h"

CreditScreenState::CreditScreenState(StateData* stateInfo)
	: State(stateInfo)
{
	// Resize window view to properly scale contents of the screen
	// PUT THIS SHIT EVERYWHERE
	sf::View properScreenView((sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y)));
	this->window->setView(properScreenView);
	this->initializeBackground();
	this->initializeKeybinds();
	this->initializeButtons();
}

void CreditScreenState::initializeBackground()
{
	this->background.setSize(
		sf::Vector2f
		(static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("MenuTextures/Credits/Credits.png"))
	{
		throw "ERROR::CREDITS_SCREEN::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void CreditScreenState::initializeKeybinds()
{
	std::ifstream readKeybinds("Config/creditScreenKeybinds.ini");
	if (readKeybinds.is_open()) {
		std::string keybind = "";
		std::string bindedValue = "";

		while (readKeybinds >> keybind >> bindedValue)
		{
			this->keyBinds[keybind] = this->supportedKeys->at(bindedValue);
		}
	}
	readKeybinds.close();

}

void CreditScreenState::initializeButtons()
{
	this->backButton = new gui::Button((this->window->getSize().x * 0.898f), 
		(this->window->getSize().y * 0.902f),
		(this->window->getSize().x * 0.156f), (this->window->getSize().y * 0.111f),
		"MenuTextures/Back.png");
}

void CreditScreenState::updateInput(const float & deltaTime)
{

	this->backButton->updateButton(this->mousPositView);
	if (this->backButton->isPressed())
	{
		this->askedForQuit = true;
	}

}

void CreditScreenState::updateState(const float & deltaTime)
{
	this->updateMousePositions();
	this->updateInput(deltaTime);
}

void CreditScreenState::renderButtons(sf::RenderTarget * target)
{
	this->backButton->renderButton(*target);
}

void CreditScreenState::renderState(sf::RenderTarget * target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);
	this->renderButtons(target);
}


CreditScreenState::~CreditScreenState()
{
	delete this->backButton;
}
