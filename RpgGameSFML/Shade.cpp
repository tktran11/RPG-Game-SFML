#include "stdafx.h"
#include "Shade.h"

/*
Shade.cpp is the .cpp for the shade class, which is a derived class of Enemy
and has unique characteristics specifc to the shade (Stats, animations, and abilities)
*/

enum attackKey {
	M = 12
};

// Constructor
Shade::Shade(sf::Texture & spriteTextureSheet, float startPointX, float startPointY, std::string filePath, std::string movesetFilePath, bool fullScreenScale) :
	Enemy(spriteTextureSheet, startPointX, startPointY, filePath, movesetFilePath, fullScreenScale)
{
	this->setPosition(startPointX, startPointY);
	this->sprite.setScale(this->scale, this->scale);
	this->makeAnimationComponent(spriteTextureSheet);
	// Given texture key, animation delay (lower = faster), xPos, yPos, number of X frames, Y Frames, width, height 
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 0, 6, 0, 59, 59);
	this->animationComponent->addAnimation("IDLE", 20.f, 0, 3, 3, 3, 59, 50);
	this->animationComponent->addAnimation("DEATH", 10.f, 0, 1, 9, 1, 59, 50);
	this->animationComponent->addAnimation("INJURE", 10.f, 0, 2, 2, 2, 59, 50);
}

// Updates the animation based on frame data
void Shade::updateAnimation(const float & deltaTime)
{
	// As long as the player is alive
	if (!this->getAttributeComponent()->isDead)
	{
		// if injured animation is playing
		if (this->isDamaged)
	{
		// facing leftside
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
		}
		// animate attack and set end of attack animation
		if (this->animationComponent->playAnimation("INJURE", deltaTime, true))
		{
			this->isDamaged = false;
			// reset position after animation for attacking finished
			if (this->sprite.getScale().x > 0.f)
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
		}
	}
		// if attack animation is playing
		else if (this->isAttacking)
		{
			// facing leftside
			if (this->sprite.getScale().x > 0.f)
			{
				this->sprite.setOrigin(0.f, 0.f);
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
			}
		}
		// plays idle as default
		else
		{
			this->animationComponent->playAnimation("IDLE", deltaTime);
		}
	}
}

// Updates all features of the shade including checking movement, animation, and stats
void Shade::update(const float & deltaTime)
{
	this->attributeComponent->update(deltaTime);
	this->checkForDamagedAnimation();
	this->checkForAttackAnimation();
	this->updateAnimation(deltaTime);
}