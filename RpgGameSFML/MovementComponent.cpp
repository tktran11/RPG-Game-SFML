#include "stdafx.h"
#include "MovementComponent.h"

/* MovementComponent.cpp is the body for the MovementComponent class, which handles
   the movement of entities or characters in the game by managing how they move and
   accelerating or decelerating them to simulate more realistic motion. 
*/

/* Constructor for the MovementComponent, with an initialization list, which sets
   the values to the parameter list immedaitely upon object creation
*/
MovementComponent::MovementComponent(sf::Sprite& sprite, float maximumVelocity,
	float acceleration, float deceleration): sprite(sprite), maximumVelocity(maximumVelocity),
	acceleration(acceleration), deceleration(deceleration)
{
}

/* getMaximumVelocity() is an assessor function that returns
   the maximum velocity alloted for a character
*/
const float & MovementComponent::getMaximumVelocity() const
{
	return this->maximumVelocity;
}
/* getVelocity() is an assessor function that returns
   the current velocity for a character
*/
const sf::Vector2f & MovementComponent::getVelocity() const
{
	return this->velocity;
}

/* getMoveType(moveType) evaluates what type of movement the character
   is doing. 
*/
const bool MovementComponent::checkMoveType(const short unsigned moveType) const
{
	switch (moveType)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
		{
			return true;
		}
		break;
	case WALKING:
		if (this->velocity.x != 0.f && this->velocity.y != 0.f)
		{
			return true;
		}
		break;
	case WALK_LEFT:
		if (this->velocity.x < 0.f)
		{
			return true;
		}
		break;
	case WALK_RIGHT:
		if (this->velocity.x > 0.f)
		{
			return true;
		}
		break;
	case WALK_UP:
		if (this->velocity.y < 0.f)
		{
			return true;
		}
		break;
	case WALK_DOWN:
		if (this->velocity.y > 0.f)
		{
			return true;
		}
		break;
	}
	return false;
}

/* move(xAmount, yAmount, deltaTime) is a function that handles changing movement velocity 
   for a character by accelerating it based on distance traveled. 
*/
void MovementComponent::move(const float & deltaTime, const float xAmount, const float yAmount)
{
	this->velocity.x += this->acceleration * xAmount;
	this->velocity.y += this->acceleration * yAmount;
}
/* updateMovement(deltaTIme) is a function that updates the movement of a character
   based on the direction that they are traveling. 
*/
void MovementComponent::updateMovement(const float & deltaTime)
{

	if (this->velocity.x > 0.f) // Right
	{

		if (this->velocity.x > this->maximumVelocity)
		{
			this->velocity.x = this->maximumVelocity;
		}

		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f) // Left
	{
		if (this->velocity.x < -(this->maximumVelocity))
		{
			this->velocity.x = -(this->maximumVelocity);
		}
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
		{
			this->velocity.x = 0.f;
		}
	}

	if (this->velocity.y > 0.f) // Up
	{
		
		if (this->velocity.y > this->maximumVelocity)
			this->velocity.y = this->maximumVelocity;

		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f) // Down
	{
	
		if (this->velocity.y < -this->maximumVelocity)
			this->velocity.y = -this->maximumVelocity;

		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}
	// Execute movement
	this->sprite.move(this->velocity * deltaTime); 
}

/* Destructor
*/
MovementComponent::~MovementComponent()
{
}
