#include "stdafx.h"
#include "GameState.h"

/*
GameState.cpp is the body for the Gamestate class, which handles the resources for
the specific state called GameState. It houses textures and such for the main portion of
the game.
*/

// Constructor, calls initialization features
GameState::GameState(sf::RenderWindow* window, GraphicsSettings& graphics, std::map<std::string, int>* supportedKeys,
	std::stack<State*>* states, std::string playerType)
	: State(window, supportedKeys, states), graphicsSettings(graphics)
{
	this->chosenCharacter = playerType;
	this->initializeKeybinds();
	this->initializeTextures();
	this->initializePauseMenu();
	this->initializePlayer();
}

// Reads keybinds from a specified .ini file and creates a map from keybind to binded value
void GameState::initializeKeybinds()
{
	std::ifstream readKeybinds("Config/gameStateKeybinds.ini");
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

// Initializes the texture of the background and player character based on chosen character from
// the character selection screen (choices are mage and knight
void GameState::initializeTextures()
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

void GameState::initializePauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window);
	this->pauseMenu->createButton(500.f, 170.f, 80.f, "MainMenuTextures/Quit.png", "QUIT_GAME");
}

// Creates a new player, setting its texture and position
void GameState::initializePlayer()
{
	this->player = new PlayerCharacter(this->stateTextures["PLAYER_SPRITES"], 0, 0);
}

// Updates input for the player movement by polling the keyboard for any input and moving the player based on that
void GameState::updatePlayerInput(const float& deltaTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP"))))
	{
		this->player->move(deltaTime, 0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT"))))
	{
		this->player->move(deltaTime, -1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN"))))
	{
		this->player->move(deltaTime, 0.f, 1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT"))))
	{
		this->player->move(deltaTime, 1.f, 0.f);
	}

}

void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT_GAME"))
	{
		this->states->push(new MainMenuState(this->window, this->graphicsSettings, this->supportedKeys, this->states));
	}
}

void GameState::updateInput(const float & deltaTime)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("PAUSE"))) && this->getKeyboardTimer())
	{
		if (!this->isPaused)
		{
			this->pauseState();
		}
		else
		{
			this->unPauseState();
		}
	}
}

// Handles checking for input and player updates for each frame 
void GameState::updateState(const float& deltaTime)
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

// Renders characters and such to the state's window
void GameState::renderState(sf::RenderTarget* target)
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

// Destructor
GameState::~GameState()
{
	delete this->player;
	delete this->pauseMenu;
}
