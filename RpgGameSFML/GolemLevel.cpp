#include "stdafx.h"
#include "GolemLevel.h"

// Constructor
GolemLevel::GolemLevel(StateData* stateInfo, std::string playerType, unsigned playerLevel, std::string backgroundFile)
	: GameState(stateInfo, playerType, playerLevel, backgroundFile)
{
	this->initializeKeybinds("Config/golemLevelKeybinds.ini");
	this->initializeTextures();
	this->initializeBoss();
	this->initializeBossUI();
	this->initializeMinions();
	this->initializeMinionUI();
}

// Initializes the texture of the background and player character based on chosen character from
// the character selection screen (choices are mage and knight)
void GolemLevel::initializeTextures()
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

	if (!this->stateTextures["FIRE_GOLEM"].loadFromFile("Sprites/fireGolemSheet.png"))
	{
		throw "ERROR:GAME_STATE::MISSING_ENEMY_TEXTURE";
	}

	if (!this->stateTextures["ICE_GOLEM"].loadFromFile("Sprites/iceGolemSheet.png"))
	{
		throw "ERROR:GAME_STATE::MISSING_ENEMY_TEXTURE";
	}
	
	if (!this->stateTextures["STONE_GOLEM"].loadFromFile("Sprites/stoneGolemSheet.png"))
	{
		throw "ERROR:GAME_STATE::MISSING_ENEMY_TEXTURE";
	}
	
}

// Creates a new Ice Golem enemy, setting its texture and position on the screen
void GolemLevel::initializeBoss()
{
	// Sets starting positions in windowed mode
	float startingPosX = 1100;
	float startingPosY = this->window->getSize().y * 0.75f;
	bool scaleScreen = this->stateInfo->graphicsSettings->isFullScreen;
	// Sets starting positions in fullscreen mode
	if (scaleScreen)
	{
		startingPosX = 1100 * 1.45f;
		startingPosY = 1260 * 0.62f;
	}

	this->boss = new IceGolem(this->stateTextures["ICE_GOLEM"], startingPosX, startingPosY, "Config/GolemStats.txt", "Config/GolemMoveset.txt", scaleScreen);
}

// Creates a UI for the boss of the level
void GolemLevel::initializeBossUI()
{
	this->bossUI = new EnemyUI(this->boss, "Ice Golem", 1.045f, 1.f, 6.f);
}

// Creates new Fire and Stone Golem enemies, setting their texture and position on the screen
void GolemLevel::initializeMinions()
{
	// Sets starting positions in windowed mode
	float startingPosX = 975;
	float secondStartX = 825;
	float startingPosY = this->window->getSize().y * 0.75f;
	float secondStartY = startingPosY - 10.f;
	bool scaleScreen = this->stateInfo->graphicsSettings->isFullScreen;
	// Sets starting positions in fullscreen mode
	if (scaleScreen)
	{
		startingPosX = (startingPosX - 20.f) * 1.45f;
		secondStartX = (secondStartX - 4.f) * 1.45f;
		startingPosY = (startingPosY + 10.f) * 0.95f;
		secondStartY *= 0.95f;
	}

	this->minion1 = new FireGolem(this->stateTextures["FIRE_GOLEM"], startingPosX, startingPosY, "Config/GolemStats.txt", "Config/GolemMoveset.txt", scaleScreen);
	this->minion2 = new StoneGolem(this->stateTextures["STONE_GOLEM"], secondStartX, secondStartY, "Config/GolemStats.txt", "Config/GolemMoveset.txt", scaleScreen);
}

// Creates a UI for the minions of the level
void GolemLevel::initializeMinionUI()
{
	this->minionUI1 = new EnemyUI(this->minion1, "Fire Golem", 1.045f, 1.04f, 6.f);
	this->minionUI2 = new EnemyUI(this->minion2, "Stone Golem", 1.08f, 1.035f, 6.f);
}

// Updates the pause menu when pushed on the stack
void GolemLevel::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT_GAME"))
	{

		this->states->push(new MainMenuState(this->stateInfo));
	}
}

//Updates player input for movement
void GolemLevel::updatePlayerInput(const float & deltaTime)
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

//Updates elements of the UI for all enemies
void GolemLevel::updateEnemyUI(const float & deltaTime)
{
	this->bossUI->updateUI(deltaTime);
	this->minionUI1->updateUI(deltaTime);
	this->minionUI2->updateUI(deltaTime);
}

void GolemLevel::updateState(const float & deltaTime)
{
	this->updateMousePositions();
	this->updateKeyboardtime(deltaTime);
	this->updateInput(deltaTime);

	// If the player dies push DEAD endgame screen
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
		this->updateEnemyUI(deltaTime);

		// Updates level 1 enemies on the state
		this->boss->update(deltaTime);
		this->minion1->update(deltaTime);
		this->minion2->update(deltaTime);
	}
	else
	{
		this->pauseMenu->updateMenu(this->mousPositView);
		this->updatePauseMenuButtons();
	}

}

// Renders all necessary elements to the screen
void GolemLevel::renderState(sf::RenderTarget * target)
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
	this->minion2->renderEntity(*target);
	this->minion1->renderEntity(*target);
	this->minionUI1->renderUI(*target);
	this->minionUI2->renderUI(*target);

	// Render pause menu
	if (this->isPaused)
	{
		this->pauseMenu->renderMenu(target);
	}
}

