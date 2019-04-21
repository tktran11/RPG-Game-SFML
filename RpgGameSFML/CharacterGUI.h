#pragma once
#include "PlayerCharacter.h"

// Forward Delcaration
class PlayerCharacter;

class CharacterGUI
{
private:
	PlayerCharacter* player;
	std::string playerType;

	sf::Font font;
	sf::RectangleShape portrait;
	sf::RectangleShape portraitPic;
	sf::RectangleShape guiDock;
	sf::RectangleShape hpBar;
	sf::RectangleShape manaBar;

	std::vector<std::string> textureFiles;
	std::vector<sf::Texture> uiTextures;
	sf::Texture texture;

	void initializeTextures();
	void initializeFont();
	void initializePortrait();
	void initializeStatDock();
	void initializeHPBar();
	void initializeManaBar();

public:
	// Constructor
	CharacterGUI(PlayerCharacter* player, std::string playerType);

	void updateHPBar();
	void updateManaBar();
	void updateUI(const float& deltaTime);


	void renderUI(sf::RenderTarget& target);
	void renderHPBar();
	void renderManaBar();

	// Destructor
	virtual ~CharacterGUI();
};

