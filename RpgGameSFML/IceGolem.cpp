#include "stdafx.h"
#include "IceGolem.h"

/*
IceGolem.cpp is the .cpp for the Ice Golem class, which is a derived class of Enemy
and has unique characteristics specifc to the Ice Golem (Stats, animations, and abilities)
*/

// Constructor
IceGolem::IceGolem(sf::Texture & spriteTextureSheet, float startPointX, float startPointY, std::string filePath, std::string movesetFilePath, bool fullScreenScale) :
	Enemy(spriteTextureSheet, startPointX, startPointY, filePath, movesetFilePath, fullScreenScale)
{
	this->setPosition(startPointX, startPointY);
	this->sprite.setScale(this->scale, this->scale);
	this->makeAnimationComponent(spriteTextureSheet);

	// Given texture key, animation delay (lower = faster), xPos, yPos, number of X frames, Y Frames, width, height 
	this->animationComponent->addAnimation("ATTACK", 7.f, 0, 1, 6, 1, 72, 57);
	this->animationComponent->addAnimation("ATTACK_2", 10.f, 0, 2, 9, 2, 72, 57);
	this->animationComponent->addAnimation("IDLE", 20.f, 0, 0, 4, 0, 72, 57);
	this->animationComponent->addAnimation("INJURE", 15.f, 0, 4, 2, 4, 72, 57);
	this->animationComponent->addAnimation("DEATH", 10.f, 0, 3, 8, 3, 72, 57);
}

// Updates the animation based on frame data
void IceGolem::updateAnimation(const float & deltaTime)
{
	// As long as the ice golem is alive
	if (!this->getAttributeComponent()->isDead)
	{
		// if injured, play injured animation
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

// Updates all features of the ice golem including checking movement, animation, and stats
void IceGolem::update(const float & deltaTime)
{
	this->attributeComponent->update(deltaTime);
	this->checkForDamagedAnimation();
	this->checkForAttackAnimation();
	this->updateAnimation(deltaTime);
}