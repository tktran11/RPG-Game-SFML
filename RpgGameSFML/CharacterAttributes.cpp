#include "stdafx.h"
#include "CharacterAttributes.h"

/* CharacterAttributes.cpp is the body for the Character Attributes class, which controls the stats of the player
   and enemy characters. It holds information for the current state of the player such as their health or mana,
   and also handles level progression
*/

// Constructor
CharacterAttributes::CharacterAttributes(int characterLevel)
{
	this->level = characterLevel;
	this->experience = 0;
	this->expToNextLevel = calculateExpToNext(this->level);
	this->intelligence = 10; // DEFAULT FOR TESTING, CHANGE OR INPUT AS NEEDED
	this->vitality = 10; // DEFAULT FOR TESTING, CHANGE OR INPUT AS NEEDED
	this->updateLevel();
	this->updateAttributes(true);
}

void CharacterAttributes::initializeStats()
{

	std::ifstream readStats("Config/KnightStats.txt");
	if (readStats.is_open())
	{
		std::string statType = " ";
		int statValue;

		while (readStats >> statType >> statValue)
		{
			this->stats[statType] = statValue;

		}
	}

	// iterator to display the stats
	auto i = this->stats.begin();
	for (i; i != this->stats.end(); i++)
	{
		std::cout << i->first;
		std::cout << " Mapped to " << i->second << std::endl;
	}
	system("cls");

	readStats.close();
}

// Calculates the experience needed to reach the next level
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

// Mutator for experience, adds given experience to user stat for experience
void CharacterAttributes::gainXP(const int experience)
{
	this->experience += experience;
}

// Updates the character's relevent stats upon level update
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
	this->initializeStats();
}
