#pragma once
/* CharacterAttributes.h is the header for the Character Attributes class, which controls the stats of the player
   and enemy characters. It holds information for the current state of the player such as their health or mana, 
   and also handles level progression
*/
class CharacterAttributes
{
public:
	// Leveling (for Player) and Level Management (all entities) 
	int level;
	int experience;
	int expToNextLevel;
	int attributePoints;
	
	// Attributes (Consider putting all of the stats in a container (array, vector, map, something) for ease of either hard coding
	// or file reading
	int attack;
	int speed;
	int defense;

	// unchanging stats (base stats for calculation of HP and Mana), read in when player created, never changed
	int vitality;
	int intelligence;

	int currentHP;
	int maxHP;
	int currentMana;
	int maxMana;

	// Constructor
	CharacterAttributes(int characterLevel);

	// Functions

	// REMOVE LATER
	std::string debugPrint() const;

	
	int calculateExpToNext(int characterLevel);
	void ganXP(const int experience);
	void updateAttributes(const bool resetOnLevel);
	void updateLevel();
	void update(const int experience);

};

