#include "stdafx.h"
#include "EndGameScreen.h"

/* EndGameScreen.cpp is the body file for the end game screen. This screen represents
the victory or death screen for the player depending on the outcome of the game
*/

// Constructor
EndGameScreen::EndGameScreen(StateData* stateInfo, bool wonGame)
	: State(stateInfo)
{
	// Resize window view to properly scale contents of the screen
	// PUT THIS SHIT EVERYWHERE
	sf::View properScreenView((sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y)));
	this->window->setView(properScreenView);

	this->wonGame = wonGame;
	this->initializeBackground();
	this->initializeKeybinds("Config/endGameKeybinds.ini");
	this->initializeButtons();
}

// Creates the background for the state by settings its texture and size
void EndGameScreen::initializeBackground()
{
	this->background.setSize(
		sf::Vector2f
		(static_cast<float>(this->window->getSize().x * 0.55f),
			static_cast<float>(this->window->getSize().y * 0.55f)));
	this->background.setOrigin(this->window->getSize().x * -0.2f, this->window->getSize().y * -0.25f);

	// Choose which texture to load based on condition
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

// Initialize keybinds for the state
void EndGameScreen::initializeKeybinds(std::string configFile)
{
	std::ifstream readKeybinds(configFile);
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

// Initialize buttons for the state
void EndGameScreen::initializeButtons()
{
	this->mainMenuButton = new gui::Button((this->window->getSize().x * 0.898f),
		(this->window->getSize().y * 0.902f), (this->window->getSize().x * 0.156f),
		(this->window->getSize().y * 0.111f), "MenuTextures/Back.png");
}

// Updates button input on the state
void EndGameScreen::updateInput(const float & deltaTime)
{
	this->mainMenuButton->updateButton(this->mousPositView);
	if (this->mainMenuButton->isPressed())
	{
		this->states->push(new MainMenuState(this->stateInfo));
	}
}

// Updates the button on the state
void EndGameScreen::updateButtons()
{
	this->mainMenuButton->updateButton(this->mousPositView);

	if (this->mainMenuButton->isPressed())
	{
		this->states->push(new MainMenuState(this->stateInfo));
	}
}

// Updates the state including mouse position and button pressing
void EndGameScreen::updateState(const float & deltaTime)
{
	this->updateMousePositions();
	this->updateInput(deltaTime);
}

// Renders the buttons to the state
void EndGameScreen::renderButtons(sf::RenderTarget * target)
{
	this->mainMenuButton->renderButton(*target);
}

// Renders the state to the window
void EndGameScreen::renderState(sf::RenderTarget * target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);
	this->renderButtons(target);
}

// Destructor
EndGameScreen::~EndGameScreen()
{
	delete this->mainMenuButton;
}
