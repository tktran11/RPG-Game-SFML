#include "stdafx.h"
#include "MainMenuState.h"

// Constructor
MainMenuState::MainMenuState(sf::RenderWindow* window, GraphicsSettings& graphics,
	std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states), graphicsSettings(graphics)
{
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

		if (!this->backgroundTexture.loadFromFile("MainMenuTextures/MenuArt.png"))
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
	this->buttons["PLAY_GAME"] = new gui::Button(640.f, 360.f, 200.f, 80.f, "MainMenuTextures/Play.png");
	this->buttons["SETTINGS"] = new gui::Button(640.f, 480.f, 200.f, 80.f, "MainMenuTextures/Settings.png");
	this->buttons["QUIT_GAME"] = new gui::Button(640.f, 600.f, 200.f, 80.f, "MainMenuTextures/Quit.png");
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
		this->states->push(new CharacterSelectState(this->window, this->graphicsSettings, this->supportedKeys, this->states));
	}
	if (this->buttons["SETTINGS"]->isPressed())
	{
		this->states->push(new SettingsMenuState(this->window, this->graphicsSettings, this->supportedKeys, this->states));
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