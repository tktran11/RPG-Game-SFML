#include "stdafx.h"
#include "Enemy.h"

/*
Enemy.cpp is the .cpp for the enemy class, which is the base class for enemy characters
the player will face.It stores information and will house components for enemies to make
use of (Most notably the exclusion of movement).
*/

enum attackKey {
	M = 12
};

/* Constructor for the player character*/
Enemy::Enemy(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, std::string statFile, std::string movesetFile, bool fullScreenScale)
{
	this->startPositionX = startPointX;
	this->startPositionY = startPointY;
	this->initializeComponents(spriteTextureSheet, statFile, movesetFile);
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
		this->scale = 5.f;
	}
	else
	{
		this->scale = 3.f;
	}
}

// Subtracts HP from the player based on damage taken
void Enemy::loseHP(const int hpLost)
{
	this->attributeComponent->currentHP -= hpLost;

	if (this->attributeComponent->currentHP <= 0)
	{
		this->attributeComponent->isDead = true;
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

// Initializes the components used by the player character
void Enemy::initializeComponents(sf::Texture& spriteTextureSheet, std::string statFile, std::string movesetFile)
{
	this->makeAnimationComponent(spriteTextureSheet);
	this->makeAttributeComponent(1, statFile, movesetFile);
}

// Sets starting variables for the player
void Enemy::initializeVariables(bool fullScreenScale)
{
	this->isAttacking = false;
	this->setSpriteScale(fullScreenScale);
}

// Checks to see if the player is currently attacking (so that no other animation plays while attacking)
void Enemy::checkForAttackAnimation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(M)))
	{
		this->isAttacking = true;
	}
}