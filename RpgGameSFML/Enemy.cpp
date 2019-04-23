#include "stdafx.h"
#include "Enemy.h"

/*
Enemy.cpp is the header for the enemy class, which is the base class for enemy characters
the player will face.It stores information and will house components for enemies to make
use of(Most notably the exclusion of movement).
*/

enum attackKey {
	K = 10
};

/* Constructor for the player character*/
Enemy::Enemy(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, bool fullScreenScale)
{
	this->startPositionX = startPointX;
	this->startPositionY = startPointY;
	this->initializeComponents(spriteTextureSheet);
	this->initializeVariables(fullScreenScale);
	this->setPosition(startPointX, startPointY);
}

// Assessor for the attribute component
CharacterAttributes* Enemy::getAttributeComponent()
{
	return this->attributeComponent;
}

// Returns the starting position of the player character in the X axis
float Enemy::getStartPosX()
{
	return this->startPositionX;
}

// Returns the starting position of the player character in the Y axis
float Enemy::getStartPosY()
{
	return this->startPositionY;
}

// Assessor for sprite scale
float Enemy::getSpriteScale()
{
	return this->scale;
}

// Scales the sprite for fullscreen applications if necessary
void Enemy::setSpriteScale(bool fullScreenScale)
{
	if (fullScreenScale)
	{
		this->scale = 1.5f;
	}
	else
	{
		this->scale = 1.f;
	}
}

// Subtracts HP from the player based on damage taken
void Enemy::loseHP(const int hpLost)
{
	this->attributeComponent->currentHP -= hpLost;

	if (this->attributeComponent->currentHP < 0)
	{
		this->attributeComponent->currentHP = 0;
	}
}
// Adds HP to the player based on amount gained
void Enemy::gainHP(const int hpGain)
{
	this->attributeComponent->currentHP += hpGain;

	if (this->attributeComponent->currentHP > this->attributeComponent->maxHP)
	{
		this->attributeComponent->currentHP = this->attributeComponent->maxHP;
	}
}

// Subtracts mana from the player based on the amount spent
void Enemy::loseMana(const int manaLost)
{
	this->attributeComponent->currentMana -= manaLost;

	if (this->attributeComponent->currentMana < 0)
	{
		this->attributeComponent->currentMana = 0;
	}
}

// Returns mana to the player and changes the mana if it goes over cap
void Enemy::gainMana(const int manaGain)
{
	this->attributeComponent->currentMana += manaGain;

	if (this->attributeComponent->currentMana > this->attributeComponent->maxMana)
	{
		this->attributeComponent->currentMana = this->attributeComponent->maxMana;
	}
}

// Allows the player to gain experience
void Enemy::gainEXP(const unsigned xpGain)
{
	this->attributeComponent->gainXP(xpGain);
}

// Initializes the components used by the player character
void Enemy::initializeComponents(sf::Texture& spriteTextureSheet)
{
	this->makeMovementComponent(300.f, 10.f, 3.5f);
	this->makeAnimationComponent(spriteTextureSheet);
	this->makeAttributeComponent(1);
}

// Sets starting variables for the player
void Enemy::initializeVariables(bool fullScreenScale)
{
	this->isAttacking = false;
	this->setSpriteScale(fullScreenScale);
}

// Moves the player character based on frame rate, x direction, and y direction
void Enemy::move(const float& deltaTime, const float x, const float y)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(deltaTime, x, y);
	}
}
// Checks to see if the player is currently attacking (so that no other animation plays while attacking)
void Enemy::checkForAttackAnimation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(K)))
	{
		this->isAttacking = true;
	}
}