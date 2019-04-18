#pragma once

/* AnimationComponent.h is the header for the AnimationComponent class, which handles
   the animating of the sprites in the game. It houses two classes: the animation class, which handles
   a single animation and the actual AnimationComponent, which houses all animations and controls
   things like animation priority
*/

class AnimationComponent
{
private:
	// Animation class to control a single animation
	class Animation
	{
	private:
		bool isFinished;
	public:
		sf::Sprite& sprite;
		sf::Texture& animationSheet;
		float animationTimer;
		float timer;
		int height;
		int width;
		sf::IntRect currentFrame;
		sf::IntRect startFrame;
		sf::IntRect endingFrame;

		Animation(sf::Sprite& sprite, sf::Texture& animationSheet, float timer, int startFrameX, int startFrameY, int frameX, int frameY,
			int width, int height) : sprite(sprite), animationSheet(animationSheet), animationTimer(timer), width(width), height(height)
			, isFinished(false), timer(0.f)
		{
			this->startFrame = sf::IntRect(startFrameX * width, startFrameY * height, width, height);
			this->currentFrame = this->startFrame;
			this->endingFrame = sf::IntRect(frameX * width, frameY * height, width, height);
			this->sprite.setTexture(this->animationSheet, true);
			this->sprite.setTextureRect(this->startFrame);
		}
		void reset();
		const bool& getIsFinished();
		const bool& play(const float& deltaTime);
		const bool& play(const float& deltaTime, float playSpeedPercent);
	};

	// Animation map (name of animation) to the actual animation
	std::map<std::string, Animation*> animationSet;

	// Checks to see what the animation playing is to set correct functionality (ie. two animations can't play at once, or direction changing)
	Animation* lastPlayedAnimation;
	Animation* priorityAnimation;

	// Texture to animate
	sf::Sprite& sprite;
	sf::Texture& spriteSheet;
public:

	AnimationComponent(sf::Sprite& sprite, sf::Texture& spriteSheet);
	// Add animation to component
	void addAnimation(const std::string animationKey,
		float timer, int startFrameX, int startFrameY, int frameX, int frameY,
		int width, int height);

	// Accessor
	const bool& isAnimationFinished(const std::string animationKey);

	// Play functions
	const bool& playAnimation(const std::string animationKey, const float& deltaTime, const bool isPriority = false);
	const bool& playAnimation(const std::string animationKey, const float& deltaTime, const float& playSpeed,
		const float& maxPlaySpeed, const bool isPriority = false);
	~AnimationComponent();

};

