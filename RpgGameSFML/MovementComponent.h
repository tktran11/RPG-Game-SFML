#pragma once
/* MovementComponent.h is the header file for the movement component for
   entities or characters in this game. It handles creating more realistic 
   movement by accelerating or decelerating characters as they move. 
*/

// Enums for the input directions
enum movementTypes { IDLE = 0, WALKING, WALK_LEFT, WALK_RIGHT, WALK_UP, WALK_DOWN};
class MovementComponent
{
private:
	sf::Sprite& sprite;

	// Floats used in calculations for movement
	float maximumVelocity;
	float acceleration;
	float deceleration;

	// SFML Vector converted to Float that stores velocity in X and Y
	sf::Vector2f velocity;
public:
	// Constructor
	MovementComponent(sf::Sprite& sprite, float maximumVelocity,
		float acceleration, float deceleration);

	// Assessors
	const float& getMaximumVelocity() const;
	const sf::Vector2f& getVelocity() const;
	const bool checkMoveType(const short unsigned moveType) const;

	// Movement Handling
	void move(const float& deltaTime, const float xAmount, const float yAmount);
	void updateMovement(const float& deltaTime);
};

