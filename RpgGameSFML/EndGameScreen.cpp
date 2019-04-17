#include "stdafx.h"
#include "EndGameScreen.h"

EndGameScreen::EndGameScreen(StateData* stateInfo, bool wonGame)
	: State(stateInfo)
{
	// Resize window view to properly scale contents of the screen
	// PUT THIS SHIT EVERYWHERE
	sf::View properScreenView((sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y)));
	this->window->setView(properScreenView);

	this->wonGame = wonGame;
	this->initializeBackground();
	this->initializeKeybinds();
	this->initializeButtons();
}

void EndGameScreen::initializeBackground()
{
	this->background.setSize(
		sf::Vector2f
		(static_cast<float>(this->window->getSize().x * 0.55f),
			static_cast<float>(this->window->getSize().y * 0.55f)));
	this->background.setOrigin(this->window->getSize().x * -0.2f, this->window->getSize().y * -0.25f);

	if (this->wonGame)
	{
		if (!this->backgroundTexture.loadFromFile("MenuTextures/EndScreen/Victory.png"))
		{
			
			throw "ERROR::ENDGAME_SCREEN::FAILED_TO_LOAD_WIN_BACKGROUND_TEXTURE";
		}
	}
	else
	{
		if (!this->backgroundTexture.loadFromFile("MenuTextures/EndScreen/Death.png"))
		{
			throw "ERROR::ENDGAME_SCREEN::FAILED_TO_LOAD_DEATH_BACKGROUND_TEXTURE";
		}
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
	this->mainMenuButton = new gui::Button((this->window->getSize().x * 0.898f),
		(this->window->getSize().y * 0.902f), (this->window->getSize().x * 0.156f),
		(this->window->getSize().y * 0.111f), "MenuTextures/Back.png");
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

void EndGameScreen::updateButtons()
{
	this->mainMenuButton->updateButton(this->mousPositView);

	if (this->mainMenuButton->isPressed())
	{
		this->states->push(new MainMenuState(this->stateInfo));
	}
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
