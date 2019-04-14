#pragma once
#include "MovementComponent.h"
#include "AnimationComponent.h"
/*
Enity.h is the header for the entity class, which is the base class for characters and
other entities.
It stores information and will house components for entities to make use of.
*/
class Entity
{
private:
	void initializeVariables();
protected:
	sf::Sprite sprite;
	
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
public:

	// Constructor
	Entity();

	virtual void move(const float& deltaTime, const float x, const float y);
	virtual void updateEntity(const float& deltaTime);
	virtual void renderEntity(sf::RenderTarget& target);

	// Sprite Management
	virtual void setPosition(const float xPos, const float yPos);
	void setSpriteTexture(sf::Texture& spriteTextureSheet);
	void makeMovementComponent(const float maximumVelocity, const float accel, const float decel);
	void makeAnimationComponent(sf::Texture& spriteTextureSheet);
	// Virtual Destructor
	virtual ~Entity();
};

