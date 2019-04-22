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


	// Player Stat Bars
	float barHeight;

	// HP Bar
	float hpBarMax;
	sf::Text hpBarText;
	std::string hpBarString;
	sf::RectangleShape hpBar;

	// Mana Bar
	float manaBarMax;
	sf::Text manaBarText;
	std::string manaBarString;
	sf::RectangleShape manaBar;

	// Experience and Level Displaying
	sf::Text levelText;
	sf::String levelString;


	std::vector<std::string> textureFiles;
	std::vector<sf::Texture> uiTextures;
	sf::Texture texture;

	void initializeTextures();
	void initializeFont();
	void initializeTextDisplays();
	void initializePortrait();
	void initializeStatDock();
	void initializeHPBar();
	void initializeManaBar();

public:
	// Constructor
	CharacterGUI(PlayerCharacter* player, std::string playerType);

	// Updating
	void updateHPBar();
	void updateManaBar();
	void updateTextDisplay();
	void updateUI(const float& deltaTime);

	// Render
	void renderHPBar(sf::RenderTarget& target);
	void renderManaBar(sf::RenderTarget& target);
	void renderTextDisplay(sf::RenderTarget& target);
	void renderUI(sf::RenderTarget& target);
	// Destructor
};


