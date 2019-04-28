#pragma once
#include "Enemy.h"

/*
Minotaur.h is the header for the Minotaur class, which is a derived class of Enemy
and has unique characteristics specifc to the Minotaur (Stats, animations, and abilities)
*/

class Minotaur :
	public Enemy
{
public:
	// Constructor
	Minotaur(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, std::string filePath, std::string movesetFilePath, bool fullScreenScale = false);

	// Updates animations and other characteristics
	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);

};