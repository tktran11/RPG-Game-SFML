#include "stdafx.h"
#include "CharacterAttributes.h"


CharacterAttributes::CharacterAttributes(unsigned characterLevel)
{
	this->level = characterLevel;
	this->experience = 0;
	this->expToNextLevel = calculateExpToNext(characterLevel);
	this->attributePoints = 0;
	this->intelligence = 10; // DEFAULT FOR TESTING, CHANGE OR INPUT AS NEEDED
	this->vitality = 10; // DEFAULT FOR TESTING, CHANGE OR INPUT AS NEEDED
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

int CharacterAttributes::calculateExpToNext(unsigned characterLevel)
{
	int neededExp = 0;
	if (characterLevel >= 2)
	{
		neededExp = 100;
	}
	else
	{
		neededExp = (characterLevel * 50);
	}
	return neededExp;
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
		++this->level;
		// level up 
		this->experience = this->expToNextLevel;
		this->expToNextLevel = calculateExpToNext(this->level);
		// this->attributePoints++
		// NOTE: --------------------------------
		// Either manually update the stats by letting user choose or simply ++ to all the stats, which instead of having
		// individually you can make in a map or array or something
	}
}

void CharacterAttributes::update()
{
	this->updateLevel();
}


CharacterAttributes::~CharacterAttributes()
{
}
