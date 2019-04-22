#include "stdafx.h"
#include "CharacterGUI.h"

// Constructor
CharacterGUI::CharacterGUI(PlayerCharacter* player, std::string playerType)
{
	this->player = player;
	this->playerType = playerType;
	this->barHeight = 10.f * this->player->getSpriteScale();
	this->initializeTextures();
	this->initializeFont();
	this->initializePortrait();
	this->initializeStatDock();
	this->initializeHPBar();
	this->initializeManaBar();
	this->initializeTextDisplays();
}

// Loads the textures for use in the Player UI from a file 
void CharacterGUI::initializeTextures()
{
	std::ifstream readTextures("Config/uiTextures.txt");
	if (readTextures.is_open())
	{
		std::string line;
		while (std::getline(readTextures, line))
		{
			this->textureFiles.push_back(line);
			if (!this->texture.loadFromFile(line))
			{
				throw "ERROR:GAME_STATE::MISSING_PLAYER_UI_TEXTURE";
			}
			this->uiTextures.push_back(this->texture);
		}
	}
}

// Loads the font needed for text display
void CharacterGUI::initializeFont()
{
	this->font.loadFromFile("Fonts/MorrisRoman-Black.ttf");
}

// Sets up the text display for level and experience
void CharacterGUI::initializeTextDisplays()
{
	this->levelText.setFont(this->font);
	this->levelText.setPosition(this->guiDock.getSize().x / 2.5f,
		this->portrait.getSize().y * 0.8f);
	this->levelText.setCharacterSize(20 * this->player->getSpriteScale());
}

// Initializes the character portrait with relavent resizing based on the specs of the pictures loaded
void CharacterGUI::initializePortrait()
{
	this->portrait.setSize(sf::Vector2f(69.6f * this->player->getSpriteScale(), 81.6f * this->player->getSpriteScale()));
	this->portrait.setPosition(0.f, 0.f);
	this->portrait.setTexture(&this->uiTextures[1]);


	if (this->playerType == "mage")
	{
		this->portraitPic.setPosition(-10.5f * this->player->getSpriteScale(), 5.f * this->player->getSpriteScale());
		this->portraitPic.setSize(sf::Vector2f(80.f * this->player->getSpriteScale(), 70.6f * this->player->getSpriteScale()));
		this->portraitPic.setTexture(&this->uiTextures[3]);
	}
	else
	{
		this->portraitPic.setPosition(6.f  * this->player->getSpriteScale()	, 5.f  * this->player->getSpriteScale());
		this->portraitPic.setSize(sf::Vector2f(60.f * this->player->getSpriteScale(), 70.6f  * this->player->getSpriteScale()));
		this->portraitPic.setTexture(&this->uiTextures[2]);
	}

}

// Initializes the stat dock 
void CharacterGUI::initializeStatDock()
{
	this->guiDock.setSize(sf::Vector2f(252.6f * this->player->getSpriteScale(), 81.6f  * this->player->getSpriteScale()));
	this->guiDock.setPosition(this->portrait.getSize().x, 0.f);
	this->guiDock.setTexture(&this->uiTextures[0]);
}

// Initializes the HP bar with text display for clarity
void CharacterGUI::initializeHPBar()
{
	float width = 202.f * this->player->getSpriteScale();
	float offset = 17.f * this->player->getSpriteScale();
	this->hpBarMax = width;

	this->hpBar.setSize(sf::Vector2f(width, this->barHeight));
	this->hpBar.setPosition(this->guiDock.getPosition().x + offset, offset);
	this->hpBar.setTexture(&this->uiTextures[4]);

	this->hpBarText.setFont(this->font);
	this->hpBarText.setPosition(this->hpBar.getPosition().x + (width / 3), this->hpBar.getPosition().y - (5 * this->player->getSpriteScale()));
	this->hpBarText.setCharacterSize(offset);
}

// Initializes the Mana bar with text display for clarity
void CharacterGUI::initializeManaBar()
{
	float width = 115.f * this->player->getSpriteScale();
	float offset = 17.f  * this->player->getSpriteScale();
	this->manaBarMax = width;

	this->manaBar.setSize(sf::Vector2f(width, this->barHeight));
	this->manaBar.setPosition(this->guiDock.getPosition().x + offset, offset + (20.f * this->player->getSpriteScale()));
	this->manaBar.setTexture(&this->uiTextures[5]);

	this->manaBarText.setFont(this->font);
	this->manaBarText.setPosition(this->manaBar.getPosition().x + (width / 4), this->manaBar.getPosition().y - (5 * this->player->getSpriteScale()));
	this->manaBarText.setCharacterSize(offset);

}

// Updates the bars on the UI and the text 
void CharacterGUI::updateUI(const float & deltaTime)
{
	this->updateHPBar();
	this->updateManaBar();
	this->updateTextDisplay();
}

// Updates calculation for the HP displayed
void CharacterGUI::updateHPBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->currentHP) /
		static_cast<float>(this->player->getAttributeComponent()->maxHP);


	this->hpBar.setSize(sf::Vector2f(static_cast<float>(std::floor(this->hpBarMax * percent)), this->barHeight));

	this->hpBarString = std::to_string(this->player->getAttributeComponent()->currentHP) + " / "
		+ std::to_string((this->player->getAttributeComponent()->maxHP));
	this->hpBarText.setString(this->hpBarString);
}

// Updates calculation for the Mana displayed
void CharacterGUI::updateManaBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->currentMana) /
		static_cast<float>(this->player->getAttributeComponent()->maxMana);

	this->manaBar.setSize(sf::Vector2f(static_cast<float>(std::floor(this->manaBarMax * percent)), this->barHeight));
	this->manaBarString = std::to_string(this->player->getAttributeComponent()->currentMana) + " / "
		+ std::to_string((this->player->getAttributeComponent()->maxMana));
	this->manaBarText.setString(this->manaBarString);
}

// Updates the shown level and calculation for experience displayed
void CharacterGUI::updateTextDisplay()
{
	this->levelString = ("Level: " + std::to_string(this->player->getAttributeComponent()->level) + "\n" +
		std::to_string(this->player->getAttributeComponent()->experience) + " EXP / " +
		std::to_string(this->player->getAttributeComponent()->expToNextLevel) + " EXP");
	this->levelText.setString(this->levelString);
}

// Draws all objects to target (which is the state window)
void CharacterGUI::renderUI(sf::RenderTarget & target)
{
	target.draw(this->portrait);
	target.draw(this->portraitPic);
	target.draw(this->guiDock);
	this->renderHPBar(target);
	this->renderManaBar(target);
	this->renderTextDisplay(target);
}

// Draws the HP bar and text in the correct rendering order
void CharacterGUI::renderHPBar(sf::RenderTarget & target)
{
	target.draw(this->hpBar);
	target.draw(this->hpBarText);
}

// Draws the Mana bar and text in the correct rendering order
void CharacterGUI::renderManaBar(sf::RenderTarget & target)
{
	target.draw(this->manaBar);
	target.draw(this->manaBarText);
}

// Draws the level and experience text
void CharacterGUI::renderTextDisplay(sf::RenderTarget & target)
{
	target.draw(this->levelText);
}
