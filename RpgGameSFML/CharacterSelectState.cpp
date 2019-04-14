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

	this->initializeVariables();
	this->initializeBackground();
	this->initializeKeybinds();
	this->initializeButtons();
}

/* getCharacterChoice() is an assessor function that returns the character's chosen model */
std::string CharacterSelectState::getCharacterChoice()
{
	return this->characterChoice;
}

void CharacterSelectState::initializeVariables()
{

}
/* initializeBackground() sets the backround for the window by loading the
   appropriate texture */
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

/* initializeKeybinds() reads the keybind config file to determine what
   keys out of the game's supported keys are binded to actions for this
	screen
*/
void CharacterSelectState::initializeKeybinds()
{
	std::ifstream readKeybinds("Config/charSelectStateKeybinds.ini");
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
/* initializeButtons() creates the buttons */
void CharacterSelectState::initializeButtons()
{
	this->buttons["CHOOSE_KNIGHT"] = new gui::Button(340.f, 390, 250.f, 250.f, "MenuTextures/CharSelect/KnightPort.png");
	this->buttons["CHOOSE_MAGE"] = new gui::Button(930.f, 390.f, 250.f, 250.f, "MenuTextures/CharSelect/MagePort.png");
}

/* updateButtons() checks to see the state of the buttons and selects the appropriate action */
void CharacterSelectState::updateButtons()
{
	for (auto &iterator : this->buttons)
	{
		iterator.second->updateButton(this->mousPositView);
	}

	if (this->buttons["CHOOSE_KNIGHT"]->isPressed())
	{
		this->characterChoice = "knight";
		this->states->push(new GameState(this->stateInfo, this->characterChoice));
	}
	else if (this->buttons["CHOOSE_MAGE"]->isPressed())
	{
		this->characterChoice = "mage";
		this->states->push(new GameState(this->stateInfo, this->characterChoice));
	}


}

void CharacterSelectState::updateInput(const float & deltaTime)
{
}
void CharacterSelectState::updateState(const float & deltaTime)
{
	this->updateButtons();
	this->updateMousePositions();
	this->updateInput(deltaTime);

}

void CharacterSelectState::renderButtons(sf::RenderTarget* target)
{
	for (auto &iterator : this->buttons)
	{
		iterator.second->renderButton(*target);
	}
}

void CharacterSelectState::renderState(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);
	this->renderButtons(target);

}

CharacterSelectState::~CharacterSelectState()
{
	auto iterator = this->buttons.begin();
	for (iterator; iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
	}
}
