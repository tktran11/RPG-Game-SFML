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
	void initializeComponents(sf::Texture& spriteTextureSheet);
	void initializeVariables(bool fullScreenScale);
	// Initialization Functions
	float startPositionX;
	float startPositionY;
protected:
	float scale;
	bool isAttacking;
public:
	// Constructor
	PlayerCharacter(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, bool fullScreenScale);

	// Assessors
	CharacterAttributes* getAttributeComponent();
	float getStartPosX();
	float getStartPosY();

	// Mutators
	void setSpriteScale(bool fullScreenScale);

	virtual void updateAnimation(const float& deltaTime) = 0;
	virtual void update(const float& deltaTime) = 0;
	virtual void move(const float& deltaTime, const float x, const float y);
	void checkForAttackAnimation();
};

