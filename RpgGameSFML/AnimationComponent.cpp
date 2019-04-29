#include "stdafx.h"
#include "AnimationComponent.h"
#include "AnimationComponent.h"

/* AnimationComponent.cpp is the body for the AnimationComponent class, which handles
   the animating of the sprites in the game. It houses two classes: the animation class, which handles
   a single animation and the actual AnimationComponent, which houses all animations and controls
   things like animation priority
*/

// Constructor for the Animation Component, with an initialization list
AnimationComponent::AnimationComponent(sf::Sprite & sprite, sf::Texture & spriteSheet)
	:sprite(sprite), spriteSheet(spriteSheet), lastPlayedAnimation(NULL), priorityAnimation(NULL)
{
}

/* Adds animation based on given sprite (reference), the sprite sheet (.png reference), delay timer.
   Also requires starting X and Y positions, multiplier for the number of X and Y frames, the width and height
   of each image within the sprite sheet
*/
void AnimationComponent::addAnimation(const std::string animationKey,
	float timer, int startFrameX, int startFrameY, int frameX, int frameY,
	int width, int height)
{
	this->animationSet[animationKey] = new Animation(this->sprite, this->spriteSheet, timer, startFrameX, startFrameY,
		frameX, frameY, width, height);
}

// Returns whether or not an animation is currently being played (if current animation is finished playing or not)
const bool & AnimationComponent::isAnimationFinished(const std::string animationKey) 
{
	return this->animationSet[animationKey]->getIsFinished();
}

// Plays an animation pausing all attempts to play any other animations if that animation has priority (ie. attack animation
// takes precedence over idle animations)
const bool& AnimationComponent::playAnimation(const std::string animationKey, const float & deltaTime, const bool isPriority)
{
	if (isPriority)
	{
		this->priorityAnimation = this->animationSet[animationKey];
	}
	if (this->priorityAnimation) // if a priority animation is trying to be played
	{
		// if current animation trying to be played is the priority animation
		if (this->priorityAnimation == this->animationSet[animationKey])
		{
			// Reset any other animations that aren't the one set to be played
			if (this->lastPlayedAnimation != this->animationSet[animationKey])
			{
				if (this->lastPlayedAnimation != NULL)
				{
			
						this->lastPlayedAnimation->reset();
				}
				this->lastPlayedAnimation = this->animationSet[animationKey];
			}
			// After playing the priority animation, remove its priority
			if (this->animationSet[animationKey]->play(deltaTime))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	// If no priority animation exists, continue playing specified animation as usual
	else {
		if (isPriority)
		{
			this->priorityAnimation = this->animationSet[animationKey];
		}
		// Reset any other animations that aren't the one set to be played
		if (this->lastPlayedAnimation != this->animationSet[animationKey])
		{
			if (this->lastPlayedAnimation != NULL)
			{
	
				this->lastPlayedAnimation->reset();
			}
			this->lastPlayedAnimation = this->animationSet[animationKey];
		}
		this->animationSet[animationKey]->play(deltaTime);
	}
	return this->animationSet[animationKey]->getIsFinished();
}
// Plays animation with movement based speed modifers, mainly to change walking animation speed as character slows down
const bool& AnimationComponent::playAnimation(const std::string animationKey, const float & deltaTime, const float & playSpeed, const float & maxPlaySpeed,
	const bool isPriority)
{
	// Reset any other animations that aren't the one set to be played
	if (this->priorityAnimation) // if a priority animation is trying to be played
	{
		// if current animation trying to be played is the priority animation
		if (this->priorityAnimation == this->animationSet[animationKey])
		{
			// Reset any other animations that aren't the one set to be played
			if (this->lastPlayedAnimation != this->animationSet[animationKey])
			{
				if (this->lastPlayedAnimation != NULL)
				{
					this->lastPlayedAnimation->reset();
				}
				this->lastPlayedAnimation = this->animationSet[animationKey];
			}
			// After playing the priority animation, remove its priority
			if (this->animationSet[animationKey]->play(deltaTime, abs(playSpeed / maxPlaySpeed)))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	// If no priority animation exists, continue playing specified animation as usual
	else {
		if (isPriority)
		{
			this->priorityAnimation = this->animationSet[animationKey];
		}
		// Reset any other animations that aren't the one set to be played
		if (this->lastPlayedAnimation != this->animationSet[animationKey])
		{
			if (this->lastPlayedAnimation != NULL)
			{
				this->lastPlayedAnimation->reset();
			}
			this->lastPlayedAnimation = this->animationSet[animationKey];
		}
		this->animationSet[animationKey]->play(deltaTime, abs(playSpeed / maxPlaySpeed));
	}
	return this->animationSet[animationKey]->getIsFinished();
}

// Resets timers on the animation and the starting frame
void AnimationComponent::Animation::reset()
{
	// Reset f
	this->timer = this->animationTimer;
	this->currentFrame = this->startFrame;
}

// Returns if animation is finished playing
const bool & AnimationComponent::Animation::getIsFinished()
{
	return this->isFinished;
}

// Plays an animation with a speed based on deltatime, returns if animation is finished playing
const bool& AnimationComponent::Animation::play(const float & deltaTime)
{
	this->isFinished = false;
	// Update animation timer if timer hits the specified timer max
	this->timer += 100.f * deltaTime;
	if (this->timer >= this->animationTimer)
	{
		// Reset
		this->timer = 0.f;

		// Haven't reached the end of the sprite sheet, animate
		if (this->currentFrame != this->endingFrame)
		{
			this->currentFrame.left += this->width;
		}
		// Reset animation
		else
		{
			this->currentFrame.left = this->startFrame.left;
			this->isFinished = true;
		}
		this->sprite.setTextureRect(this->currentFrame);
	}

	return this->isFinished;
}

// Plays animation based on delta time but modified by player speed mostly for movement animations, returns if animation is finished playing
const bool& AnimationComponent::Animation::play(const float & deltaTime, float playSpeedPercent)
{
	this->isFinished = false;
	// Update animation timer if timer hits the specified timer max
	float min = 0.5f;
	if (playSpeedPercent < min)
	{
		playSpeedPercent = min;
	}
	this->timer += 100.f * (playSpeedPercent)* deltaTime;
	if (this->timer >= this->animationTimer)
	{
		// Reset
		this->timer = 0.f;

		// Haven't reached the end of the sprite sheet, animate
		if (this->currentFrame != this->endingFrame)
		{
			this->currentFrame.left += this->width;
		}
		// Reset animation
		else
		{
			this->currentFrame.left = this->startFrame.left;
			this->isFinished = true;
		}
		this->sprite.setTextureRect(this->currentFrame);
	}
	return this->isFinished;
}

// Destructor
AnimationComponent::~AnimationComponent()
{
	for (auto &iterator : this->animationSet)
	{
		delete iterator.second;
	}
}
