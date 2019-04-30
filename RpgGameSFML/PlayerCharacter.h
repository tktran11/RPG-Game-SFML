#pragma once
#include "Entity.h"
#include "Enemy.h"

/*
PlayerCharacter.h is the .header for the Player Character class, which is a virtual class that houses the
user's playable character's base functionality. Both playable characters
inherit features from this class.
It also stores information and houses components to manipulate the character.
*/

class Enemy;

class PlayerCharacter :
	public Entity
{
private:
	void initializeComponents(sf::Texture& spriteTextureSheet, unsigned level, 
		std::string statFile, std::string movesetFile);
	void initializeVariables(bool scaleScreen);
	// Initialization Functions
	float startPositionX;
	float startPositionY;
protected:
	float scale;
	bool isAttacking;
	bool isPoweringUp;
public:
	// Constructor
	PlayerCharacter(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, unsigned level, 
		std::string statFile, std::string movesetFile, bool scaleScreen);

	// Assessors
	CharacterAttributes* getAttributeComponent();
	float getStartPosX();
	float getStartPosY();
	float getSpriteScale();

	// Mutators
	void setSpriteScale(bool scaleScreen);

	// Combat Assessors 
	float getAbilityNumbers(std::string key);
	int getStatNumbers(std::string key);
	int getCurrentMana();
	int getMaxMana();
	void dealDamage(Enemy* enemy, const int damage);

	// Combat Modifications
	void loseHP(const int hpLost);
	void gainHP(const int hpGain);
	void statMod(std::string key, int modifier);
	void loseMana(const int manaLost);
	void gainMana(const int manaGain);
	void gainEXP(const unsigned xpGain);
	
	// Updates data specific to the enemy
	virtual void updateAnimation(const float& deltaTime) = 0;
	virtual void update(const float& deltaTime) = 0;
	virtual void move(const float& deltaTime, const float x, const float y);
	void checkForAttackAnimation(bool shouldAttack = false);
	void checkForPowerUpAnimation(bool shouldPower = false);
};

