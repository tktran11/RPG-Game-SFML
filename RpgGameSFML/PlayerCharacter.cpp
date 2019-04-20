#include "stdafx.h"
#include "PlayerCharacter.h"

/*
PlayerCharacter.cpp is the .cpp for the Player Character class, which is a virtual class that houses the
user's playable character's base functionality. Both playable characters
inherit features from this class.
It also stores information and houses components to manipulate the character.
*/

enum attackKey {
	K = 10
};

/* Constructor for the player character*/
PlayerCharacter::PlayerCharacter(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, bool fullScreenScale)
{
	this->startPositionX = startPointX;
	this->startPositionY = startPointY;
	this->initializeComponents(spriteTextureSheet);
	this->initializeVariables(fullScreenScale);
	this->setPosition(startPointX, startPointY);
}

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

void PlayerCharacter::setSpriteScale(bool fullScreenScale)
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

// Initializes the components used by the player character
void PlayerCharacter::initializeComponents(sf::Texture& spriteTextureSheet)
{
	this->makeMovementComponent(300.f, 12.f, 3.f);
	this->makeAnimationComponent(spriteTextureSheet);
	this->makeAttributeComponent(0);
}

// Sets starting variables for the player
void PlayerCharacter::initializeVariables(bool fullScreenScale)
{
	this->isAttacking = false;
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
void PlayerCharacter::checkForAttackAnimation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(K)))
	{
		this->isAttacking = true;
	}
}

