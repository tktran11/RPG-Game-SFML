#pragma once
#include "Entity.h"

/*
PlayerCharacter.h is the header for the Player Character class, which is the class that houses the
user's playable character.It stores information and will house components to manipulate the character.
*/
class PlayerCharacter :
	public Entity
{
private:
	// Initialization Functions
	void initializeComponents(sf::Texture& spriteTextureSheet);
	void initializeVariables();

	bool isAttacking;

public:
	// Constructor
	PlayerCharacter(sf::Texture& spriteTextureSheet, float startPointX, float startPointY);
	
	virtual void updateAnimation(const float& deltaTime) = 0;
	void checkForAttackAnimation();
	virtual void update(const float& deltaTime);
};

