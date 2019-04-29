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
	void initializeComponents(sf::Texture& spriteTextureSheet, std::string statFile, std::string movesetFile);
	void initializeVariables(bool fullScreenScale);
	// Initialization Functions
	float startPositionX;
	float startPositionY;
protected:
	float scale;
	bool isAttacking;
public:
	// Constructor
	Enemy(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, std::string statFile, std::string movesetFile, bool fullScreenScale);

	// Assessors
	CharacterAttributes* getAttributeComponent();
	float getStartPosX();
	float getStartPosY();
	float getSpriteScale();

	// Makes sprite disappear
	void disappear();

	// Mutators
	void setSpriteScale(bool fullScreenScale);

	// Combat Modifications
	void loseHP(const int hpLost);
	void gainHP(const int hpGain);
	void statMod(std::string key, int modifier);

	// Updates data specific to the enemy
	virtual void updateAnimation(const float& deltaTime) = 0;
	virtual void update(const float& deltaTime) = 0;
	void checkForAttackAnimation();

	bool playDeathAnimation(const float& deltaTime);
};