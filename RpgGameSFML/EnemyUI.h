#pragma once
#include "Enemy.h"
#include "Slime.h"
#include "Shade.h"
#include "FireGolem.h"
#include "IceGolem.h"
#include "StoneGolem.h"
#include "Minotaur.h"

class EnemyUI
{
private:
	Enemy* enemy;

	//Sets Font
	sf::Font font;
	float scale;
	//HP Bar
	float barHeight;
	float hpBarMax;

	sf::Texture texture;
	sf::Text hpBarText;
	std::string hpBarString;
	sf::RectangleShape hpBar;

	//Other Displays
	sf::Text nameText;
	std::string nameString;

	//Initializers
	void initializeTextures();
	void initializeFont();
	void initializeHPBar(float xScale, float yScale);
	void initializeTextDisplay(std::string enemyName, float offsetDivision);
public:
	//Constructor
	EnemyUI(Enemy* enemy, std::string enemyName, float xScale, float yScale, float nameOffset);

	//Update Function
	void updateUI(const float& deltaTime);
	void updateHPBar();

	//Render Function
	void renderUI(sf::RenderTarget& target);
};

