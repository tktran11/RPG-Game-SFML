#include "stdafx.h"
#include "Entity.h"

/*Enity.cpp is the body for the Entity class, which is the base class for characters and
other entities.
It stores information and will house components for entities to make use of.
*/

/* Constructor for the Entity class*/
Entity::Entity()
{
	this->initializeVariables();

}

/* initializeVariables()* is a function to set the default values for the entity sprite */
void Entity::initializeVariables()
{
	this->movementComponent = nullptr;
}

/* move() is a function that handles basic movement for testing purposes at this time*/
void Entity::move(const float& deltaTime, const float directionX, const float directionY)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(deltaTime, directionX, directionY);
	}
}
/* updateEntity handles movement input for the entity at this time*/
void Entity::updateEntity(const float & deltaTime)
{

}

/* renderEntity draws the entity so that it can be palced on the window*/
void Entity::renderEntity(sf::RenderTarget& target)
{
		target.draw(this->sprite);
}
/* setPosition() sets the position of the entity on the screen.*/
void Entity::setPosition(const float xPos, const float yPos)
{
		this->sprite.setPosition(xPos, yPos);
}

/* makeSprite() sets the texture for a sprite and then creates a new sprite
   using SFML*/
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

/* Destructor for the Entity Class*/
Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
}

