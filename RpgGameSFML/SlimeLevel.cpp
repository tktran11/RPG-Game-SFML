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
	this->initializeNextLevelButton();
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
	this->minion1 = new Slime(this->stateTextures["SLIME_SPRITE"], secondStartX, secondStartY, "Config/SlimeStats.txt", "Config/SlimeMoveset.txt", scaleScreen);
	this->minion2 = new Slime(this->stateTextures["SLIME_SPRITE"], startingPosX, startingPosY, "Config/SlimeStats.txt", "Config/SlimeMoveset.txt", scaleScreen);
}

// Creates a UI for the minions of the level
void SlimeLevel::initializeMinionUI()
{
	this->minionUI1 = new EnemyUI(this->minion1, "Slime", 0.98f, 1.f, -10.f);
	this->minionUI2 = new EnemyUI(this->minion2, "Slime", 0.98f, 1.f, -10.f);
}

void SlimeLevel::initializeNextLevelButton()
{
	// Sets starting positions in windowed mode
	float startingPosX = 1150;
	float secondStartX = startingPosX - 100;
	float startingPosY = this->window->getSize().y * .875;
	float secondStartY = startingPosY * 1.04f;
	bool scaleScreen = this->stateInfo->graphicsSettings->isFullScreen;
	// Sets starting positions in fullscreen mode
	if (scaleScreen)
	{
		startingPosX *= 1.45f;
		secondStartX *= 1.45f;

	}
	this->nextLevel = new gui::Button(startingPosX, startingPosY, 100, 100, "MenuTextures/NextLevel.png");
}

// Updates the pause menu when pushed on the stack
void SlimeLevel::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT_GAME"))
	{
		this->states->push(new MainMenuState(this->stateInfo));
	}
}

// Updates the combat menu when pushed on the stack
void SlimeLevel::updateCombatMenuButtons()
{
	// Knight moveset
	if (this->chosenCharacter == "knight")
	{
		// Executes combat with move 1 (COSTS NO MANA)
		if (this->combatMenu->isButtonPressed("MOVE_1") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability1Mana") 
			&& this->getPlayerActionTimer())
		{
			if (!this->minion1->getAttributeComponent()->isDead)
			{
				this->player->dealDamage(this->minion1,
					(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Slash")) - this->minion1->getStatNumbers("DEF"));
				this->player->loseMana(this->player->getAbilityNumbers("Ability1Mana"));
			}
			else if (!this->minion2->getAttributeComponent()->isDead)
			{
				this->player->dealDamage(this->minion2,
					(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Slash")) - this->minion2->getStatNumbers("DEF"));
				this->player->loseMana(this->player->getAbilityNumbers("Ability1Mana"));
			}
			else if (!this->boss->getAttributeComponent()->isDead)
			{
				this->player->dealDamage(this->boss, (
					this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Slash")) - this->boss->getStatNumbers("DEF"));
				this->player->loseMana(this->player->getAbilityNumbers("Ability1Mana"));
			}
			this->player->checkForAttackAnimation(true);
			this->playerActed = true;
		}

		// Other moves in loop because they require mana
		if (this->player->getCurrentMana() > 0)
		{
			// Executes combat with move 2
			if (this->combatMenu->isButtonPressed("MOVE_2") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability2Mana")
				&& this->getPlayerActionTimer())

			{
				this->player->statMod("DEF", this->player->getAbilityNumbers("Fortify"));
				this->player->loseMana(this->player->getAbilityNumbers("Ability2Mana"));
				this->playerActed = true;
			}

			// Executes combat with move 3
			if (this->combatMenu->isButtonPressed("MOVE_3") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability3Mana")
				&& this->getPlayerActionTimer())
			{
				if (!this->minion1->getAttributeComponent()->isDead)
				{
					this->minion1->statMod("ATK", this->player->getAbilityNumbers("Taunt"));
					this->player->loseMana(this->player->getAbilityNumbers("Ability3Mana"));
				}
				else if (!this->minion2->getAttributeComponent()->isDead)
				{
					this->minion2->statMod("ATK", this->player->getAbilityNumbers("Taunt"));
					this->player->loseMana(this->player->getAbilityNumbers("Ability3Mana"));
				}
				else if (!this->boss->getAttributeComponent()->isDead)
				{
					this->boss->statMod("ATK", this->player->getAbilityNumbers("Taunt"));
					this->player->loseMana(this->player->getAbilityNumbers("Ability3Mana"));
				}
				this->playerActed = true;
			}

			// Executes combat with move 4
			if (this->combatMenu->isButtonPressed("MOVE_4") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability4Mana")
				&& this->getPlayerActionTimer())

			{
				this->player->checkForAttackAnimation(true);
				if (!this->minion1->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->minion1,
						(this->player->getStatNumbers("ATK") * this->player->getAbilityNumbers("ShieldBash")) - this->minion1->getStatNumbers("DEF"));
					this->player->loseMana(this->player->getAbilityNumbers("Ability4Mana"));
				}
				else if (!this->minion2->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->minion2,
						(this->player->getStatNumbers("ATK") * this->player->getAbilityNumbers("ShieldBash")) - this->minion2->getStatNumbers("DEF"));
					this->player->loseMana(this->player->getAbilityNumbers("Ability4Mana"));
				}
				else if (!this->boss->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->boss,
						(this->player->getStatNumbers("ATK") * this->player->getAbilityNumbers("ShieldBash")) - this->boss->getStatNumbers("DEF"));
					this->player->loseMana(this->player->getAbilityNumbers("Ability4Mana"));
				}
				this->playerActed = true;
			}
		}
	}

	// Mage moveset
	else
	{
		// Execute combat based on first move in set
		if (this->player->getCurrentMana() > 0)
		{
			// Execute combat based on first move in set
			if (this->combatMenu->isButtonPressed("MOVE_1") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability1Mana")
				&& this->getPlayerActionTimer())

			{
				this->player->checkForAttackAnimation(true);
				if (!this->minion1->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->minion1,
						(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Hexplosion")) - this->minion1->getStatNumbers("DEF"));
					this->player->loseMana(this->player->getAbilityNumbers("Ability1Mana"));
				}
				else if (!this->minion2->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->minion2,
						(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Hexplosion")) - this->minion2->getStatNumbers("DEF"));
					this->player->loseMana(this->player->getAbilityNumbers("Ability1Mana"));
				}
				else if (!this->boss->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->boss,
						(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Hexplosion")) - this->boss->getStatNumbers("DEF"));
					this->player->loseMana(this->player->getAbilityNumbers("Ability1Mana"));
				}
				this->playerActed = true;
			}

			// Execute combat based on second move in set
			if (this->combatMenu->isButtonPressed("MOVE_2") && this->player->getCurrentMana() > 0 && this->player->getCurrentMana() < this->player->getMaxMana() 
				&& this->getPlayerActionTimer())
			{
				// Check to see if mage (only mage can power up)
				if (this->chosenCharacter == "mage")
				{
					this->player->checkForPowerUpAnimation(true);
					this->player->statMod("ATK", this->player->getAbilityNumbers("DisciplinedThinking"));
					this->player->statMod("SPD", this->player->getAbilityNumbers("DisciplinedThinking"));
					this->player->gainMana(this->player->getAbilityNumbers("Ability2Mana"));
				}
				else
				{
					this->player->checkForAttackAnimation(true);
				}
			}

			// Execute combat based on third move in set
			if (this->combatMenu->isButtonPressed("MOVE_3") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability3Mana")
				&& this->getPlayerActionTimer())

			{
				this->player->checkForAttackAnimation(true);
				{
					if (!this->minion1->getAttributeComponent()->isDead)
					{
						this->player->dealDamage(this->minion1,
							(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Dark Ignition")) - this->minion1->getStatNumbers("DEF"));
					}
					else if (!this->minion2->getAttributeComponent()->isDead)
					{
						this->player->dealDamage(this->minion2,
							(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Dark Ignition")) - this->minion2->getStatNumbers("DEF"));
					}
					else if (!this->boss->getAttributeComponent()->isDead)
					{
						this->player->dealDamage(this->boss,
							(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Dark Ignition")) - this->boss->getStatNumbers("DEF"));
					}
				}
				// Heal on attack
				this->player->gainHP(this->player->getStatNumbers("ATK"));
				this->player->loseMana(this->player->getAbilityNumbers("Ability3Mana"));
				this->playerActed = true;
			}

			// Execute combat based on fourth move in set
			if (this->combatMenu->isButtonPressed("MOVE_4") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability4Mana")
				&& this->getPlayerActionTimer())

			{
				this->player->checkForAttackAnimation(true);
				//deals damage to minion 1 if alive
				if (!this->minion1->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->minion1,
						(this->player->getStatNumbers("ATK") * this->player->getAbilityNumbers("ObsidianSweep")) - this->minion1->getStatNumbers("DEF"));
				}
				//deals damage to minion 2 if alive
				if (!this->minion2->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->minion2,
						(this->player->getStatNumbers("ATK") * this->player->getAbilityNumbers("ObsidianSweep")) - this->minion2->getStatNumbers("DEF"));
				}
				//deals damage to boss if alive
				if (!this->boss->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->boss,
						(this->player->getStatNumbers("ATK") * this->player->getAbilityNumbers("ObsidianSweep")) - this->boss->getStatNumbers("DEF"));
				}
				this->player->loseMana(this->player->getAbilityNumbers("Ability4Mana"));
				this->playerActed = true;
			}
		}
		else if (this->player->getCurrentMana() == 0)
		{
			this->playerActed = true;
		}
	}

	// Enemy combat
	if (this->playerActed && this->getEnemyActionTimer())
	{
		if (!this->minion1->getAttributeComponent()->isDead)
		{
			this->minion1->checkForAttackAnimation(true);
			if (this->minion1->getStatNumbers("ATK") - this->player->getStatNumbers("DEF") >= 0)
			{
				this->minion1->dealDamage(this->player,
					this->minion1->getStatNumbers("ATK") - this->player->getStatNumbers("DEF"));
				this->playerActed = false;
			}
		}
		if (!this->minion2->getAttributeComponent()->isDead)
		{
			this->minion2->checkForAttackAnimation(true);
			if (this->minion2->getStatNumbers("ATK") - this->player->getStatNumbers("DEF") >= 0)
			{
				this->minion2->dealDamage(this->player,
					this->minion2->getStatNumbers("ATK") - this->player->getStatNumbers("DEF"));
				this->playerActed = false;
			}
		}
		if (!this->boss->getAttributeComponent()->isDead)
		{
			this->boss->checkForAttackAnimation(true);
			if (this->boss->getStatNumbers("ATK") - this->player->getStatNumbers("DEF") >= 0)
			{
				this->boss->dealDamage(this->player,
					this->boss->getStatNumbers("ATK") - this->player->getStatNumbers("DEF"));
				this->playerActed = false;
			}
		}
	}
}

void SlimeLevel::updateNextLevelButton()
{
	this->nextLevel->updateButton(this->mousPositView);
	if (this->nextLevel->isPressed())
	{
		this->states->push(new GolemLevel(this->stateInfo, this->chosenCharacter, 2, "MenuTextures/GameBackground/Map2.png"));
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
	this->updateDeathTime(deltaTime);
	this->updateInput(deltaTime);
	this->updateCombat(deltaTime);
	
	// If everyone is dead set a bool for the render
	if (this->minion1->getAttributeComponent()->isDead && this->minion2->getAttributeComponent()->isDead && this->boss->getAttributeComponent()->isDead)
	{
		this->updateNextLevelButton();
		this->allDead = true;
	}

	//If the player dies pushes DEAD endgame screen
	if (this->player->getAttributeComponent()->isDead)
	{
		this->states->push(new EndGameScreen(this->stateInfo, false));
	}

	// Update state while unpaused
	if (!this->isPaused) {
		// Updated player related functions on the state
		this->player->update(deltaTime);
		this->playerGUI->updateUI(deltaTime);
		this->updateEnemyUI(deltaTime);
		this->boss->update(deltaTime);
		this->minion1->update(deltaTime);
		this->minion2->update(deltaTime);
		if (this->isInCombat)
		{
			this->updatePlayerActionTimer(deltaTime);
			this->updateEnemyActionTime(deltaTime);
			this->combatMenu->updateMenu(this->mousPositView);
			this->updateCombatMenuButtons();
		}
		else
		{
			this->updatePlayerInput(deltaTime);
		}
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
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);

	//Render player and player UI to the screen
	this->player->renderEntity(*target);
	this->playerGUI->renderUI(*target);

	// Renders level 1 enemies (Slime + Shade)
	this->boss->renderEntity(*target);
	this->minion1->renderEntity(*target);
	this->minion2->renderEntity(*target);
	// Play death animation when boss dies then de-render
	if (this->boss->getAttributeComponent()->isDead)
	{

		if (!bossDead && this->getDeathTimer())
		{
			if (this->boss->playDeathAnimation(600.f))
			{
				this->bossDead = true;
				this->player->gainEXP(this->boss->getAttributeComponent()->stats["EXP"]);
				this->boss->disappear();
			}
		}
	}
	else
	{
		this->bossUI->renderUI(*target);
	}

	// Play death animation when minion 1 dies, then de-render
	if (this->minion1->getAttributeComponent()->isDead)
	{
		if (!minion1Dead && this->getDeathTimer())
		{
			if (this->minion1->playDeathAnimation(100.f))
			{
				this->minion1Dead = true;
				this->player->gainEXP(this->minion1->getAttributeComponent()->stats["EXP"]);
				this->minion1->disappear();
			}
		}
	}
	else
	{
		this->minionUI1->renderUI(*target);
	}

	// Play death animation when minion 2 dies, then de-render
	if (this->minion2->getAttributeComponent()->isDead)
	{
		if (!minion2Dead && this->getDeathTimer())
		{
			if (this->minion2->playDeathAnimation(100.f))
			{
				this->minion2Dead = true;
				this->player->gainEXP(this->minion2->getAttributeComponent()->stats["EXP"]);
				this->minion2->disappear();
			}
		}
	}
	else
	{
		this->minionUI2->renderUI(*target);
	}

	// If all enemies are dead, render a button that pushes the next state
	if (this->allDead)
	{
		this->isInCombat = false;
		this->nextLevel->renderButton(*target);
	}

	// Render pause menu
	if (this->isPaused)
	{
		this->pauseMenu->renderMenu(target);
	}

	// Render combat menu
	if (this->isInCombat)
	{
		if (!this->isPaused)
		{
			this->combatMenu->renderMenu(target);
		}
	}
}
