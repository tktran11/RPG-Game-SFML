#include "stdafx.h"
#include "CharacterGUI.h"

CharacterGUI::CharacterGUI(PlayerCharacter* player)
{
	this->player = player;
	this->initializeFont();
	this->initializeStatDock();
	this->initializeHPBar();
}

void CharacterGUI::updateHPBar()
{
}

void CharacterGUI::updateManaBar()
{
}

void CharacterGUI::initializeFont()
{
	this->font.loadFromFile("Fonts/MorrisRoman-Black.ttf");
}

void CharacterGUI::initializeStatDock()
{
}

void CharacterGUI::initializeHPBar()
{
}

void CharacterGUI::initializeManaBar()
{
}

void CharacterGUI::updateUI(const float & deltaTime)
{
}

void CharacterGUI::renderUI(sf::RenderTarget & target)
{
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
