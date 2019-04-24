#include "stdafx.h"
#include "GameState.h"

/*
GameState.cpp is the body for the Gamestate class, which handles the resources for
the specific state called GameState. It houses textures and such for the main portion of
the game.
*/

// Constructor, calls initialization features
GameState::GameState(StateData* stateInfo, std::string playerType)
	: State(stateInfo)
{
	sf::View properScreenView((sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y)));
	this->window->setView(properScreenView);
	this->chosenCharacter = playerType;
	this->initializeKeybinds();
	this->initializeTextures();
	this->initializeBackground();
	this->initializePauseMenu();
	this->initializePlayer();
	this->initializePlayerGUI();
	this->initializeShade();
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
// the character selection screen (choices are mage and knight)
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

	if (!this->stateTextures["SHADE_SPRITE"].loadFromFile("Sprites/shadeSheet.png"))
	{
		throw "ERROR:GAME_STATE::MISSING_ENEMY_TEXTURE";
	}

	if (!this->stateTextures["SLIME_SPRITE"].loadFromFile("Sprites/slimeSheet.png"))
	{
		throw "ERROR:GAME_STATE::MISSING_ENEMY_TEXTURE";
	}
}

// Initializes the texture of the background and sets its texture
void GameState::initializeBackground()
{
	this->background.setSize(
		sf::Vector2f
		(static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("MenuTextures/GameBackground/Map1.png"))
	{
		throw "ERROR::GAME_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

// Creates the pause menu 
void GameState::initializePauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window);
	this->pauseMenu->createButton((this->window->getSize().y * 0.694f),
		(this->window->getSize().x * 0.132f), (this->window->getSize().y * 0.111f),
		"MenuTextures/MainMenu/Quit.png", "QUIT_GAME");
}

// Creates a new player, setting its texture and position
void GameState::initializePlayer()
{
	float startingPos = this->window->getSize().y * 0.72f;
	bool scaleScreen = this->stateInfo->graphicsSettings->isFullScreen;
	if (scaleScreen)
	{
		startingPos = 1280 * 0.62f;
	}
	if (this->chosenCharacter == "knight")
	{
		this->player = new Knight(this->stateTextures["PLAYER_SPRITES"], 0, startingPos, scaleScreen);
	}
	else
		if (this->chosenCharacter == "mage")
		{
			this->player = new Mage(this->stateTextures["PLAYER_SPRITES"], 0, startingPos, scaleScreen);
		}

}

void GameState::initializeShade()
{
	float startingPos = this->window->getSize().y * 0.72f;
	bool scaleScreen = this->stateInfo->graphicsSettings->isFullScreen;
	if (scaleScreen)
	{
		startingPos = 1280 * 0.62f;
	}

	this->enemy1 = new Shade(this->stateTextures["SHADE_SPRITE"], 1000, startingPos, scaleScreen);
}

void GameState::initializeSlime()
{
	float startingPos = this->window->getSize().y * 0.72f;
	bool scaleScreen = this->stateInfo->graphicsSettings->isFullScreen;
	if (scaleScreen)
	{
		startingPos = 1280 * 0.62f;
	}

	this->enemy2 = new Slime(this->stateTextures["SLIME_SPRITE"], 1200, startingPos, scaleScreen);
}

// Creates the player interface for relevant stats like health and mana, experience, and level
void GameState::initializePlayerGUI()
{
	this->playerGUI = new CharacterGUI(this->player, this->chosenCharacter);
}

// Updates input for the player movement by polling the keyboard for any input and moving the player based on that
void GameState::updatePlayerInput(const float& deltaTime)
{
	// Movement is soft limited to the bounds of where the screen is. The player can still technically fall off screen, but can't continue moving that way
	// Up and downward movement limited to actual ground

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT")))) && (this->player->getXPosition() >= this->window->getSize().x * 0.039f))
	{
		this->player->move(deltaTime, -0.8f, 0.f);
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT")))) && (this->player->getXPosition() <= this->window->getSize().x * 0.9f))
	{
		this->player->move(deltaTime, 0.8f, 0.f);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN")))) && (this->player->getYPosition() <= this->player->getStartPosY() + 14.f))
	{
		this->player->move(deltaTime, 0.f, 0.5f);
	
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP")))) && (this->player->getYPosition() >= this->player->getStartPosY() - 10.f))
	{

		this->player->move(deltaTime, 0.f, -0.5f);

	}
}

// Updates the player interface for relevant stats
void GameState::updatePlayerGUI(const float & deltaTime)
{
	this->playerGUI->updateUI(deltaTime);
}

// Updates the pause menu buttons
void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT_GAME"))
	{

		this->states->push(new MainMenuState(this->stateInfo));
	}
}

// Updates input on the state, specifically the pause menu
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
		// Updated player related functions on the state
		this->updatePlayerInput(deltaTime);
		this->player->update(deltaTime);
		this->playerGUI->updateUI(deltaTime);

		// Updates enemies on the state
		this->enemy1->update(deltaTime);
		//this->enemy2->update(deltaTime);
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
	target->draw(this->background);

	//Render player and player UI to the screen
	this->player->renderEntity(*target);
	this->playerGUI->renderUI(*target);

	//Renders level 1 enemies (Slime + Shade)
	this->enemy1->renderEntity(*target);
	//this->enemy2->renderEntity(*target);

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
	delete this->playerGUI;
	delete this->pauseMenu;
}
