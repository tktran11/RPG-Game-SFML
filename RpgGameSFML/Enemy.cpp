#include "stdafx.h"
#include "Enemy.h"

/*
Enemy.cpp is the header for the enemy class, which is the base class for enemy characters
the player will face.It stores information and will house components for enemies to make
use of(Most notably the exclusion of movement).
*/

enum attackKey {
	M = 12
};

//Constructor for enemies
Enemy::Enemy(sf::Texture& spriteTextureSheet, float startPointX, float startPointY)
{
	this->initializeComponents(spriteTextureSheet);
	this->initializeVariables();
	this->setPosition(startPointX, startPointY);

	// Given texture key, animation delay (lower = faster), xPos, yPos, number of X frames, Y Frames, width, height 
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 4, 13, 4, 384, 192);
}

// Initializes the components used by the player character
void Enemy::initializeComponents(sf::Texture& spriteTextureSheet)
{
	this->makeAnimationComponent(spriteTextureSheet);
	this->makeAttributeComponent(1); // first level is level 1
}

// Sets starting variables for the player
void Enemy::initializeVariables()
{
	this->isAttacking = false;
}

// Checks to see if the player is currently attacking (so that no other animation plays while attacking)
void Enemy::checkForAttackAnimation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(M)))
	{
		this->isAttacking = true;
	}
}

// Updates what is happening to the player character (ie. change in stats, movement, animation)
void Enemy::update(const float & deltaTime)
{
	this->attributeComponent->update();
	// REMOVE LATER
	system("cls");
	std::cout << this->attributeComponent->debugPrint() << "\n";
	// This cout and cls shit super lags everything. If you don't remove it the game will feel like trash

	this->checkForAttackAnimation();
	this->updateAnimation(deltaTime);
}


