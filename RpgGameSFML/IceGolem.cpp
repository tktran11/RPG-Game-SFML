#include "stdafx.h"
#include "IceGolem.h"

/*
IceGolem.cpp is the .cpp for the Ice Golem class, which is a derived class of Enemy
and has unique characteristics specifc to the Ice Golem (Stats, animations, and abilities)
*/

enum attackKey {
	M = 12
};

IceGolem::IceGolem(sf::Texture & spriteTextureSheet, float startPointX, float startPointY, bool fullScreenScale) :
	Enemy(spriteTextureSheet, startPointX, startPointY, fullScreenScale)

{
	this->setPosition(startPointX, startPointY);
	this->sprite.setScale(this->scale, this->scale);
	this->makeAnimationComponent(spriteTextureSheet);
	// Given texture key, animation delay (lower = faster), xPos, yPos, number of X frames, Y Frames, width, height 
	this->animationComponent->addAnimation("ATTACK", 7.f, 0, 1, 6, 1, 32, 25);
	this->animationComponent->addAnimation("ATTACK_2", 7.f, 0, 1, 10, 1, 32, 25);
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 4, 4, 4, 32, 25);
	this->animationComponent->addAnimation("INJURE", 15.f, 0, 3, 2, 3, 32, 25);
	this->animationComponent->addAnimation("DEATH", 10.f, 0, 2, 8, 2, 32, 25);
}

void IceGolem::updateAnimation(const float & deltaTime)
{
	if (this->isAttacking)
	{
		// facing leftside
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(0, 0.f);
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
	// plays idle by default
	else
	{
		this->animationComponent->playAnimation("IDLE", deltaTime);
	}
}

void IceGolem::update(const float & deltaTime)
{
	this->attributeComponent->update(deltaTime);
	this->checkForAttackAnimation();
	this->updateAnimation(deltaTime);
}

