#include "stdafx.h"
#include "BossLevel.h"

// Constructor
BossLevel::BossLevel(StateData* stateInfo, std::string playerType, unsigned playerLevel, std::string backgroundFile)
	: GameState(stateInfo, playerType, playerLevel, backgroundFile)
{
	this->initializeKeybinds("Config/bossLevelKeybinds.ini");
	this->initializeTextures();
	this->initializeBoss();
	this->initializeBossUI();
}

// Initializes the texture of the background and player character based on chosen character from
// the character selection screen (choices are mage and knight)
void BossLevel::initializeTextures()
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
	if (!this->stateTextures["MINOTAUR"].loadFromFile("Sprites/minotaurSheet.png"))
	{
		throw "ERROR:GAME_STATE::MISSING_ENEMY_TEXTURE";
	}
}

// Creates a minotaur enemy, setting its texture and position on the screen
void BossLevel::initializeBoss()
{
	// Sets starting positions in windowed mode
	float startingPosX = 1000;
	float startingPosY = this->window->getSize().y * 0.65f;
	bool scaleScreen = this->stateInfo->graphicsSettings->isFullScreen;
	// Sets starting positions in fullscreen mode
	if (scaleScreen)
	{
		startingPosX = 1100 * 1.34f;
		startingPosY = 1260 * 0.53f;
	}

	this->boss = new Minotaur(this->stateTextures["MINOTAUR"], startingPosX, startingPosY, "Config/MinotaurStats.txt", "Config/MinotaurMoveset.txt", scaleScreen);
}

// Creates a UI for the boss of the level
void BossLevel::initializeBossUI()
{
	this->bossUI = new EnemyUI(this->boss, "Minotaur", 1.1f, 1.15f, 8.f);
}

// Updates the pause menu when pushed on the stack
void BossLevel::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT_GAME"))
	{

		this->states->push(new MainMenuState(this->stateInfo));
	}
}

// Updates the player input for movement
void BossLevel::updatePlayerInput(const float & deltaTime)
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

// Updates the UI for all enemies
void BossLevel::updateEnemyUI(const float & deltaTime)
{
	this->bossUI->updateUI(deltaTime);
}

// Handles checking for input and player updates for each frame
void BossLevel::updateState(const float & deltaTime)
{
	this->updateMousePositions();
	this->updateKeyboardtime(deltaTime);
	this->updateDeathTime(deltaTime);
	this->updateInput(deltaTime);

	// If the player kills the minotaur push WIN endgame screen
	if (this->boss->getAttributeComponent()->isDead && this->getDeathTimer())
	{
		if (this->boss->playDeathAnimation(400.f))
		{
			this->bossDead = true;
			this->boss->disappear();
			this->player->gainEXP(this->boss->getAttributeComponent()->stats["EXP"]);
			if (this->bossDead)
			{
				this->states->push(new EndGameScreen(this->stateInfo, true));
			}

		}
	}

	// If the player dies pushes DEAD endgame screen
	if (this->player->getAttributeComponent()->isDead)
	{

		this->states->push(new EndGameScreen(this->stateInfo, false));
	}

	// Update state while unpaused
	if (!this->isPaused) {
		// Updated player related functions on the state
		this->updatePlayerInput(deltaTime);
		this->player->update(deltaTime);
		this->playerGUI->updateUI(deltaTime);
		this->boss->update(deltaTime);
		this->updateEnemyUI(deltaTime);
	}
	else
	{
		this->pauseMenu->updateMenu(this->mousPositView);
		this->updatePauseMenuButtons();
	}

}

// Renders all necessary elements to the screen
void BossLevel::renderState(sf::RenderTarget * target)
{
	if (!target) {
		target = this->window;
	}
	target->draw(this->background);

	//Render player and player UI to the screen
	this->player->renderEntity(*target);
	this->playerGUI->renderUI(*target);

	this->boss->renderEntity(*target);

	this->bossUI->renderUI(*target);

	// Render pause menu
	if (this->isPaused)
	{
		this->pauseMenu->renderMenu(target);
	}
}
