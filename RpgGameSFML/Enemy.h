#pragma once
#include "Entity.h"
#include "CharacterAttributes.h"
#include "AnimationComponent.h"

/*#pragma once
#include "Entity.h"

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
	void initializeVariables(bool fullScreenScale);
	// Initialization Functions
	float startPositionX;
	float startPositionY;
protected:
	float scale;
	bool isAttacking;
public:
	// Constructor
	Enemy(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, bool fullScreenScale);

	// Assessors
	CharacterAttributes* getAttributeComponent();
	float getStartPosX();
	float getStartPosY();
	float getSpriteScale();

	// Mutators
	void setSpriteScale(bool fullScreenScale);

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

