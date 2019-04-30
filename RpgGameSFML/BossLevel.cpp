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
	// loads minotaur texture otherwise throws an exception
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
	// creates a new minotaur
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

// Updates the combat menu when pushed on the stack
void BossLevel::updateCombatMenuButtons()
{
	// Knight moveset
	if (this->chosenCharacter == "knight")
	{
		// Executes standard attack (COSTS NO MANA)
		if (this->combatMenu->isButtonPressed("MOVE_1") && this->player->getCurrentMana() >= this->player->getAbilityNumbers("Ability1Mana")
			&& this->getPlayerActionTimer())
		{
			// Targets boss
			if (!this->boss->getAttributeComponent()->isDead)
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
				// Debuffs boss
				if (!this->boss->getAttributeComponent()->isDead)
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
				// Targets boss
				if (!this->boss->getAttributeComponent()->isDead)
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
				// Targets boss
				if (!this->boss->getAttributeComponent()->isDead)
				{
					this->player->dealDamage(this->boss,
						(this->player->getStatNumbers("ATK") + this->player->getAbilityNumbers("Hexplosion")) - this->boss->getStatNumbers("DEF"));
					this->boss->checkForDamagedAnimation(true);
					this->player->loseMana(this->player->getAbilityNumbers("Ability1Mana"));
				}
				this->playerActed = true;
			}

			// Execute Stat buff
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
					// Targets boss
					if (!this->boss->getAttributeComponent()->isDead)
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
		// If oom, kills player
		else if (this->player->getCurrentMana() == 0)
		{
			this->playerActed = true;
		}
	}

	// Enemy combat
	if (this->playerActed && this->getEnemyActionTimer())
	{
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
	this->updateCombat(deltaTime);

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
		this->player->update(deltaTime);
		this->playerGUI->updateUI(deltaTime);
		this->updateEnemyUI(deltaTime);
		this->boss->update(deltaTime);

		// Updates if player is in combat
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
	
	// Render combat menu
	if (this->isInCombat)
	{
		if (!this->isPaused)
		{
			this->combatMenu->renderMenu(target);
		}
	}
}
