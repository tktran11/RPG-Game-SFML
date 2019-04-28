#include "stdafx.h"
#include "EnemyUI.h"

// Constructor
EnemyUI::EnemyUI(Enemy* enemy, std::string enemyName, float xScale, float yScale, float nameOffset)
{
	this->enemy = enemy;
	this->scale = this->enemy->getSpriteScale() / 3;
	this->barHeight = 10.f * this->scale;
	this->initializeTextures();
	this->initializeFont();
	this->initializeHPBar(xScale, yScale);
	this->initializeTextDisplay(enemyName, nameOffset);
}

//Initializes texture for the UI
void EnemyUI::initializeTextures()
{
	if (!this->texture.loadFromFile("EnemyUI/health.png"))
	{
		throw "ERROR:GAME_STATE::MISSING_PLAYER_UI_TEXTURE";
	}
}

// Initializes font from a file
void EnemyUI::initializeFont()
{
	this->font.loadFromFile("Fonts/MorrisRoman-Black.ttf");
}

// Creates an HP bar with dimensions and position on the screen
void EnemyUI::initializeHPBar(float xScale, float  yScale)
{
	float width =  125.f * this->scale;
	float offset = 17.f *  this->scale;
	this->hpBarMax = width;

	this->hpBar.setSize(sf::Vector2f( this->hpBarMax, this->barHeight * 20));
	this->hpBar.setPosition(this->enemy->getXPosition() * xScale, this->enemy->getYPosition() * yScale);
	this->hpBar.setTexture(&this->texture);

	this->hpBarText.setFont(this->font);
	this->hpBarText.setPosition(this->hpBar.getPosition().x + (width / 3.9f), this->hpBar.getPosition().y - (5.5 * this->scale));
	this->hpBarText.setCharacterSize(offset);
}

// Calls different UI elements to the screen
void EnemyUI::initializeTextDisplay(std::string enemyName, float offSetDivision)
{
	this->nameString = enemyName;
	this->nameText.setFont(this->font);
	this->nameText.setCharacterSize(20 * this->scale);
	this->nameText.setString(this->nameString);
	this->nameText.setPosition(this->hpBarText.getPosition().x - (this->nameText.getGlobalBounds().width /offSetDivision), this->hpBar.getPosition().y * 0.95f);
}

// Updates per frame values that will be altered in combat
void EnemyUI::updateUI(const float & deltaTime)
{
	this->updateHPBar();
}

// Updates the HP bar 
void EnemyUI::updateHPBar()
{
	float percent = static_cast<float>(this->enemy->getAttributeComponent()->currentHP) /
		static_cast<float>(this->enemy->getAttributeComponent()->maxHP);


	this->hpBar.setSize(sf::Vector2f(static_cast<float>(std::floor(this->hpBarMax * percent)), this->barHeight));

	this->hpBarString = std::to_string(this->enemy->getAttributeComponent()->currentHP) + " / "
		+ std::to_string((this->enemy->getAttributeComponent()->maxHP));
	this->hpBarText.setString(this->hpBarString);
}

// Renders elements to the screen
void EnemyUI::renderUI(sf::RenderTarget & target)
{
	target.draw(this->hpBar);
	target.draw(this->hpBarText);
	target.draw(this->nameText);
}

