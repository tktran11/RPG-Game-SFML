#include "stdafx.h"
#include "Entity.h"

/*Enity.cpp is the body for the Entity class, which is the base class for characters and
other entities.
It stores information and will house components for entities to make use of.
*/


Entity::Entity()
{
	this->initializeVariables();

}


void Entity::initializeVariables()
{
	this->movementComponent = nullptr;
}


void Entity::move(const float& deltaTime, const float directionX, const float directionY)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(deltaTime, directionX, directionY);
	}
}

void Entity::updateEntity(const float & deltaTime)
{

}


void Entity::renderEntity(sf::RenderTarget& target)
{
		target.draw(this->sprite);
}

void Entity::setPosition(const float xPos, const float yPos)
{
		this->sprite.setPosition(xPos, yPos);
}


void Entity::setSpriteTexture(sf::Texture& spriteTexture)
{
	this->sprite.setTexture(spriteTexture);
}

void Entity::makeMovementComponent(const float maximumVelocity, const float accel, const float decel)
{
	this->movementComponent = new MovementComponent(this->sprite, maximumVelocity, accel, decel);
}

void Entity::makeAnimationComponent(sf::Texture & spriteTextureSheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, spriteTextureSheet);
}

void Entity::makeAttributeComponent(const unsigned level)
{
	this->attributeComponent = new CharacterAttributes(level);
}

/* Destructor for the Entity Class*/
Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->attributeComponent;
}

