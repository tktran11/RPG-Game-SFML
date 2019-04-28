#include "stdafx.h"
#include "Knight.h"

/*
Knight.cpp is the .cpp for the knight class, which is a derived class of PlayerCharacter
and has unique characteristics specifc to the knight (Stats, animations, and abilities)
*/

enum attackKey {
	K = 10
};

// Constructor
Knight::Knight(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, unsigned level, std::string filePath, std::string movesetFilePath, bool scaleScreen) :
	PlayerCharacter(spriteTextureSheet, startPointX, startPointY, level, filePath, movesetFilePath, scaleScreen)
{
	this->setPosition(startPointX, startPointY);
	this->sprite.setScale(this->scale, this->scale);
	this->makeAnimationComponent(spriteTextureSheet);
	// Given texture key, animation delay (lower = faster), xPos, yPos, number of X frames, Y Frames, width, height 
	this->animationComponent->addAnimation("MOVE", 5.f, 0, 0, 11, 0, 192, 192);
	this->animationComponent->addAnimation("IDLE", 18.f, 0, 3, 13, 3, 192, 192);
	this->animationComponent->addAnimation("SWING", 5.f, 0, 5, 13, 5, 384, 192);
}

// Updates the animation for the knight, deciding what way it faces and if its attacking
void Knight::updateAnimation(const float & deltaTime)
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
		this->sprite.setOrigin(265.f, 0.f);
		}
		// animate attack and set end of attack animation
		if (this->animationComponent->playAnimation("SWING", deltaTime, true))
		{
			this->isAttacking = false;
			// reset position after animation for attacking finished
			if (this->sprite.getScale().x > 0.f)
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			// facing leftside
			else
			{
		
				this->sprite.setOrigin(169.f, 0.f);
			}
		}
	}
	// checks for idle
	if (this->movementComponent->checkMoveType(IDLE))
	{
		this->animationComponent->playAnimation("IDLE", deltaTime);
	}
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
	else if (this->movementComponent->checkMoveType(WALK_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(169.f, 0.f);
			// Flip sprite
			this->sprite.setScale(-1.f * this->scale, 1.f * this->scale);
		}

		this->animationComponent->playAnimation("MOVE", deltaTime,
			this->movementComponent->getVelocity().x, this->movementComponent->getMaximumVelocity());
	}
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

// Updates all features of the knight including checking movement, animation, and stats
void Knight::update(const float & deltaTime)
{
	this->attributeComponent->update(deltaTime);
	this->movementComponent->updateMovement(deltaTime);
	this->checkForAttackAnimation();
	this->updateAnimation(deltaTime);
}
