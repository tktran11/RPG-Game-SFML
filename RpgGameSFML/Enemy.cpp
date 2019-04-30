#include "stdafx.h"
#include "Enemy.h"

/*
Enemy.cpp is the .cpp for the enemy class, which is the base class for enemy characters
the player will face.It stores information and will house components for enemies to make
use of (Most notably the exclusion of movement).
*/

// Constructor for the enemy character
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

// Returns the starting position of the enemy character in the X axis
float Enemy::getStartPosX()
{
	return this->startPositionX;
}

// Returns the starting position of the enemy character in the Y axis
float Enemy::getStartPosY()
{
	return this->startPositionY;
}

// Assessor for sprite scale
float Enemy::getSpriteScale()
{
	return this->scale;
}

// Makes enemy sprite disappear
void Enemy::disappear()
{
	this->sprite.setScale(0, 0);
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

// Subtracts HP from the enemy character based on damage taken
void Enemy::loseHP(const int hpLost)
{
	this->attributeComponent->currentHP -= hpLost;

	if (this->attributeComponent->currentHP <= 0)
	{
		this->attributeComponent->isDead = true;
		this->attributeComponent->currentHP = 0;
	}
}

// Adds HP to the enemy based on amount gained
void Enemy::gainHP(const int hpGain)
{
	this->attributeComponent->currentHP += hpGain;

	if (this->attributeComponent->currentHP > this->attributeComponent->maxHP)
	{
		this->attributeComponent->currentHP = this->attributeComponent->maxHP;
	}
}

// Deals damage the player based on the damage calculated
void Enemy::dealDamage(PlayerCharacter* player, const int damage)
{
	player->loseHP(damage);
}

// Adds/removes stat values to a specific stat (buff/debuff)
void Enemy::statMod(std::string key, int modifier)
{
	this->attributeComponent->stats[key] += modifier;
}

// Gets stats number from the map
int Enemy::getStatNumbers(std::string key)
{
	return this->attributeComponent->stats[key];
}

// Initializes the components used by the enemy character
void Enemy::initializeComponents(sf::Texture& spriteTextureSheet, std::string statFile, std::string movesetFile)
{
	this->makeAnimationComponent(spriteTextureSheet);
	this->makeAttributeComponent(1, statFile, movesetFile);
}

// Sets starting variables for the enemy
void Enemy::initializeVariables(bool fullScreenScale)
{
	this->isAttacking = false;
	this->isDamaged = false;
	this->setSpriteScale(fullScreenScale);
}

// Checks to see if the enemy is currently attacking (so that no other animation plays while attacking)
void Enemy::checkForAttackAnimation(bool shouldAttack)
{
	if (shouldAttack)
	{
		this->isAttacking = true;
	}
}

// Checks to see if the enemy is currently damaged (so that no other animation plays while damaged)
void Enemy::checkForDamagedAnimation(bool takeDamage)
{
	if (takeDamage)
	{
		this->isDamaged = true;
	}
}

// Plays the death animation when HP reaches 0
bool Enemy::playDeathAnimation(const float & deltaTime)
{
	if (this->animationComponent->playAnimation("DEATH", deltaTime, true))
	{
		return true;
	}
}

