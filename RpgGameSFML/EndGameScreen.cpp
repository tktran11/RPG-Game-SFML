#include "stdafx.h"
#include "EndGameScreen.h"

EndGameScreen::EndGameScreen(StateData* stateInfo, bool win)
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

void EndGameScreen::initializeBackground()
{
	this->background.setSize(
		sf::Vector2f
		(static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("MenuTextures/StartScreen/TitleArt.png"))
	{
		throw "ERROR::CREDITS_SCREEN::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void EndGameScreen::initializeKeybinds()
{
	std::ifstream readKeybinds("Config/endGameKeybinds.ini");
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

void EndGameScreen::initializeButtons()
{
	this->mainMenuButton = new gui::Button(1150.f, 650.f, 200.f, 80.f, "MenuTextures/Settings/Back.png");
}

void EndGameScreen::updateInput(const float & deltaTime)
{
	this->mainMenuButton->updateButton(this->mousPositView);
	if (this->mainMenuButton->isPressed())
	{
		this->states->push(new MainMenuState(this->stateInfo));
	}
}

void EndGameScreen::updateState(const float & deltaTime)
{
	this->updateMousePositions();
	this->updateInput(deltaTime);
}

void EndGameScreen::renderButtons(sf::RenderTarget * target)
{
	this->mainMenuButton->renderButton(*target);
}

void EndGameScreen::renderState(sf::RenderTarget * target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);
	this->renderButtons(target);
}


EndGameScreen::~EndGameScreen()
{
	delete this->mainMenuButton;
}
