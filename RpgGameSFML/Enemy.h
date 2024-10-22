#pragma once
#include "Entity.h"
#include "PlayerCharacter.h"
#include "CharacterAttributes.h"
#include "AnimationComponent.h"

/*
Enemy.h is the header for the enemy class, which is the base class for enemy characters
the player will face. It stores information and will house components for enemies to make 
use of (Most notably the exclusion of movement).
*/

// Forward declaration
class PlayerCharacter;

class Enemy :
	public Entity
{
private:
	// Initializer functions
	void initializeComponents(sf::Texture& spriteTextureSheet, std::string statFile, std::string movesetFile);
	void initializeVariables(bool fullScreenScale);

	// Float values for position
	float startPositionX;
	float startPositionY;
protected:
	// Protected values for calculations
	float scale;
	bool isAttacking;
	bool isDamaged;
public:
	// Constructor
	Enemy(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, std::string statFile, std::string movesetFile, bool fullScreenScale);

	// Assessors
	CharacterAttributes* getAttributeComponent();
	float getStartPosX();
	float getStartPosY();
	float getSpriteScale();

	// Mutators
	void setSpriteScale(bool fullScreenScale);
	void disappear();

	// Combat Modifications/Assessors
	void loseHP(const int hpLost);
	void gainHP(const int hpGain);
	void dealDamage(PlayerCharacter* player, const int damage);
	void statMod(std::string key, int modifier);
	int getStatNumbers(std::string key);

	// Updates data specific to the enemy
	virtual void updateAnimation(const float& deltaTime) = 0;
	virtual void update(const float& deltaTime) = 0;

	// Animation checkers
	void checkForAttackAnimation(bool shouldAttack = false);
	void checkForDamagedAnimation(bool takeDamage = false);
	bool playDeathAnimation(const float& deltaTime);
};