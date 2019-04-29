#include "stdafx.h"
#include "Mage.h"

/*
Mage.h is the .cpp for the mage class, which is a derived class of PlayerCharacter
and has unique characteristics specifc to the mage (Stats, animations, and abilities)
*/

enum attackKey {
	K = 10,	L = 11
};

// Constructor
Mage::Mage(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, unsigned level, std::string filePath, std::string movesetFilePath, bool scaleScreen) :
	PlayerCharacter(spriteTextureSheet, startPointX, startPointY, level, filePath, movesetFilePath, scaleScreen)
{
	this->initializeVariables();
	this->setPosition(startPointX, startPointY);
	this->sprite.setScale(this->scale, this->scale);
	this->makeAnimationComponent(spriteTextureSheet);

	// Given texture key, animation delay (lower = faster), xPos, yPos, number of X frames, Y Frames, width, height 
	this->animationComponent->addAnimation("MOVE", 7.f, 0, 1, 7, 1, 192, 192);
	this->animationComponent->addAnimation("IDLE", 18.f, 0, 0, 9, 0, 192, 192);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 3, 16, 3, 384, 192);
	this->animationComponent->addAnimation("POWER_UP", 5.f, 0, 2, 16, 2, 192, 192);
}

// Sets base values for animation checking
void Mage::initializeVariables()
{
	this->isAttacking = false;
	this->isPoweringUp = false;
}

// Updates the animation for the mage, changing direction when moving, and checking for animation
void Mage::updateAnimation(const float & deltaTime)
{
	if (this->isAttacking)
	{
		// facing rightside
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(96.f, 0.f);
		}
		// facing leftside
		else
		{
			this->sprite.setOrigin(236.f, 0.f);
		}
		// animate attack and set end of attack animation
		if (this->animationComponent->playAnimation("ATTACK", deltaTime, true))
		{
			this->isAttacking = false;
			// reset position after animation for attacking finished
			if (this->sprite.getScale().x > 0.f)
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			// facing rightside
			else
			{
				this->sprite.setOrigin(140.f, 0.f);
			}
		}
	}
	// if powering up and not attacking
	if (this->isPoweringUp && !this->isAttacking)
	{
		// facing rightside
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
		}
		// facing leftside
		else
		{
			this->sprite.setOrigin(172.f, 0.f);
		}
		// animate power up and set end of attack animation
		if (this->animationComponent->playAnimation("POWER_UP", deltaTime, true))
		{
			this->isPoweringUp = false;
			// reset position after animation for attacking finished
			if (this->sprite.getScale().x > 0.f)
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			// facing rightside
			else
			{
				this->sprite.setOrigin(172.f, 0.f);
			}
		}
	}
	// checks for idle
	if (this->movementComponent->checkMoveType(IDLE))
	{
		this->animationComponent->playAnimation("IDLE", deltaTime);
	}
	// walking left
	else if (this->movementComponent->checkMoveType(WALK_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(172.f, 0.f);
			// Flip sprite
			this->sprite.setScale(-1.f * this->scale, 1.f * this->scale);
		}
		this->animationComponent->playAnimation("MOVE", deltaTime,
			this->movementComponent->getVelocity().x, this->movementComponent->getMaximumVelocity());
	}
	// walking right
	else if (this->movementComponent->checkMoveType(WALK_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			// Flip sprite
			this->sprite.setScale(1.f * this->scale, 1.f * this->scale);
		}
		this->animationComponent->playAnimation("MOVE", deltaTime,
			this->movementComponent->getVelocity().x, this->movementComponent->getMaximumVelocity());
	}
	// walking up
	else if (this->movementComponent->checkMoveType(WALK_UP))
	{
		this->animationComponent->playAnimation("MOVE", deltaTime,
			this->movementComponent->getVelocity().y, this->movementComponent->getMaximumVelocity());
	}
	else if ((this->movementComponent->checkMoveType(WALK_UP)) || (this->movementComponent->checkMoveType(WALK_DOWN)))
	{
		this->animationComponent->playAnimation("MOVE", deltaTime,
			this->movementComponent->getVelocity().y, this->movementComponent->getMaximumVelocity());
	}

}

// Checks to see if the mage is in the middle of powering up
void Mage::checkForPowerUpAnimation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(L)))
	{
		this->isPoweringUp = true;
	}
}

// Updates all components for the mage, checking for animation and movement and stat changes
void Mage::update(const float & deltaTime)
{
	this->movementComponent->updateMovement(deltaTime);
	this->checkForAttackAnimation();
	this->checkForPowerUpAnimation();
	this->updateAnimation(deltaTime);
}
