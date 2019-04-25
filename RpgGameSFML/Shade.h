#pragma once
#include "Enemy.h"

/*
Shade.h is the header for the shade class, which is a derived class of Enemy
and has unique characteristics specifc to the shade (Stats, animations, and abilities)
*/

class Shade :
	public Enemy
{
public:
	// Constructor
	Shade(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, bool fullScreenScale = false);

	// Updates animations and other characteristics
	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);

};

