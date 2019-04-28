#include "stdafx.h"
#include "SlimeLevel.h"

// Constructor
SlimeLevel::SlimeLevel(StateData* stateInfo, std::string playerType, unsigned playerLevel, std::string backgroundFile)
	: GameState(stateInfo, playerType, playerLevel, backgroundFile)
{
	this->initializeKeybinds("Config/slimeLevelKeybinds.ini");
	this->initializeTextures();
	this->initializeBoss();
	this->initializeBossUI();
	this->initializeMinions();
	this->initializeMinionUI();
}


// Initializes the texture of the background and player character based on chosen character from
// the character selection screen (choices are mage and knight)
void SlimeLevel::initializeTextures()
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

// Creates a new shade enemy, setting its texture and position on the screen
void SlimeLevel::initializeBoss()
{
	// Sets starting positions in windowed mode
	float startingPosX = 1100;
	float startingPosY = this->window->getSize().y * 0.75f;
	bool scaleScreen = this->stateInfo->graphicsSettings->isFullScreen;
	// Sets starting positions in fullscreen mode
	if (scaleScreen)
	{
		startingPosX = 1100 * 1.45f;
		startingPosY = 1280 * 0.62f;
	}

	this->boss = new Shade(this->stateTextures["SHADE_SPRITE"], startingPosX, startingPosY, "Config/ShadeStats.txt", "Config/ShadeMoveset.txt", scaleScreen);
}

// Creates a UI for the boss of the level
void SlimeLevel::initializeBossUI()
{
	this->bossUI = new EnemyUI(this->boss, "Shade", 1.0475f, 1.05f, -11.f);
}

//Creates a new slime enemy, setting its texture and position on the screen
void SlimeLevel::initializeMinions()
{
	// Sets starting positions in windowed mode
	float startingPosX = 1075;
	float secondStartX = startingPosX - 100;
	float startingPosY = this->window->getSize().y * 0.85f;
	float secondStartY = startingPosY * 1.04f;
	bool scaleScreen = this->stateInfo->graphicsSettings->isFullScreen;
	// Sets starting positions in fullscreen mode
	if (scaleScreen)
	{
		startingPosX *= 1.45f;
		secondStartX *= 1.45f;

	}

	this->minion1 = new Slime(this->stateTextures["SLIME_SPRITE"], startingPosX, startingPosY, "SlimeStats.txt", "Config/SlimeMoveset.txt", scaleScreen);
	this->minion2 = new Slime(this->stateTextures["SLIME_SPRITE"], secondStartX, secondStartY, "SlimeStats.txt", "Config/SlimeMoveset.txt", scaleScreen);
}

// Creates a UI for the minions of the level
void SlimeLevel::initializeMinionUI()
{
	this->minionUI1 = new EnemyUI(this->minion1, "Slime", 0.98f, 1.f, -10.f);
	this->minionUI2 = new EnemyUI(this->minion2, "Slime", 0.98f, 1.f, -10.f);
}

// Updates the pause menu when pushed on the stack
void SlimeLevel::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT_GAME"))
	{

		this->states->push(new MainMenuState(this->stateInfo));
	}
}

// Updates the player input for movement
void SlimeLevel::updatePlayerInput(const float & deltaTime)
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
		this->player->move(deltaTime, 0.f, 0.4f);
	}
	
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP")))) && (this->player->getYPosition() >= this->player->getStartPosY() - 10.f))
	{
		this->player->move(deltaTime, 0.f, -0.4f);
	}
}

// Updates elements of the UI for all enemies
void SlimeLevel::updateEnemyUI(const float& deltaTime)
{
	this->bossUI->updateUI(deltaTime);
	this->minionUI1->updateUI(deltaTime);
	this->minionUI2->updateUI(deltaTime);
}

// Handles checking for input and player updates for each frame 
void SlimeLevel::updateState(const float & deltaTime)
{
	this->updateMousePositions();
	this->updateKeyboardtime(deltaTime);
	this->updateInput(deltaTime);

	//If the player dies pushes DEAD endgame screen
	if (this->player->getAttributeComponent()->isDead)
	{
	
		this->states->push(new EndGameScreen(this->stateInfo, true));
	}

	// Update state while unpaused
	if (!this->isPaused) {
		// Updated player related functions on the state
		this->updatePlayerInput(deltaTime);
		this->player->update(deltaTime);
		this->playerGUI->updateUI(deltaTime);

		// Updates level 1 enemies on the state
		this->boss->update(deltaTime);
		this->minion1->update(deltaTime);
		this->minion2->update(deltaTime);
		this->updateEnemyUI(deltaTime);
	}
	else
	{
		this->pauseMenu->updateMenu(this->mousPositView);
		this->updatePauseMenuButtons();
	}

}

// Renders all necessary elements to the screen
void SlimeLevel::renderState(sf::RenderTarget * target)
{
	if (!target) {
		target = this->window;
	}
	target->draw(this->background);

	//Render player and player UI to the screen
	this->player->renderEntity(*target);
	this->playerGUI->renderUI(*target);

	//Renders level 1 enemies (Slime + Shade)
	this->boss->renderEntity(*target);
	this->bossUI->renderUI(*target);
	this->minion1->renderEntity(*target);
	this->minion2->renderEntity(*target);
	this->minionUI1->renderUI(*target);
	this->minionUI2->renderUI(*target);

	// Render pause menu
	if (this->isPaused)
	{
		this->pauseMenu->renderMenu(target);
	}
}
