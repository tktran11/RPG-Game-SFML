#pragma once
class CharacterAttributes
{
public:
	// Leveling (for Player) and Level Management (all entities)
	unsigned level;
	unsigned experience;
	unsigned expToNextLevel;
	unsigned attributePoints;
	
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
	CharacterAttributes(unsigned characterLevel);

	// Functions

	// REMOVE LATER
	std::string debugPrint() const;


	int calculateExpToNext(unsigned characterLevel);
	void updateAttributes(const bool resetOnLevel);
	void updateLevel();
	void update();
	// Destructor
	virtual ~CharacterAttributes();
};

