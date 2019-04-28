#pragma once
#include "Enemy.h"
class EnemyUI
{
private:
	Enemy* enemy;

	sf::Font font;
	float scale;
	//HP Bar
	float barHeight;
	float hpBarMax;

	sf::Texture texture;
	sf::Text hpBarText;
	std::string hpBarString;
	sf::RectangleShape hpBar;

	// Other Displays
	sf::Text nameText;
	std::string nameString;


	void initializeTextures();
	void initializeFont();
	void initializeHPBar();
	void initializeTextDisplay(std::string enemyName);
public:
	EnemyUI(Enemy* enemy, std::string enemyName);

	void updateUI(const float& deltaTime);
	void updateHPBar();

	void renderUI(sf::RenderTarget& target);
};

