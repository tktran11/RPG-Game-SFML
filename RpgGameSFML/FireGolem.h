#pragma once
#include "Enemy.h"

/*
FireGolem.h is the header for the Fire Golem class, which is a derived class of Enemy
and has unique characteristics specifc to the Fire Golem (Stats, animations, and abilities)
*/

class FireGolem :
	public Enemy
{
public:
	// Constructor
	FireGolem(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, std::string filePath, std::string movesetFilePath, bool fullScreenScale = false);

	// Updates animations and other characteristics
	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);
};
