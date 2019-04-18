#include "stdafx.h"
#include "Knight.h"

enum attackKey {
	K = 10
};


Knight::Knight(sf::Texture& spriteTextureSheet, float startPointX, float startPointY) :
	PlayerCharacter(spriteTextureSheet, startPointX, startPointY)
{
	this->initializeComponents();
	this->initializeVariables();
	this->setPosition(startPointX, startPointY);
	this->makeAnimationComponent(spriteTextureSheet);

	// Given texture key, animation delay (lower = faster), xPos, yPos, number of X frames, Y Frames, width, height 
	this->animationComponent->addAnimation("MOVE", 5.f, 0, 1, 11, 1, 192, 192);
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 2, 13, 2, 192, 192);
	this->animationComponent->addAnimation("SWING", 5.f, 0, 4, 13, 4, 384, 192);
}

void Knight::initializeComponents()
{
	this->makeMovementComponent(300.f, 12.f, 3.f);
}

void Knight::initializeVariables()
{
	this->isAttacking = false;
}

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
			this->sprite.setOrigin(354.f, 0.f);
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
			// facing rightside
			else
			{
				this->sprite.setOrigin(258.f, 0.f);
			}
		}
	}
	if (this->movementComponent->checkMoveType(IDLE))
	{
		this->animationComponent->playAnimation("IDLE", deltaTime);
	}
	else if (this->movementComponent->checkMoveType(WALK_RIGHT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(258.f, 0.f);
			// Flip sprite
			this->sprite.setScale(-1.f, 1.f);
		}
		this->animationComponent->playAnimation("MOVE", deltaTime,
			this->movementComponent->getVelocity().x, this->movementComponent->getMaximumVelocity());
	}
	else if (this->movementComponent->checkMoveType(WALK_LEFT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			// Flip sprite
			this->sprite.setScale(1.f, 1.f);
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

void Knight::checkForAttackAnimation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(K)))
	{
		this->isAttacking = true;
	}
}

void Knight::update(const float & deltaTime)
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


Knight::~Knight()
{
}
