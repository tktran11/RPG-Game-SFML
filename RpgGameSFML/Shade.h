#pragma once
#include "Enemy.h"

class Shade :
	public Enemy
{
public:
	Shade(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, bool fullScreenScale = false);

	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);

};

