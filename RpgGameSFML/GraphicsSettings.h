#pragma once
class GraphicsSettings
{
public:
	GraphicsSettings();

	std::string gameTitle;
	sf::VideoMode windowResolution;
	bool isFullScreen;
	bool verticalSyncOn;
	unsigned fpsLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> displayModes;

	void saveSettingsToFile(const std::string filePath);
	void loadSettingsFromFile(const std::string filePath);
};

