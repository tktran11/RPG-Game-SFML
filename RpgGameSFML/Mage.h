#pragma once
#include "PlayerCharacter.h"
class Mage :
	public PlayerCharacter
{
private:
	// Initialization Functions
	void initializeComponents();
	void initializeVariables();

	bool isAttacking;
	bool isPoweringUp;
public:
	Mage(sf::Texture& spriteTextureSheet, float startPointX, float startPointY);

	void updateAnimation(const float& deltaTime);
	void checkForAttackAnimation();
	virtual void update(const float& deltaTime);
	virtual ~Mage();
};

