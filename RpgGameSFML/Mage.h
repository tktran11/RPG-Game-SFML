#pragma once
#include "PlayerCharacter.h"

/*
Mage.h is the header for the mage class, which is a derived class of PlayerCharacter
and has unique characteristics specifc to the mage (Stats, animations, and abilities)
*/

class Mage :
	public PlayerCharacter
{
private:
	// Initialization Functions
	void initializeVariables();
	bool isPoweringUp;
public:
	// Constructor
	Mage(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, unsigned level, std::string filePath, bool scaleScreen = false);

	// Updates animations and other characteristics
	void updateAnimation(const float& deltaTime);
	void checkForPowerUpAnimation();
	void update(const float& deltaTime);
};

