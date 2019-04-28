#pragma once
#include "Enemy.h"

/*
StoneGolem.h is the header for the Stone Golem class, which is a derived class of Enemy
and has unique characteristics specifc to the Stone Golem (Stats, animations, and abilities)
*/

class StoneGolem :
	public Enemy
{
public:
	// Constructor
	StoneGolem(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, std::string filePath, std::string movesetFilePath, bool fullScreenScale = false);

	// Updates animations and other characteristics
	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);

};
