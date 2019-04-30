#include "stdafx.h"
#include "GameState.h"

/*
GameState.cpp is the body for the Gamestate class, which handles the resources for
the specific state called GameState. It houses textures and such for the main portion of
the game.
*/

// Constructor, calls initialization features
GameState::GameState(StateData* stateInfo, std::string playerType, unsigned playerLevel, std::string backgroundFile) :
	State(stateInfo)
{
	sf::View properScreenView((sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y)));
	this->window->setView(properScreenView);
	this->backgroundFile = backgroundFile;
	this->chosenCharacter = playerType;
	this->initializeBackground(backgroundFile);
	this->initializePlayer(playerLevel);
	this->initializePlayerGUI();
	this->initializePauseMenu();
	this->initializeCombatMenu();
	this->playerActionTimer = 50.f;
	this->playerActionTimerMax = 100.f;
	this->enemyActionTimer = 0.f;
	this->enemyActionTimerMax = 175.f;
	this->deathTimer = 0.f;
	this->deathTimeMax = 8.5f;
}

const bool GameState::getPlayerActionTimer()
{
	if (this->playerActionTimer >= this->playerActionTimerMax)
	{
		this->playerActionTimer = 100.f;
		return true;
	}
	else
	{
		return false;
	}
}

const bool GameState::getEnemyActionTimer()
{
	if (this->enemyActionTimer>= this->enemyActionTimerMax)
	{
		this->enemyActionTimer = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

// Returns reset of death timer
const bool GameState::getDeathTimer()
{
	if (this->deathTimer >= this->deathTimeMax)
	{
		this->deathTimer = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

// Reads keybinds from a specified .ini file and creates a map from keybind to binded value
void GameState::initializeKeybinds(std::string configFile)
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

// Initializes the texture of the background and sets its texture
void GameState::initializeBackground(std::string backgroundFile)
{
	this->background.setSize(
		sf::Vector2f
		(static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile(backgroundFile))
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

void GameState::initializeCombatMenu()
{
	float scale = this->player->getSpriteScale();
	this->combatMenu = new CombatMenu(*this->window);
	if (this->chosenCharacter == "knight")
	{
		this->combatMenu->createButton((this->window->getSize().x * 0.41f),
			(this->window->getSize().y * 0.12f), (this->window->getSize().x * 0.15f),
			(this->window->getSize().y * 0.09f),
			"MenuTextures/CombatMenu/Button.png", "Slash\n0 Mana", 24 * scale, "MOVE_1");
		this->combatMenu->createButton((this->window->getSize().x * 0.59f),
			(this->window->getSize().y * 0.12f), (this->window->getSize().x * 0.15f),
			(this->window->getSize().y * 0.09f),
			"MenuTextures/CombatMenu/Button.png", "Fortify\n25 Mana", 24 * scale, "MOVE_2");
		this->combatMenu->createButton((this->window->getSize().x * 0.41f),
			(this->window->getSize().y * 0.22f), (this->window->getSize().x * 0.15f),
			(this->window->getSize().y * 0.09f),
			"MenuTextures/CombatMenu/Button.png", "Taunt\n50 Mana", 24 * scale, "MOVE_3");
		this->combatMenu->createButton((this->window->getSize().x * 0.59f),
			(this->window->getSize().y * 0.22f), (this->window->getSize().x * 0.15f),
			(this->window->getSize().y * 0.09f),
			"MenuTextures/CombatMenu/Button.png", "Shield Bash \n 50 Mana", 24 * scale, "MOVE_4");
	}
	else if (this->chosenCharacter == "mage")
	{
		this->combatMenu->createButton((this->window->getSize().x * 0.41f),
			(this->window->getSize().y * 0.12f), (this->window->getSize().x * 0.15f),
			(this->window->getSize().y * 0.09f),
			"MenuTextures/CombatMenu/Button.png", "Hexplosion\n25 Mana", 22 * scale, "MOVE_1");
		this->combatMenu->createButton((this->window->getSize().x * 0.59f),
			(this->window->getSize().y * 0.12f), (this->window->getSize().x * 0.15f),
			(this->window->getSize().y * 0.09f),
			"MenuTextures/CombatMenu/Button.png", "Disciplined Thinking \n Restores 25 Mana", 18 * scale, "MOVE_2");
		this->combatMenu->createButton((this->window->getSize().x * 0.41f),
			(this->window->getSize().y * 0.22f), (this->window->getSize().x * 0.15f),
			(this->window->getSize().y * 0.09f),
			"MenuTextures/CombatMenu/Button.png", "Dark Ignition\n 50 Mana", 22 * scale, "MOVE_3");
		this->combatMenu->createButton((this->window->getSize().x * 0.59f),
			(this->window->getSize().y * 0.22f), (this->window->getSize().x * 0.15f),
			(this->window->getSize().y * 0.09f),
			"MenuTextures/CombatMenu/Button.png", "Obsidian Sweep \n  100 Mana", 22 * scale, "MOVE_4");
	}
}

// Creates a new player, setting its texture and position on the screen
void GameState::initializePlayer(unsigned playerLevel)
{
	float startingPos = this->window->getSize().y * 0.72f;
	bool scaleScreen = this->stateInfo->graphicsSettings->isFullScreen;
	if (scaleScreen)
	{
		startingPos = 1280 * 0.62f;
	}
	// If knight, loads knight texture sheet
	if (this->chosenCharacter == "knight")
	{
		this->player = new Knight(this->stateTextures["PLAYER_SPRITES"], 0, startingPos, playerLevel, 
			"Config/KnightStats.txt", "Config/KnightMoveset.txt", scaleScreen);
	}
	// Otherwise load mage texture sheet
	else
		if (this->chosenCharacter == "mage")
		{
			this->player = new Mage(this->stateTextures["PLAYER_SPRITES"], 0, startingPos, playerLevel, 
				"Config/MageStats.txt", "Config/MageMoveset.txt", scaleScreen);
		}
}

// Creates the player interface for relevant stats like health and mana, experience, and level
void GameState::initializePlayerGUI()
{
	this->playerGUI = new CharacterGUI(this->player, this->chosenCharacter);
}

// Updates the player interface for relevant stats
void GameState::updatePlayerGUI(const float & deltaTime)
{
	this->playerGUI->updateUI(deltaTime);
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

void GameState::updateCombat(const float& deltaTime)
{
	//std::cout << this->player->getXPosition() << std::endl;
	if (this->player->getXPosition() >= this->window->getSize().x * 0.4f)
	{
		this->enterCombatState();
	}
}

void GameState::updatePlayerActionTimer(const float & deltaTime)
{
	if (this->playerActionTimer < this->playerActionTimerMax)
	{
		this->playerActionTimer += 100.f * deltaTime;
	}
}

void GameState::updateEnemyActionTime(const float & deltaTime)
{
	if (this->enemyActionTimer < this->enemyActionTimerMax)
	{
		this->enemyActionTimer += 100.f * deltaTime;
	}
}

// Timer to control how fast death animations happen in a state
void GameState::updateDeathTime(const float & deltaTime)
{
	if (this->deathTimer < this->deathTimeMax)
	{
		this->deathTimer += 100.f * deltaTime;
	}
}


// Destructor
GameState::~GameState()
{
	delete this->player;
	delete this->playerGUI;
	delete this->pauseMenu;
	delete this->combatMenu;
}
