#pragma once
/* CharacterAttributes.h is the header for the Character Attributes class, which controls the stats of the player
   and enemy characters. It holds information for the current state of the player such as their health or mana, 
   and also handles level progression
*/
class CharacterAttributes
{
public:
	// Map to bind stats annd moves to numeric values
	std::map<std::string, int> stats;
	std::map<std::string, float> moveset;

	// Leveling (for Player) and Level Management (all entities) 
	int level;
	int experience;
	int expToNextLevel;

	// Character Attributes (current vs max values)
	int currentHP;
	int maxHP;
	int currentMana;
	int maxMana;
	bool isDead = false;

	// Constructor
	CharacterAttributes(int characterLevel, std::string statFile, std::string movesetFile);

	// Attribute Calculations and Updating
	int calculateExpToNext(int characterLevel);
	void gainXP(const int experience);
	void initializeStats(std::string statsFile);
	void initializeMoveset(std::string movesetFile);
	void updateAttributes(const bool resetOnLevel);
	//void updateStats(std::string statName, int statChange);
	void updateLevel();
	void update(const int experience);

};

