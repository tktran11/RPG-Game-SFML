#pragma once
#include "PlayerCharacter.h"
class Mage :
	public PlayerCharacter
{
private:
	// Initialization Functions
	void initializeVariables();
	bool isPoweringUp;
public:
	Mage(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, bool fullScreenScale = false);

	void updateAnimation(const float& deltaTime);
	void checkForPowerUpAnimation();
	void update(const float& deltaTime);
};

