#pragma once
class AnimationComponent
{
private:
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

	std::map<std::string, Animation*> animationSet;
	Animation* lastPlayedAnimation;
	Animation* priorityAnimation;
	sf::Sprite& sprite;
	sf::Texture& spriteSheet;
public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& spriteSheet);
	// Add animation to   component
	void addAnimation(const std::string animationKey,
		float timer, int startFrameX, int startFrameY, int frameX, int frameY,
		int width, int height);

	// Accessor
	const bool& isAnimationFinished(const std::string animationKey);

	const bool& playAnimation(const std::string animationKey, const float& deltaTime, const bool isPriority = false);
	const bool& playAnimation(const std::string animationKey, const float& deltaTime, const float& playSpeed,
		const float& maxPlaySpeed, const bool isPriority = false);
	~AnimationComponent();

};

