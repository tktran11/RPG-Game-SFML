#include "stdafx.h"
#include "PlayerCharacter.h"

/*
PlayerCharacter.cpp is the .cpp for the Player Character class, which is a virtual class that houses the
user's playable character's base functionality. Both playable characters
inherit features from this class.
It also stores information and houses components to manipulate the character.
*/

/* Constructor for the player character*/
PlayerCharacter::PlayerCharacter(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, unsigned level, 
	std::string statFile, std::string movesetFile, bool scaleScreen)
{
	this->startPositionX = startPointX;
	this->startPositionY = startPointY;
	this->setSpriteScale(scaleScreen);
	this->initializeComponents(spriteTextureSheet, level, statFile, movesetFile);
	this->initializeVariables(scaleScreen);
	this->setPosition(startPointX, startPointY);
}

// Assessor for the attribute component
CharacterAttributes * PlayerCharacter::getAttributeComponent()
{
	return this->attributeComponent;
}

// Returns the starting position of the player character in the X axis
float PlayerCharacter::getStartPosX()
{
	return this->startPositionX;
}

// Returns the starting position of the player character in the Y axis
float PlayerCharacter::getStartPosY()
{
	return this->startPositionY;
}

// Assessor for sprite scale
float PlayerCharacter::getSpriteScale()
{
	return this->scale;
}

// Scales the sprite for fullscreen applications if necessary
void PlayerCharacter::setSpriteScale(bool scaleScreen)
{
	if (scaleScreen)
	{
		this->scale = 1.5f;
	} 
	else
	{
		this->scale = 1.f;
	}
}

// Assessor for moveset numbers
float PlayerCharacter::getAbilityNumbers(std::string key)
{
	return this->attributeComponent->moveset[key];
}

// Assessor for stat numbers
int PlayerCharacter::getStatNumbers(std::string key)
{
	return this->attributeComponent->stats[key];
}

// Assessor for player's current mana
int PlayerCharacter::getCurrentMana()
{
	return this->attributeComponent->currentMana;
}

// Assessor for player's maximum mana
int PlayerCharacter::getMaxMana()
{
	return this->attributeComponent->maxMana;
}

// Assessor for dealing damage to the enemy
void PlayerCharacter::dealDamage(Enemy * enemy, const int damage)
{
	enemy->loseHP(damage);
}

// Subtracts HP from the player based on damage taken
void PlayerCharacter::loseHP(const int hpLost)
{
	this->attributeComponent->currentHP -= hpLost;
	if (this->attributeComponent->currentHP <= 0)
	{
		this->attributeComponent->isDead = true;
		this->attributeComponent->currentHP = 0;
	}
}

// Adds HP to the player based on amount gained
void PlayerCharacter::gainHP(const int hpGain)
{
	this->attributeComponent->currentHP += hpGain;

	if (this->attributeComponent->currentHP > this->attributeComponent->maxHP)
	{
		this->attributeComponent->currentHP = this->attributeComponent->maxHP;
	}
}

// Adds/removes stat values to a specific stat (buff/debuff)
void PlayerCharacter::statMod(std::string key, int modifier)
{
	this->attributeComponent->stats[key] += modifier;
}

// Subtracts mana from the player based on the amount spent
void PlayerCharacter::loseMana(const int manaLost)
{
	this->attributeComponent->currentMana -= manaLost;

	if (this->attributeComponent->currentMana < 0)
	{
		this->attributeComponent->currentMana = 0;
	}
}

// Returns mana to the player and changes the mana if it goes over cap
void PlayerCharacter::gainMana(const int manaGain)
{
	this->attributeComponent->currentMana += manaGain;

	if (this->attributeComponent->currentMana > this->attributeComponent->maxMana)
	{
		this->attributeComponent->currentMana = this->attributeComponent->maxMana;
	}
}

// Allows the player to gain experience
void PlayerCharacter::gainEXP(const unsigned xpGain)
{
	this->attributeComponent->gainXP(xpGain);
}

// Initializes the components used by the player character
void PlayerCharacter::initializeComponents(sf::Texture& spriteTextureSheet, unsigned level, 
	std::string statFile, std::string movesetFile)
{
	this->makeMovementComponent(300.f * this->scale, 10.f * this->scale, 3.5f * this->scale);
	this->makeAnimationComponent(spriteTextureSheet);
	this->makeAttributeComponent(level, statFile, movesetFile);
}

// Sets starting variables for the player
void PlayerCharacter::initializeVariables(bool fullScreenScale)
{
	this->isAttacking = false;
	this->isPoweringUp = false;
	this->setSpriteScale(fullScreenScale);
}

// Moves the player character based on frame rate, x direction, and y direction
void PlayerCharacter::move(const float & deltaTime, const float x, const float y)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(deltaTime, x, y);
	}
}

// Checks to see if the player is currently attacking (so that no other animation plays while attacking)
void PlayerCharacter::checkForAttackAnimation(bool shouldAttack)
{
	if (shouldAttack)
	{
		this->isAttacking = true;
	}
}

// Checks to see if the player is currently powering up (so that no other animation plays while powering up)
void PlayerCharacter::checkForPowerUpAnimation(bool shouldPower)
{
	if (shouldPower)
	{
		this->isPoweringUp = true;
	}
}

