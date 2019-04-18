#pragma once
#include "PlayerCharacter.h"
class Knight :
	public PlayerCharacter
{
private:
	// Initialization Functions
	void initializeComponents();
	void initializeVariables();

	bool isAttacking;
public:
	Knight(sf::Texture& spriteTextureSheet, float startPointX, float startPointY);

	void updateAnimation(const float& deltaTime);
	void checkForAttackAnimation();
	void update(const float& deltaTime);

	~Knight();
};

