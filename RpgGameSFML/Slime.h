#pragma once
#include "Enemy.h"

class Slime :
	public Enemy
{
public:
	Slime(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, bool fullScreenScale = false);

	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);

};

