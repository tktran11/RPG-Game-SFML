#include "stdafx.h"
#include "CombatState.h"


CombatState::CombatState(StateData* stateInfo, std::string playerType)
	: State(stateInfo)
{
	sf::View properScreenView((sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y)));
	this->window->setView(properScreenView);
	this->chosenCharacter = playerType;
	this->initializeKeybinds();
	this->initializeBackground();
	this->initializeTextures();
	this->initializePauseMenu();
	this->initializePlayer();
}

// Reads keybinds from a specified .ini file and creates a map from keybind to binded value
void CombatState::initializeKeybinds()
{
	std::ifstream readKeybinds("Config/combatStateKeybinds.ini");
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

void CombatState::initializeTextures()
{
	if (this->chosenCharacter == "mage") {
		if (!this->stateTextures["PLAYER_SPRITES"].loadFromFile("Sprites/mageSheet.png"))
		{
			throw "ERROR:GAME_STATE::MISSING_PLAYER_TEXTURE";
		}
	}
	else {
		if (!this->stateTextures["PLAYER_SPRITES"].loadFromFile("Sprites/knightSheet.png"))
		{
			throw "ERROR:GAME_STATE::MISSING_PLAYER_TEXTURE";
		}
	}
}

void CombatState::initializeBackground()
{
	this->background.setSize(
		sf::Vector2f
		(static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("MenuTextures/GameBackground/Map1.png"))
	{
		throw "ERROR::CHAR_SELECT_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void CombatState::initializePauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window);
	this->pauseMenu->createButton((this->window->getSize().y * 0.694f),
		(this->window->getSize().x * 0.132f), (this->window->getSize().y * 0.111f),
		"MenuTextures/MainMenu/Quit.png", "QUIT_GAME");
}

void CombatState::initializePlayer()
{
	this->player = new Knight(this->stateTextures["PLAYER_SPRITES"], 0, 0);
}

void CombatState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT_GAME"))
	{

		this->states->push(new MainMenuState(this->stateInfo));
	}
}

void CombatState::updateState(const float& deltaTime)
{
	this->updateMousePositions();
	this->updateKeyboardtime(deltaTime);
	this->updateInput(deltaTime);

	// Update state while unpaused
	if (!this->isPaused) {
		this->updatePlayerInput(deltaTime);
		this->player->update(deltaTime);
	}
	else
	{
		this->pauseMenu->updateMenu(this->mousPositView);
		this->updatePauseMenuButtons();
	}

}

void CombatState::updatePlayerInput(const float& deltaTime)
{
}

void CombatState::renderState(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	this->player->renderEntity(*target);

	// Render pause menu
	if (this->isPaused)
	{
		this->pauseMenu->renderMenu(target);
	}
}

CombatState::~CombatState()
{
}
