#include "stdafx.h"
#include "GraphicsSettings.h"

/* 
GraphicsSettings.cpp is the body file for the graphics settings container. This stores all 
the graphic elements to be passed from state to state to ensure that the game's playability and
window remain constant even after changing things via the Settings Menu
*/

// Constructor
GraphicsSettings::GraphicsSettings()
{
	this->gameTitle = "";
	this->windowResolution = sf::VideoMode::getDesktopMode();
	this->isFullScreen = false;
	this->hasVerticalSync = false;
	this->fpsLimit = 144;
	this->contextSettings.antialiasingLevel = 0;
	this->displayModes = sf::VideoMode::getFullscreenModes();
}

// Saves settings to a file
void GraphicsSettings::saveSettingsToFile(const std::string filePath)
{
	std::ofstream outstream(filePath);

	if (outstream.is_open())
	{
		outstream << this->gameTitle << std::endl;
		outstream << this->windowResolution.width << " " << this->windowResolution.height << std::endl;;
		outstream << this->isFullScreen << std::endl;;
		outstream << this->fpsLimit << std::endl;;
		outstream << this->hasVerticalSync << std::endl;;
		outstream << this->contextSettings.antialiasingLevel << std::endl;;

	}
	outstream.close();
}

// Loads default settings from a file
void GraphicsSettings::loadSettingsFromFile(const std::string filePath)
{
	std::ifstream fileReader(filePath);

	if (fileReader.is_open())
	{
		std::getline(fileReader, gameTitle);
		fileReader >> this->windowResolution.width >> this->windowResolution.height;
		fileReader >> this->isFullScreen;
		fileReader >> this->fpsLimit;
		fileReader >> hasVerticalSync;
		fileReader >> this->contextSettings.antialiasingLevel;
	}
	fileReader.close();
}
