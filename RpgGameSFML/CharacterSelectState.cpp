#include "stdafx.h"
#include "CharacterSelectState.h"

/* CharacterSelectState.cpp is the body file for the Character Selection Menu. Here the player
   will select which of the two characters they would like to begin the game as */
CharacterSelectState::CharacterSelectState(StateData* stateInfo)
	: State(stateInfo)
{
	// Resize window view to properly scale contents of the screen
	// PUT THIS SHIT EVERYWHERE
	sf::View properScreenView((sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y)));
	this->window->setView(properScreenView);

	this->initializeBackground();
	this->initializeKeybinds("Config/charSelectStateKeybinds.ini");
	this->initializeButtons();
}

// Assessor function that returns the character's chosen model */
std::string CharacterSelectState::getCharacterChoice()
{
	return this->characterChoice;
}

/* Sets the backround for the window by loading the
   appropriate texture
*/
void CharacterSelectState::initializeBackground()
{
	this->background.setSize(
		sf::Vector2f
		(static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("MenuTextures/CharSelect/CharacterSelectBG.png"))
	{
		throw "ERROR::CHAR_SELECT_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

/* Reads the keybind config file to determine what
   keys out of the game's supported keys are binded to actions for this
	screen
*/
void CharacterSelectState::initializeKeybinds(std::string configFile)
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

// Creates the buttons for the state
void CharacterSelectState::initializeButtons()
{
	this->buttons["CHOOSE_KNIGHT"] = new gui::Button((this->window->getSize().x * 0.265f),
		(this->window->getSize().y * 0.542f), 
		(this->window->getSize().x * 0.195f), (this->window->getSize().y * 0.347f), 
		"MenuTextures/CharSelect/KnightPort.png");
	this->buttons["CHOOSE_MAGE"] = new gui::Button((this->window->getSize().x * 0.726f), 
		(this->window->getSize().y * 0.542f),
		(this->window->getSize().x * 0.195f), (this->window->getSize().y * 0.347f), 
		"MenuTextures/CharSelect/MagePort.png");
	this->buttons["BACK"] = new gui::Button((this->window->getSize().x * 0.898f),
		(this->window->getSize().y * 0.902f), (this->window->getSize().x * 0.156f),
		(this->window->getSize().y * 0.111f), "MenuTextures/Back.png");
}

// Checks to see what's happening with the buttons
void CharacterSelectState::updateButtons()
{
	for (auto &iterator : this->buttons)
	{
		iterator.second->updateButton(this->mousPositView);
	}
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}
	if (this->buttons["CHOOSE_KNIGHT"]->isPressed())
	{
		this->characterChoice = "knight";
		this->states->push(new SlimeLevel(this->stateInfo, this->characterChoice, 1));
	}
	else if (this->buttons["CHOOSE_MAGE"]->isPressed())
	{
		this->characterChoice = "mage";
		this->states->push(new SlimeLevel(this->stateInfo, this->characterChoice, 1));
	}
}

// Updates any input on the state
void CharacterSelectState::updateInput(const float & deltaTime)
{
	this->updateButtons();
}

// Updates the state
void CharacterSelectState::updateState(const float & deltaTime)
{
	this->updateMousePositions();
	this->updateInput(deltaTime);
}

// Renders the buttons to the state
void CharacterSelectState::renderButtons(sf::RenderTarget* target)
{
	for (auto &iterator : this->buttons)
	{
		iterator.second->renderButton(*target);
	}
}

// Renders the state to the window
void CharacterSelectState::renderState(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);
	this->renderButtons(target);
}

// Destructor
CharacterSelectState::~CharacterSelectState()
{
	auto iterator = this->buttons.begin();
	for (iterator; iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
	}
}
