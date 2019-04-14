#include "stdafx.h"
#include "GraphicsSettings.h"


GraphicsSettings::GraphicsSettings()
{
	this->gameTitle = "";
	this->windowResolution = sf::VideoMode::getDesktopMode();
	this->isFullScreen = false;
	this->verticalSyncOn = false;
	this->fpsLimit = 144;
	this->contextSettings.antialiasingLevel = 0;
	this->displayModes = sf::VideoMode::getFullscreenModes();

}


void GraphicsSettings::saveSettingsToFile(const std::string filePath)
{
	std::ofstream outstream(filePath);

	if (outstream.is_open())
	{
		outstream << this->gameTitle;
		outstream << this->windowResolution.width << " " << this->windowResolution.height;
		outstream << this->isFullScreen;
		outstream << this->fpsLimit;
		outstream << this->verticalSyncOn;
		outstream << this->contextSettings.antialiasingLevel;

	}
	outstream.close();
}

void GraphicsSettings::loadSettingsFromFile(const std::string filePath)
{
	std::ifstream fileReader(filePath);

	if (fileReader.is_open())
	{
		std::getline(fileReader, gameTitle);
		fileReader >> this->windowResolution.width >> this->windowResolution.height;
		fileReader >> this->isFullScreen;
		fileReader >> this->fpsLimit;
		fileReader >> verticalSyncOn;
		fileReader >> this->contextSettings.antialiasingLevel;
	}
	fileReader.close();
}
