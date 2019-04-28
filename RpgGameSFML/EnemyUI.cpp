#include "stdafx.h"
#include "EnemyUI.h"


EnemyUI::EnemyUI(Enemy * enemy, std::string enemyName)
{
	this->enemy = enemy;
	this->scale = this->enemy->getSpriteScale() / 3;
	this->barHeight = 10.f * this->scale;
	this->initializeTextures();
	this->initializeFont();
	this->initializeHPBar();
	this->initializeTextDisplay(enemyName);
}

void EnemyUI::initializeTextures()
{
	if (!this->texture.loadFromFile("EnemyUI/health.png"))
	{
		throw "ERROR:GAME_STATE::MISSING_PLAYER_UI_TEXTURE";
	}
}

void EnemyUI::initializeFont()
{
	this->font.loadFromFile("Fonts/MorrisRoman-Black.ttf");
}

void EnemyUI::initializeHPBar()
{
	float width = 202.8f * this->scale;
	float offset = 17.f *  this->scale;
	this->hpBarMax = width;

	this->hpBar.setSize(sf::Vector2f(this->enemy->getAttributeComponent()->maxHP, this->barHeight));
	this->hpBar.setPosition(this->enemy->getXPosition() * 1.06f, this->enemy->getYPosition() * 1.15f);
	this->hpBar.setTexture(&this->texture);

	this->hpBarText.setFont(this->font);
	this->hpBarText.setPosition(this->hpBar.getPosition().x + (width / 2.9f), this->hpBar.getPosition().y - (5.5 * this->scale));
	this->hpBarText.setCharacterSize(offset);
}

void EnemyUI::initializeTextDisplay(std::string enemyName)
{
	this->nameString = enemyName;
	this->nameText.setFont(this->font);
	this->nameText.setCharacterSize(20 * this->scale);
	this->nameText.setString(this->nameString);
	this->nameText.setPosition(this->hpBarText.getPosition().x - (this->nameText.getGlobalBounds().width /6.f), this->hpBar.getPosition().y * 0.95f);
}

void EnemyUI::updateUI(const float & deltaTime)
{
	this->updateHPBar();
}

void EnemyUI::updateHPBar()
{
	float percent = static_cast<float>(this->enemy->getAttributeComponent()->currentHP) /
		static_cast<float>(this->enemy->getAttributeComponent()->maxHP);


	this->hpBar.setSize(sf::Vector2f(static_cast<float>(std::floor(this->hpBarMax * percent)), this->barHeight));

	this->hpBarString = std::to_string(this->enemy->getAttributeComponent()->currentHP) + " / "
		+ std::to_string((this->enemy->getAttributeComponent()->maxHP));
	this->hpBarText.setString(this->hpBarString);
}

void EnemyUI::renderUI(sf::RenderTarget & target)
{
	target.draw(this->hpBar);
	target.draw(this->hpBarText);
	target.draw(this->nameText);
}

