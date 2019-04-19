#pragma once
#include "PlayerCharacter.h"
class Knight :
	public PlayerCharacter
{
public:
	Knight(sf::Texture& spriteTextureSheet, float startPointX, float startPointY, bool fullScreenScale = false);

	void updateAnimation(const float& deltaTime);
	void update(const float& deltaTime);

};

