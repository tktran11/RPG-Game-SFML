#pragma once
#include "Enemy.h"
class Slime :
	public Enemy
{
private:
	void initializeComponents();
	void initializeVariables();

	bool isAttacking;
public:
	Slime(sf::Texture& spriteTextureSheet, float startPointX, float startPointY);

	void updateAnimation(const float& deltaTime);
	void checkForAttackAnimation();
	void update(const float& deltaTime);

	~Slime();
};

