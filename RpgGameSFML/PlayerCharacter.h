#pragma once
#include "Entity.h"

/*
PlayerCharacter.h is the .header for the Player Character class, which is a virtual class that houses the
user's playable character's base functionality. Both playable characters
inherit features from this class.
It also stores information and houses components to manipulate the character.
*/

class PlayerCharacter :
	public Entity
{
private:
	// Initialization Functions
	void initializeComponents(sf::Texture& spriteTextureSheet);
	void initializeVariables();
	float startPositionX;
	float startPositionY;
	bool isAttacking;

public:
	// Constructor
	PlayerCharacter(sf::Texture& spriteTextureSheet, float startPointX, float startPointY);

	// Assessors
	float getStartPosX();
	float getStartPosY();

	virtual void updateAnimation(const float& deltaTime) = 0;
	virtual void move(const float& deltaTime, const float x, const float y);
	void checkForAttackAnimation();
	virtual void update(const float& deltaTime);
};

