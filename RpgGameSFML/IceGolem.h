#pragma once
#include "Enemy.h"

/*
IceGolem.h is the header for the Ice Golem class, which is a derived class of Enemy
and has unique characteristics specifc to the Ice Golem (Stats, animations, and abilities)
*/

class IceGolem :
	public Enemy
{
public:
	// Constructor
	IceGolem(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, bool fullScreenScale = false);

	// Updates animations and other characteristics
	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);

};
