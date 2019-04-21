#include "stdafx.h"
#include "CharacterGUI.h"

CharacterGUI::CharacterGUI(PlayerCharacter* player, std::string playerType)
{
	this->player = player;
	this->playerType = playerType;
	this->initializeTextures();
	this->initializeFont();
	this->initializePortrait();
	this->initializeStatDock();
	this->initializeHPBar();
	this->initializeManaBar();
}

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

void CharacterGUI::initializeFont()
{
	this->font.loadFromFile("Fonts/MorrisRoman-Black.ttf");
}

void CharacterGUI::initializePortrait()
{
	this->portrait.setSize(sf::Vector2f(69.6f, 81.6f));
	this->portrait.setPosition(0.f, 0.f);
	this->portrait.setTexture(&this->uiTextures[1]);

	this->portraitPic.setSize(sf::Vector2f(60.f, 70.6f));
	this->portraitPic.setPosition(6.f, 5.f);
	if (this->playerType == "mage")
	{
		this->portraitPic.setTexture(&this->uiTextures[3]);
	} 
	else
	{
		this->portraitPic.setTexture(&this->uiTextures[2]);
	}

}

void CharacterGUI::initializeStatDock()
{
	this->guiDock.setSize(sf::Vector2f(252.6f, 81.6f));
	this->guiDock.setPosition(this->portrait.getSize().x, 0.f);
	this->guiDock.setTexture(&this->uiTextures[0]);
}

void CharacterGUI::initializeHPBar()
{
	this->hpBar.setSize(sf::Vector2f(202.f, 10.f));
	this->hpBar.setPosition(this->guiDock.getPosition().x + 17, 17);
	this->hpBar.setTexture(&this->uiTextures[4]);
}

void CharacterGUI::initializeManaBar()
{
	this->manaBar.setSize(sf::Vector2f(115.f, 10.f));
	this->manaBar.setPosition(this->guiDock.getPosition().x + 17, 37);
	this->manaBar.setTexture(&this->uiTextures[5]);
}

void CharacterGUI::updateUI(const float & deltaTime)
{
}
void CharacterGUI::updateHPBar()
{
}

void CharacterGUI::updateManaBar()
{
}


void CharacterGUI::renderUI(sf::RenderTarget & target)
{
	target.draw(this->portrait);
	target.draw(this->portraitPic);
	target.draw(this->guiDock);
	target.draw(this->hpBar);
	target.draw(this->manaBar);
}

void CharacterGUI::renderHPBar()
{
}

void CharacterGUI::renderManaBar()
{
}


CharacterGUI::~CharacterGUI()
{
}
