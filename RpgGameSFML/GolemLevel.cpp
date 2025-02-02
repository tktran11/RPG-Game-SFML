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
	this->initializeNextLevelButton();
}

// Initializes the texture of the background and player character based on chosen character from
// the character selection screen (choices are mage and knight)
void GolemLevel::initializeTextures()
{
	// loads mage texture otherwise throws an exception
	if (this->chosenCharacter == "mage") {
		if (!this->stateTextures["PLAYER_SPRITES"].loadFromFile("Sprites/mageSheet.png"))
		{
			throw "ERROR:GAME_STATE::MISSING_PLAYER_TEXTURE";
		}
	}
	// loads knight texture otherwise throws an exception
	else {
		if (!this->stateTextures["PLAYER_SPRITES"].loadFromFile("Sprites/knightSheet.png"))
		{
			throw "ERROR:GAME_STATE::MISSING_PLAYER_TEXTURE";
		}
	}

	// loads fire golem texture otherwise throws an exception
	if (!this->stateTextures["FIRE_GOLEM"].loadFromFile("Sprites/fireGolemSheet.png"))
	{
		throw "ERROR:GAME_STATE::MISSING_ENEMY_TEXTURE";
	}

	// loads ice golem texture otherwise throws an exception
	if (!this->stateTextures["ICE_GOLEM"].loadFromFile("Sprites/iceGolemSheet.png"))
	{
		throw "ERROR:GAME_STATE::MISSING_ENEMY_TEXTURE";
	}

	// loads stone golem texture otherwise throws an exception
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

	// Creates ice golem boss
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

	// Creates golem minions for the level
	this->minion1 = new StoneGolem(this->stateTextures["STONE_GOLEM"], secondStartX, secondStartY, "Config/GolemStats.txt", "Config/GolemMoveset.txt", scaleScreen);
	this->minion2 = new FireGolem(this->stateTextures["FIRE_GOLEM"], startingPosX, startingPosY, "Config/GolemStats.txt", "Config/GolemMoveset.txt", scaleScreen);
}

// Creates a UI for the minions of the level
void GolemLevel::initializeMinionUI()
{
	this->minionUI1 = new EnemyUI(this->minion1, "Fire Golem", 1.045f, 1.04f, 6.f);
	this->minionUI2 = new EnemyUI(this->minion2, "Stone Golem", 1.08f, 1.035f, 6.f);
}

// Initializes the button to push the next state
void GolemLevel::initializeNextLevelButton()
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
void GolemLevel::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT_GAME"))
	{
		this->states->push(new MainMenuState(this->stateInfo));
	}
}

// Updates the combat menu when pushed on the stack
void GolemLevel::updateCombatMenuButtons()
{
	// Knight moveset
	if (this->chosenCharacter == "knight")
	{
		// Executes standard attack (COSTS NO MANA)
		if (this->combatMenu->isButtonPressed("MOVE_1") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability1Mana")
			&& this->getPlayerActionTimer())
		{
			// Targets minion 1
			if (!this->minion1->getAttributeComponent()->isDead)
			{
				this->player->dealDamage(this->minion1,
					(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Slash")) - this->minion1->getStatNumbers("DEF"));
				this->minion1->checkForDamagedAnimation(true);
				this->player->loseMana(this->player->getAbilityNumbers("Ability1Mana"));
			}
			// Targets minion 2
			else if (!this->minion2->getAttributeComponent()->isDead)
			{
				this->player->dealDamage(this->minion2,
					(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Slash")) - this->minion2->getStatNumbers("DEF"));
				this->minion2->checkForDamagedAnimation(true);
				this->player->loseMana(this->player->getAbilityNumbers("Ability1Mana"));
			}
			// Targets boss
			else if (!this->boss->getAttributeComponent()->isDead)
			{
				this->player->dealDamage(this->boss, (
					this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Slash")) - this->boss->getStatNumbers("DEF"));
				this->boss->checkForDamagedAnimation(true);
				this->player->loseMana(this->player->getAbilityNumbers("Ability1Mana"));
			}
			this->player->checkForAttackAnimation(true);
			this->playerActed = true;
		}

		// Other moves in loop because they require mana
		if (this->player->getCurrentMana() > 0)
		{
			// Executes stat buff
			if (this->combatMenu->isButtonPressed("MOVE_2") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability2Mana")
				&& this->getPlayerActionTimer())
			{
				this->player->statMod("DEF", this->player->getAbilityNumbers("Fortify"));
				this->player->loseMana(this->player->getAbilityNumbers("Ability2Mana"));
				this->playerActed = true;
			}

			// Executes enemy debuff
			if (this->combatMenu->isButtonPressed("MOVE_3") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability3Mana")
				&& this->getPlayerActionTimer())
			{
				// Debuffs minion 1
				if (!this->minion1->getAttributeComponent()->isDead)
				{
					this->minion1->statMod("ATK", this->player->getAbilityNumbers("Taunt"));
					this->player->loseMana(this->player->getAbilityNumbers("Ability3Mana"));
				}
				// Debuffs minion 2
				else if (!this->minion2->getAttributeComponent()->isDead)
				{
					this->minion2->statMod("ATK", this->player->getAbilityNumbers("Taunt"));
					this->player->loseMana(this->player->getAbilityNumbers("Ability3Mana"));
				}

				// Debuffs minion 3
				else if (!this->boss->getAttributeComponent()->isDead)
				{
					this->boss->statMod("ATK", this->player->getAbilityNumbers("Taunt"));
					this->player->loseMana(this->player->getAbilityNumbers("Ability3Mana"));
				}
				this->playerActed = true;
			}

			// Executes powerful attack
			if (this->combatMenu->isButtonPressed("MOVE_4") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability4Mana")
				&& this->getPlayerActionTimer())

			{
				this->player->checkForAttackAnimation(true);
				// Targets minion 1
				if (!this->minion1->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->minion1,
						(this->player->getStatNumbers("ATK") * this->player->getAbilityNumbers("ShieldBash")) - this->minion1->getStatNumbers("DEF"));
					this->minion1->checkForDamagedAnimation(true);
					this->player->loseMana(this->player->getAbilityNumbers("Ability4Mana"));
				}
				// Targets minion 2
				else if (!this->minion2->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->minion2,
						(this->player->getStatNumbers("ATK") * this->player->getAbilityNumbers("ShieldBash")) - this->minion2->getStatNumbers("DEF"));
					this->minion2->checkForDamagedAnimation(true);
					this->player->loseMana(this->player->getAbilityNumbers("Ability4Mana"));
				}
				// Targets boss
				else if (!this->boss->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->boss,
						(this->player->getStatNumbers("ATK") * this->player->getAbilityNumbers("ShieldBash")) - this->boss->getStatNumbers("DEF"));
					this->boss->checkForDamagedAnimation(true);
					this->player->loseMana(this->player->getAbilityNumbers("Ability4Mana"));
				}
				this->playerActed = true;
			}
		}
	}

	// Mage moveset
	else
	{
		// So long as the mage doesnt go OOM
		if (this->player->getCurrentMana() > 0)
		{
			// Execute standard attack
			if (this->combatMenu->isButtonPressed("MOVE_1") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability1Mana")
				&& this->getPlayerActionTimer())
			{
				this->player->checkForAttackAnimation(true);
				// Targets minion 1
				if (!this->minion1->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->minion1,
						(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Hexplosion")) - this->minion1->getStatNumbers("DEF"));
					this->minion1->checkForDamagedAnimation(true);
					this->player->loseMana(this->player->getAbilityNumbers("Ability1Mana"));
				}
				// Targets minion 2
				else if (!this->minion2->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->minion2,
						(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Hexplosion")) - this->minion2->getStatNumbers("DEF"));
					this->minion2->checkForDamagedAnimation(true);
					this->player->loseMana(this->player->getAbilityNumbers("Ability1Mana"));
				}
				// Targets boss
				else if (!this->boss->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->boss,
						(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Hexplosion")) - this->boss->getStatNumbers("DEF"));
					this->boss->checkForDamagedAnimation(true);
					this->player->loseMana(this->player->getAbilityNumbers("Ability1Mana"));
				}
				this->playerActed = true;
			}

			// Execute stat buff
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

			// Execute healing attack
			if (this->combatMenu->isButtonPressed("MOVE_3") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability3Mana")
				&& this->getPlayerActionTimer())

			{
				this->player->checkForAttackAnimation(true);
				{
					// Targets minion 1
					if (!this->minion1->getAttributeComponent()->isDead)
					{
						this->player->dealDamage(this->minion1,
							(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Dark Ignition")) - this->minion1->getStatNumbers("DEF"));
						this->minion1->checkForDamagedAnimation(true);
					}
					// Targets minion 2
					else if (!this->minion2->getAttributeComponent()->isDead)
					{
						this->player->dealDamage(this->minion2,
							(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Dark Ignition")) - this->minion2->getStatNumbers("DEF"));
						this->minion2->checkForDamagedAnimation(true);
					}
					// Targets boss
					else if (!this->boss->getAttributeComponent()->isDead)
					{
						this->player->dealDamage(this->boss,
							(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Dark Ignition")) - this->boss->getStatNumbers("DEF"));
						this->boss->checkForDamagedAnimation(true);
					}
				}
				// Heal based on attack stat
				this->player->gainHP(this->player->getStatNumbers("ATK"));
				this->player->loseMana(this->player->getAbilityNumbers("Ability3Mana"));
				this->playerActed = true;
			}

			// Execute AOE attack
			if (this->combatMenu->isButtonPressed("MOVE_4") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability4Mana")
				&& this->getPlayerActionTimer())

			{
				this->player->checkForAttackAnimation(true);
				//deals damage to minion 1 if alive
				if (!this->minion1->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->minion1,
						(this->player->getStatNumbers("ATK") * this->player->getAbilityNumbers("ObsidianSweep")) - this->minion1->getStatNumbers("DEF"));
					this->minion1->checkForDamagedAnimation(true);
				}
				//deals damage to minion 2 if alive
				if (!this->minion2->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->minion2,
						(this->player->getStatNumbers("ATK") * this->player->getAbilityNumbers("ObsidianSweep")) - this->minion2->getStatNumbers("DEF"));
					this->minion2->checkForDamagedAnimation(true);
				}
				//deals damage to boss if alive
				if (!this->boss->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->boss,
						(this->player->getStatNumbers("ATK") * this->player->getAbilityNumbers("ObsidianSweep")) - this->boss->getStatNumbers("DEF"));
					this->boss->checkForDamagedAnimation(true);
				}
				this->player->loseMana(this->player->getAbilityNumbers("Ability4Mana"));
				this->playerActed = true;
			}
		}
		// If OOM, kills player
		else if (this->player->getCurrentMana() == 0)
		{
			this->playerActed = true;
		}
	}

	// Enemy combat
	if (this->playerActed && this->getEnemyActionTimer())
	{
		// Minion 1 attacks while it isnt dead
		if (!this->minion1->getAttributeComponent()->isDead)
		{
			this->minion1->checkForAttackAnimation(true);
			if (this->minion1->getStatNumbers("ATK") - this->player->getStatNumbers("DEF") >= 0)
			{
				this->minion1->dealDamage(this->player,
					this->minion1->getStatNumbers("ATK") - this->player->getStatNumbers("DEF"));
				this->playerActed = false;
				this->minion1->checkForDamagedAnimation(false);
			}
		}
		// Minion 2 attacks while it isnt dead
		if (!this->minion2->getAttributeComponent()->isDead)
		{
			this->minion2->checkForAttackAnimation(true);
			if (this->minion2->getStatNumbers("ATK") - this->player->getStatNumbers("DEF") >= 0)
			{
				this->minion2->dealDamage(this->player,
					this->minion2->getStatNumbers("ATK") - this->player->getStatNumbers("DEF"));
				this->playerActed = false;
				this->minion2->checkForDamagedAnimation(false);
			}
		}
		// Boss attacks while it isnt dead
		if (!this->boss->getAttributeComponent()->isDead)
		{
			this->boss->checkForAttackAnimation(true);
			if (this->boss->getStatNumbers("ATK") - this->player->getStatNumbers("DEF") >= 0)
			{
				this->boss->dealDamage(this->player,
					this->boss->getStatNumbers("ATK") - this->player->getStatNumbers("DEF"));
				this->playerActed = false;
				this->boss->checkForDamagedAnimation(false);
			}
		}
	}
}

// Updates the button to push next level state
void GolemLevel::updateNextLevelButton()
{
	this->nextLevel->updateButton(this->mousPositView);
	if (this->nextLevel->isPressed())
	{
		this->states->push(new BossLevel(this->stateInfo, this->chosenCharacter, 3, "MenuTextures/GameBackground/Map3.png"));
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
	this->updateDeathTime(deltaTime);
	this->updateInput(deltaTime);
	this->updateCombat(deltaTime);

	// If everyone is dead set a bool for the render
	if (this->minion1->getAttributeComponent()->isDead && this->minion2->getAttributeComponent()->isDead && this->boss->getAttributeComponent()->isDead)
	{
		this->updateNextLevelButton();
		this->allDead = true;
	}

	// If the player dies push DEAD endgame screen
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

		// Updates if the player is in combat
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
	// Updates menus
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

	//Renders level 2 enemies (Elemental Golems)
	this->boss->renderEntity(*target);
	this->minion2->renderEntity(*target);
	this->minion1->renderEntity(*target);

	// Play death animation when boss dies then de-render
	if (this->boss->getAttributeComponent()->isDead)
	{
		while (!bossDead && this->getDeathTimer())
		{
			if (this->boss->playDeathAnimation(200.f))
			{
				bossDead = true;
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
		while (!minion1Dead && this->getDeathTimer())
		{
			if (this->minion1->playDeathAnimation(100.f))
			{
				minion1Dead = true;
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
		while (!minion2Dead && this->getDeathTimer())
		{
			if (this->minion2->playDeathAnimation(100.f))
			{
				minion2Dead = true;
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
		{// howd you de render the combat menu
			this->combatMenu->renderMenu(target);
		}
	}
}

