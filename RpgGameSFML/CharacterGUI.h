#pragma once
#include "PlayerCharacter.h"

// Forward Delcaration
class PlayerCharacter;

class CharacterGUI
{
private:
	PlayerCharacter* player;

	sf::Font font;
	sf::RectangleShape guiDock;
	sf::RectangleShape hpBarFull;
	sf::RectangleShape hpBarPercent;

	void initializeFont();
	void initializeStatDock();
	void initializeHPBar();
	void initializeManaBar();

public:
	// Constructor
	CharacterGUI(PlayerCharacter* player);

	void updateHPBar();
	void updateManaBar();
	void updateUI(const float& deltaTime);


	void renderUI(sf::RenderTarget& target);
	void renderHPBar();
	void renderManaBar();

	// Destructor
	virtual ~CharacterGUI();
};

