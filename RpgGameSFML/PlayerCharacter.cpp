#include "stdafx.h"
#include "PlayerCharacter.h"

enum attackKey {
	K = 10
};

/*
PlayerCharacter.h is the header for the Player Character class, which is the class that houses the
user's playable character.It stores information and will house components to manipulate the character.
*/


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

void PlayerCharacter::checkForAttackAnimation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(K)))
	{
		this->isAttacking = true;
	}
}

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

void PlayerCharacter::initializeComponents(sf::Texture& spriteTextureSheet)
{
	this->makeMovementComponent(300.f, 12.f, 3.f);
	this->makeAnimationComponent(spriteTextureSheet);
	this->makeAttributeComponent(1); // first level is level 1
}

void PlayerCharacter::initializeVariables()
{
	this->isAttacking = false;
}

