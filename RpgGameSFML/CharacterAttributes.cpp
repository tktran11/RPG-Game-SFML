#include "stdafx.h"
#include "CharacterAttributes.h"

/* CharacterAttributes.cpp is the body for the Character Attributes class, which controls the stats of the player
   and enemy characters. It holds information for the current state of the player such as their health or mana,
   and also handles level progression
*/

CharacterAttributes::CharacterAttributes(int characterLevel)
{
	this->level = characterLevel;
	this->experience = 0;
	this->expToNextLevel = calculateExpToNext(this->level);
	this->attributePoints = 0;
	this->intelligence = 10; // DEFAULT FOR TESTING, CHANGE OR INPUT AS NEEDED
	this->vitality = 10; // DEFAULT FOR TESTING, CHANGE OR INPUT AS NEEDED
	this->updateLevel();
	this->updateAttributes(true);
}

std::string CharacterAttributes::debugPrint() const
{
	std::stringstream ss;

	ss << "Level: " << this->level << "\n"
		<< "Exp: " << this->experience << "\n"
		<< "Experience to Next: " << this->expToNextLevel << "\n"
		<< "Attribute Points: " << this->attributePoints << "\n"
		<< "Health: " << this->currentHP << "\n"
		<< "Health Max: " << this->maxHP << "\n"
		<< "Mana: " << this->currentMana << "\n"
		<< "Max Mana: " << this->maxMana << "\n" << "\n";

	return ss.str();
}

int CharacterAttributes::calculateExpToNext(int characterLevel)
{
	int neededExp = 0;
	if (characterLevel <= 2)
	{
		neededExp = 100;
	}
	else
	{
		neededExp = (characterLevel * 50);
	}
	return neededExp;
}

void CharacterAttributes::ganXP(const int experience)
{
	this->experience += experience;
}

void CharacterAttributes::updateAttributes(const bool resetOnLevel)
{

	this->maxHP = this->vitality * 10 + (25 * this->level);
	this->maxMana = this->intelligence * 10 + (25 * this->level);

	// if we decide to heal on level up, reset total health and mana
	if (resetOnLevel)
	{
		this->currentHP = this->maxHP;
		this->currentMana = this->maxMana;
	}

}

void CharacterAttributes::updateLevel()
{
	while (this->experience >= this->expToNextLevel)
	{
		// level up 
		this->experience -= this->expToNextLevel;
		this->expToNextLevel = calculateExpToNext(++this->level);
		this->updateAttributes(true);
	}
}

void CharacterAttributes::update(const int experience)
{
	this->ganXP(experience);
	this->updateLevel();
}
