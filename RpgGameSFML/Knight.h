#pragma once
#include "PlayerCharacter.h"

/*
Knight.h is the header for the knight class, which is a derived class of PlayerCharacter
and has unique characteristics specifc to the knight (Stats, animations, and abilities)
*/

class Knight :
	public PlayerCharacter
{
public:
	// Constructor
	Knight(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, bool scaleScreen = false);

	// Updates animation and other characteristics
	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);

};

