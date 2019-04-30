#include "stdafx.h"
#include "Slime.h"

/*
Slime.cpp is the .cpp for the slime class, which is a derived class of Enemy
and has unique characteristics specifc to the slime (Stats, animations, and abilities)
*/

// Constructor
Slime::Slime(sf::Texture & spriteTextureSheet, float startPointX, float startPointY, std::string filePath, std::string movesetFilePath, bool fullScreenScale) :
	Enemy(spriteTextureSheet, startPointX, startPointY, filePath, movesetFilePath, fullScreenScale)
{
	this->setPosition(startPointX, startPointY);
	this->sprite.setScale(this->scale, this->scale);
	this->makeAnimationComponent(spriteTextureSheet);

	// Given texture key, animation delay (lower = faster), xPos, yPos, number of X frames, Y Frames, width, height 
	this->animationComponent->addAnimation("ATTACK", 7.f, 0, 1, 7, 1, 32, 25);
	this->animationComponent->addAnimation("IDLE", 20.f, 0, 0, 7, 0, 32, 25);
	this->animationComponent->addAnimation("DEATH", 10.f, 0, 2, 5, 2, 32, 25);
}

// Updates the animation based on frame data
void Slime::updateAnimation(const float & deltaTime)
{
	// As long as the slime is alive
	if (!this->getAttributeComponent()->isDead)
	{
		// if attack animation is playing
		if (this->isAttacking)
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

// Updates all features of the slime including checking movement, animation, and stats
void Slime::update(const float & deltaTime)
{
	this->attributeComponent->update(deltaTime);
	this->checkForDamagedAnimation();
	this->checkForAttackAnimation();
	this->updateAnimation(deltaTime);
}