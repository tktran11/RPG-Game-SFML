#pragma once
#include "PlayerCharacter.h"

// Forward Delcaration
class PlayerCharacter;

class CharacterGUI
{
private:
	// Player Loading for the UI
	PlayerCharacter* player;
	std::string playerType;

	// Font for stats displaying
	sf::Font font;

	// GUI Dock for the player UI
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

	// Experience, Level, and Stat Displaying
	sf::Text levelText;
	sf::String levelString;
	sf::Text statText;
	sf::String statString;

	// Texture loading for the various components of the Player UI
	std::vector<std::string> textureFiles;
	std::vector<sf::Texture> uiTextures;
	sf::Texture texture;

	// Initialization
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
	void updateUI(const float& deltaTime);
	void updateHPBar();
	void updateManaBar();
	void updateTextDisplay();

	// Render
	void renderUI(sf::RenderTarget& target);
	void renderHPBar(sf::RenderTarget& target);
	void renderManaBar(sf::RenderTarget& target);
	void renderTextDisplay(sf::RenderTarget& target);
};


