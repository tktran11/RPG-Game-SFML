#include "stdafx.h"
#include "Entity.h"

/*
Enity.cpp is the body for the Entity class, which is the base class for characters and
other entities.
It stores information and will house components for entities to make use of.
*/

// Constructor
Entity::Entity()
{
	this->initializeVariables();

}

// Set initial values to null to avoid garbage before component creation
void Entity::initializeVariables()
{
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->attributeComponent = nullptr;
}

// Renders entity to the target
void Entity::renderEntity(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
// Returns the x position of the sprite
float Entity::getXPosition()
{
	return this->sprite.getPosition().x;
}
// Returns the y position of the sprite
float Entity::getYPosition()
{
	return this->sprite.getPosition().y;
}

// Sets the sprite's position on the screen
void Entity::setPosition(const float xPos, const float yPos)
{
		this->sprite.setPosition(xPos, yPos);
}

// Sets the texture of the sprite to the given texture sheet 
void Entity::setSpriteTexture(sf::Texture& spriteTexture)
{
	this->sprite.setTexture(spriteTexture);
}

// Creates a movement component for the entity, with values for realistic movement physics
void Entity::makeMovementComponent(const float maximumVelocity, const float accel, const float decel)
{
	this->movementComponent = new MovementComponent(this->sprite, maximumVelocity, accel, decel);
}

// Creates an animation component for the entity with a given texture sheet to go through and animate from
void Entity::makeAnimationComponent(sf::Texture & spriteTextureSheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, spriteTextureSheet);
}

// Creates an attribute component to hold the attributes of an entity
void Entity::makeAttributeComponent(const unsigned level, std::string statFile, std::string movesetFile)
{
	this->attributeComponent = new CharacterAttributes(level, statFile, movesetFile);
}

/* Destructor for the Entity Class*/
Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->attributeComponent;
}

