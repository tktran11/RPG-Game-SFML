#include "stdafx.h"
#include "Shade.h"

	enum attackKey {
	M = 12
};

	Shade::Shade(sf::Texture & spriteTextureSheet, float startPointX, float startPointY, bool fullScreenScale) :
		Enemy(spriteTextureSheet, startPointX, startPointY, fullScreenScale)

	{
		this->setPosition(startPointX, startPointY);
		this->sprite.setScale(this->scale, this->scale);
		this->makeAnimationComponent(spriteTextureSheet);
		// Given texture key, animation delay (lower = faster), xPos, yPos, number of X frames, Y Frames, width, height 
		this->animationComponent->addAnimation("ATTACK", 5.f, 0, 0, 6, 0, 59, 59);
		this->animationComponent->addAnimation("IDLE", 15.f, 0, 3, 3, 3, 59, 50);
		this->animationComponent->addAnimation("DEATH", 10.f, 0, 1, 8, 1, 59, 50);
		this->animationComponent->addAnimation("INJURE", 10.f, 0, 2, 13, 2, 59, 50);
	}

	void Shade::updateAnimation(const float & deltaTime)
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
			this->sprite.setOrigin(354.f, 0.f);
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
				this->sprite.setOrigin(258.f, 0.f);
			}
		}
	}
	else
	{
		this->animationComponent->playAnimation("IDLE", deltaTime);
	}
}

void Shade::update(const float & deltaTime)
{
	this->attributeComponent->update(deltaTime);
	this->checkForAttackAnimation();
	this->updateAnimation(deltaTime);
}

