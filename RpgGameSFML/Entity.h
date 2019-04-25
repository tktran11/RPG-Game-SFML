#pragma once
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "CharacterAttributes.h"

/*
Enity.h is the header for the entity class, which is the base class for characters and
other entities.
It stores information and will house components for entities to make use of.
*/

// Forward Declarations
class MovementComponent;
class AnimationComponent;
class CharacterAttributes;

class Entity
{
private:
	void initializeVariables();
protected:
	sf::Sprite sprite;

	// Components that entities can choose to have (ie. player will likely have all of them, enemy wont move)
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	CharacterAttributes* attributeComponent;
public:

	// Constructor
	Entity();
	virtual void update(const float& deltaTime) = 0;
	virtual void renderEntity(sf::RenderTarget& target);

	//Assessors
	float getXPosition();
	float getYPosition();

	// Sprite Management
	virtual void setPosition(const float xPos, const float yPos);
	void setSpriteTexture(sf::Texture& spriteTextureSheet);
	void makeMovementComponent(const float maximumVelocity, const float accel, const float decel);
	void makeAnimationComponent(sf::Texture& spriteTextureSheet);
	void makeAttributeComponent(const unsigned level);
	// Virtual Destructor
	virtual ~Entity();
};

