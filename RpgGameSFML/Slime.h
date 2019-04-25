#pragma once
#include "Enemy.h"

/*
Slime.h is the header for the slime class, which is a derived class of Enemy
and has unique characteristics specifc to the slime (Stats, animations, and abilities)
*/

class Slime :
	public Enemy
{
public:
	// Constructor
	Slime(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, bool fullScreenScale = false);

	// Updates animations and other characteristics
	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);

};

