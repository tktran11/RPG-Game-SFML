#pragma once
#include "Entity.h"
#include "CharacterAttributes.h"
#include "AnimationComponent.h"

/*
Enemy.h is the header for the enemy class, which is the base class for enemy characters
the player will face. It stores information and will house components for enemies to make 
use of (Most notably the exclusion of movement).
*/

class Enemy :
	public Entity
{
private:
	void initializeComponents(sf::Texture& spriteTextureSheet);
	void initializeVariables();

	bool isAttacking;
public:
	//Constructor
	Enemy(sf::Texture& spriteTextureSheet, float startPointX, float startPointY);

	virtual void updateAnimation(const float deltaTime) = 0;
	void checkForAttackAnimation();
	virtual void update(const float& deltaTime);

};

