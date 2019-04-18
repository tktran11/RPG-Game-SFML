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
PlayerCharacter::PlayerCharacter(sf::Texture& spriteTextureSheet, float startPointX, float startPointY)
{
	this->initializeComponents(spriteTextureSheet);
	this->initializeVariables();
	this->setPosition(startPointX, startPointY);

	// Given texture key, animation delay (lower = faster), xPos, yPos, number of X frames, Y Frames, width, height 
	this->animationComponent->addAnimation("MOVE", 5.f, 0, 1, 11, 1, 192, 192);
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 2, 13, 2, 192, 192);
	this->animationComponent->addAnimation("SWING", 5.f, 0, 4, 13, 4, 384, 192);
}

// Initializes the components used by the player character
void PlayerCharacter::initializeComponents(sf::Texture& spriteTextureSheet)
{
	this->makeMovementComponent(300.f, 12.f, 3.f);
	this->makeAnimationComponent(spriteTextureSheet);
	this->makeAttributeComponent(1); // first level is level 1
}

// Sets starting variables for the player
void PlayerCharacter::initializeVariables()
{
	this->isAttacking = false;
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

// Updates what is happening to the player character (ie. change in stats, movement, animation)
void PlayerCharacter::update(const float & deltaTime)
{
	this->attributeComponent->update();
	// REMOVE LATER
	system("cls");
	std::cout << this->attributeComponent->debugPrint() << "\n";
	// This cout and cls shit super lags everything. If you don't remove it the game will feel like trash



	this->movementComponent->updateMovement(deltaTime);
	this->checkForAttackAnimation();
	this->updateAnimation(deltaTime);
}


