#include "stdafx.h"
#include "CreditScreenState.h"


/* CreditScreenState.cpp is the body file for the credit screen state, which
houses a simple picture of the contributors to this project, including the programmers
and our artist friend
*/

// Constructor
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

// Creates the background and sets the texture for the background
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

// Inializes keybinds for the state
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

// Creates the buttons for the state
void CreditScreenState::initializeButtons()
{
	this->backButton = new gui::Button((this->window->getSize().x * 0.898f), 
		(this->window->getSize().y * 0.902f),
		(this->window->getSize().x * 0.156f), (this->window->getSize().y * 0.111f),
		"MenuTextures/Back.png");
}

// Updates input on the state, specifically for the single button the state has
void CreditScreenState::updateInput(const float & deltaTime)
{

	this->backButton->updateButton(this->mousPositView);
	if (this->backButton->isPressed())
	{
		this->askedForQuit = true;
	}

}

// Updates the state including mouse position and the buttons
void CreditScreenState::updateState(const float & deltaTime)
{
	this->updateMousePositions();
	this->updateInput(deltaTime);
}

// Draws the button
void CreditScreenState::renderButtons(sf::RenderTarget * target)
{
	this->backButton->renderButton(*target);
}

// Renders the state to the window
void CreditScreenState::renderState(sf::RenderTarget * target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);
	this->renderButtons(target);
}

// Destructor
CreditScreenState::~CreditScreenState()
{
	delete this->backButton;
}
