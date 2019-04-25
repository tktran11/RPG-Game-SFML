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
	void initializeComponents(sf::Texture& spriteTextureSheet, unsigned level);
	void initializeVariables(bool scaleScreen);
	// Initialization Functions
	float startPositionX;
	float startPositionY;
protected:
	float scale;
	bool isAttacking;
public:
	// Constructor
	PlayerCharacter(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, unsigned level, bool scaleScreen);

	// Assessors
	CharacterAttributes* getAttributeComponent();
	float getStartPosX();
	float getStartPosY();
	float getSpriteScale();

	// Mutators
	void setSpriteScale(bool scaleScreen);

	// Combat Modifications
	void loseHP(const int hpLost);
	void gainHP(const int hpGain);

	void loseMana(const int manaLost);
	void gainMana(const int manaGain);

	void gainEXP(const unsigned xpGain);
	


	virtual void updateAnimation(const float& deltaTime) = 0;
	virtual void update(const float& deltaTime) = 0;
	virtual void move(const float& deltaTime, const float x, const float y);
	void checkForAttackAnimation();
};

