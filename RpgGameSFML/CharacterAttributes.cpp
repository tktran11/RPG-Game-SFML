#include "stdafx.h"
#include "CharacterAttributes.h"

/* CharacterAttributes.cpp is the body for the Character Attributes class, which controls the stats of the player
   and enemy characters. It holds information for the current state of the player such as their health or mana,
   and also handles level progression
*/

// Constructor
CharacterAttributes::CharacterAttributes(int characterLevel, std::string statFile, std::string movesetFile)
{
	this->level = characterLevel;
	this->initializeStats(statFile);
	this->initializeMoveset(movesetFile);
	this->experience = 0;
	this->expToNextLevel = calculateExpToNext(this->level);
	this->updateLevel();
	this->updateAttributes(true);
}

// Maps a string to a value when read from a file for stat values
// that will be stored in a map
void CharacterAttributes::initializeStats(std::string statsFile)
{
	std::ifstream readStats(statsFile);
	if (readStats.is_open())
	{
		std::string statType = " ";   
		int statValue;

		while (readStats >> statType >> statValue)
		{
			this->stats[statType] = statValue;
		}
	}
	readStats.close();
}

// Maps a string to a value when read from a file for moveset numbers and multipliers
void CharacterAttributes::initializeMoveset(std::string movesetFile)
{
	std::ifstream readStats(movesetFile);
	if (readStats.is_open())
	{
		std::string abilityName = " ";
		float abilityValue;

		while (readStats >> abilityName >> abilityValue)
		{
			this->moveset[abilityName] = abilityValue;
		}
	}
	readStats.close();
}

// Calculates the experience needed to reach the next level
int CharacterAttributes::calculateExpToNext(int characterLevel)
{
	int neededExp = 0;
	if (characterLevel < 2)
	{
		neededExp = 100;
	}
	else
	{
		neededExp = (characterLevel * 75);
	}
	return neededExp;
}

// Mutator for experience, adds given experience to user stat for experience
void CharacterAttributes::gainXP(const int experience)
{
	this->experience += experience;
}

// Updates the character's relevent stats per frame
void CharacterAttributes::updateAttributes(const bool resetOnLevel)
{
	//Updates max HP and mana based on base stats and level multiplier
	this->maxHP = this->stats["VIT"] * 10 + (this->stats["ARM"] * 10 * (this->level - 1));
	this->maxMana = (this->stats["INT"] * 4) + (this->stats["INT"] * (this->level - 1)); 

	// Updates ATK/SPD/Def based on base stats and level multiplier
	this->stats["ATK"] += ((this->level - 1) * this->stats["STR"]);
	this->stats["SPD"] += ((this->level - 1) * this->stats["DEX"]);
	this->stats["DEF"] += ((this->level - 1) * this->stats["ARM"]);


	// if we decide to heal on level up, reset total health and mana
	if (resetOnLevel)
	{
		this->currentHP = this->maxHP;
		this->currentMana = this->maxMana;
	}
}

// Updates the character's level, changing relevant stats, and resets the experience afterwards
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

// Update function to check for experience gain and the need for level updating
void CharacterAttributes::update(const int experience)
{
	this->gainXP(experience);
	this->updateLevel();
}
