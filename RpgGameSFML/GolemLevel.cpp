#include "stdafx.h"
#include "GolemLevel.h"


GolemLevel::GolemLevel(StateData* stateInfo, std::string playerType, unsigned playerLevel, std::string backgroundFile)
	: GameState(stateInfo, playerType, playerLevel, backgroundFile)
{
	this->initializeKeybinds("Config/golemLevelKeybinds.ini");
	this->initializeTextures();
	this->initializeBoss();
	this->initializeMinions();
}

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

	this->boss = new IceGolem(this->stateTextures["ICE_GOLEM"], startingPosX, startingPosY, scaleScreen);
}

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

	this->minion1 = new FireGolem(this->stateTextures["FIRE_GOLEM"], startingPosX, startingPosY, scaleScreen);
	this->minion2 = new StoneGolem(this->stateTextures["STONE_GOLEM"], secondStartX, secondStartY, scaleScreen);
}

void GolemLevel::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT_GAME"))
	{

		this->states->push(new MainMenuState(this->stateInfo));
	}
}

void GolemLevel::updatePlayerInput(const float & deltaTime)
{

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

void GolemLevel::updateState(const float & deltaTime)
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
	this->minion2->renderEntity(*target);
	this->minion1->renderEntity(*target);

	// Render pause menu
	if (this->isPaused)
	{
		this->pauseMenu->renderMenu(target);
	}
}

