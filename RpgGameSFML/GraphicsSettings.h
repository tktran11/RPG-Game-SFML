#pragma once

/* GraphicsSettings.cpp is the body file for the graphics settings container. This stores all
the graphic elements to be passed from state to state to ensure that the game's playability and
window remain constant even after changing things via the Settings Menu
*/
class GraphicsSettings
{
public:
	GraphicsSettings();
	
	// Settings held by this container
	std::string gameTitle;
	sf::VideoMode windowResolution;
	bool isFullScreen;
	bool hasVerticalSync;
	unsigned fpsLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> displayModes;

	// Loading and unloading settings from a file
	void saveSettingsToFile(const std::string filePath);
	void loadSettingsFromFile(const std::string filePath);
};

