#include "stdafx.h"
#include "MainMenuState.h"

// Constructor
MainMenuState::MainMenuState(StateData* stateInfo)
	: State(stateInfo)
{
	// Resize window view to properly scale contents of the screen
	// PUT THIS SHIT EVERYWHERE
	sf::View properScreenView((sf::FloatRect(0.f, 0.f, this->window->getSize().x, this->window->getSize().y)));
	this->window->setView(properScreenView);

	this->initializeBackground();
	this->initializeKeybinds();
	this->initializeButtons();
}

// Sets background texture for the main menu
void MainMenuState::initializeBackground()
{
		this->background.setSize(
			sf::Vector2f
			(static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)));

		if (!this->backgroundTexture.loadFromFile("MenuTextures/MainMenu/MenuArt.png"))
		{
			throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
		}

		this->background.setTexture(&this->backgroundTexture);
	}

// Sets keybinds for the main menu
void MainMenuState::initializeKeybinds()
{
	std::ifstream readKeybinds("Config/mainMenuStateKeybinds.ini");
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

// Creates a set of buttons for the main menu
void MainMenuState::initializeButtons()
{
	
	
	this->buttons["PLAY_GAME"] = new gui::Button((this->window->getSize().x * 0.5f),
		(this->window->getSize().y * 0.5f), (this->window->getSize().x * 0.156f),
		(this->window->getSize().y * 0.111f), "MenuTextures/MainMenu/Play.png");

	this->buttons["SETTINGS"] = new gui::Button((this->window->getSize().x * 0.5f),
		(this->window->getSize().y * 0.666f), (this->window->getSize().x * 0.156f),
		(this->window->getSize().y * 0.111f), "MenuTextures/MainMenu/Settings.png");

	this->buttons["CREDITS"] = new gui::Button((this->window->getSize().x * 0.851f), 
		(this->window->getSize().y * 0.902f), (this->window->getSize().x * 0.156f),
		(this->window->getSize().y * 0.111f), "MenuTextures/MainMenu/Credits.png");

	this->buttons["QUIT_GAME"] = new gui::Button((this->window->getSize().x * 0.5f),
		(this->window->getSize().y * 0.833f), (this->window->getSize().x * 0.156f),
		(this->window->getSize().y * 0.111f), "MenuTextures/MainMenu/Quit.png");
}

// Updates the buttons based on mouse position
void MainMenuState::updateButtons()
{
	for (auto &iterator : this->buttons)
	{
		iterator.second->updateButton(this->mousPositView);
	}

	if (this->buttons["PLAY_GAME"]->isPressed())
	{
		this->states->push(new CharacterSelectState(this->stateInfo));
	}
	if (this->buttons["SETTINGS"]->isPressed())
	{
		this->states->push(new SettingsMenuState(this->stateInfo));
	}
	if (this->buttons["CREDITS"]->isPressed())
	{
		this->states->push(new CreditScreenState(this->stateInfo));
	}
	if (this->buttons["QUIT_GAME"]->isPressed())
	{
		this->askedForQuit = true;
		this->window->close();
	}
}

// Needed for virtual. Updates any keypresses in the state (so none)
void MainMenuState::updateInput(const float & deltaTime) 
{
}

// Updates happenings on the state
void MainMenuState::updateState(const float & deltaTime) 
{
	this->updateButtons();
	this->updateMousePositions();
	this->updateInput(deltaTime);

}

// Renders the buttons
void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto &iterator : this->buttons)
	{
		iterator.second->renderButton(*target);
	}
}

// Renders the state
void MainMenuState::renderState(sf::RenderTarget* target)
{
	if (!target) 
	{
		target = this->window;
	}
	target->draw(this->background);
	this->renderButtons(target);

}

// Destructor
MainMenuState::~MainMenuState()
{
	auto iterator = this->buttons.begin();
	for (iterator; iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
	}
}