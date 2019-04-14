#include "stdafx.h"
#include "SettingsMenuState.h"

SettingsMenuState::SettingsMenuState(StateData* stateInfo)
	: State(stateInfo)
{
	this->initializeVariables();
	this->initializeBackground();
	this->initializeKeybinds();
	this->initializeGUI();
}


void SettingsMenuState::initializeVariables()
{
	int choices = 3;
	// true = 1, false = 0
	this->hasVerticalSync = false;
	unsigned short widths[] = { 1280, 1152, 1366 };
	unsigned short heights[] = { 720, 648, 768 };
	unsigned frameRateChoices[] = { 144, 120, 60 };
	for (int i = 0; i < choices; i++)
	{
		this->mode.width = widths[i];
		this->mode.height = heights[i];
		this->resolutionModes.push_back(this->mode);

		this->fpsLimits.push_back(frameRateChoices[i]);
	}


}
void SettingsMenuState::initializeBackground()
{
	this->background.setSize(
		sf::Vector2f
		(static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("MainMenuTextures/MenuArt.png"))
	{
		throw "ERROR::SETTINGS_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void SettingsMenuState::initializeKeybinds()
{
	std::ifstream readKeybinds("Config/SettingsStateKeybinds.ini");
	if (readKeybinds.is_open()) {
		std::string keybind = "";
		std::string bindedValue = "";

		while (readKeybinds >> keybind >> bindedValue)
		{
			this->keyBinds[keybind] = this->supportedKeys->at(bindedValue);
		}
	}
	readKeybinds.close();
}

void SettingsMenuState::initializeGUI()
{

	this->buttons["BACK"] = new gui::Button(900.f, 650.f, 200.f, 80.f, "SettingsMenuTextures/Back.png");
	this->buttons["APPLY"] = new gui::Button(1150.f, 650.f, 200.f, 80.f, "SettingsMenuTextures/Apply.png");
	this->buttons["VSYNC_ON"] = new gui::Button(450.f, 550.f, 150.f, 75.f, "SettingsMenuTextures/On.png");
	this->buttons["VSYNC_OFF"] = new gui::Button(650.f, 550.f, 150.f, 75.f, "SettingsMenuTextures/Off.png");

	// Resolution Textures
	std::string	resolutions[] = { "SettingsMenuTextures/1280x720.png", "SettingsMenuTextures/1152x648.png",
		 "SettingsMenuTextures/1366x768.png" };
	this->dropDown["RESOLUTIONS"] = new gui::DropDownMenu(450.f, 250.f, 150.f, 75.f, resolutions, this->resolutionModes.size());

	// Screen Type Textures
	std::string screenTypes[] = {"SettingsMenuTextures/Windowed.png", "SettingsMenuTextures/Fullscreen.png"};
	this->dropDown["SCREEN_MODE"] = new gui::DropDownMenu(450.f, 450.f, 150.f, 75.f, screenTypes, 2);

	std::string FPSChoices[] = { "SettingsMenuTextures/1280x720.png", "SettingsMenuTextures/1152x648.png",
		 "SettingsMenuTextures/1366x768.png" };
	// Frame Rate Limit Choices
	this->dropDown["FRAMERATE"] = new gui::DropDownMenu(450.f, 650.f, 150.f, 75.f, FPSChoices, 3);
}

void SettingsMenuState::updateButtons()
{
	for (auto &iterator : this->buttons)
	{
		iterator.second->updateButton(this->mousPositView);
	}
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}
	if (this->buttons["VSYNC_ON"]->isPressed())
	{
		this->hasVerticalSync = true;
	}
	if (this->buttons["VSYNC_OFF"]->isPressed())
	{
		this->hasVerticalSync = false;
	}
	if (this->buttons["APPLY"]->isPressed())
	{
		// Scale actual window size (for resolution choices)
		this->stateInfo->graphicsSettings->windowResolution = this->resolutionModes[this->dropDown["RESOLUTIONS"]->getActiveElementID()];
		// Change window type (fullscreen = 1, windowed = 0)
		this->stateInfo->graphicsSettings->isFullScreen = this->dropDown["SCREEN_MODE"]->getActiveElementID();

		// Create window based on graphics settings to be applied
		unsigned screenMode = this->stateInfo->graphicsSettings->isFullScreen;
		switch (screenMode)
		{
		case 0:
			this->window->create(this->stateInfo->graphicsSettings->windowResolution,
			this->stateInfo->graphicsSettings->gameTitle, sf::Style::Titlebar | sf::Style::Close);
			break;
		case 1:
			this->window->create(this->stateInfo->graphicsSettings->windowResolution,
				this->stateInfo->graphicsSettings->gameTitle, sf::Style::Fullscreen);
			break;
		}

		// Set framerate
		this->stateInfo->graphicsSettings->fpsLimit = this->fpsLimits[this->dropDown["FRAMERATE"]->getActiveElementID()];
		this->window->setFramerateLimit(this->stateInfo->graphicsSettings->fpsLimit);

		// Set vertical sync
		this->stateInfo->graphicsSettings->hasVerticalSync = this->hasVerticalSync;
		this->window->setVerticalSyncEnabled = this->stateInfo->graphicsSettings->hasVerticalSync;

		// Resize window view to properly scale contents of the screen
		sf::View properScreenView((sf::FloatRect(0, 0, 1280.f, 720.f)));
		this->window->setView(properScreenView);

		// Save settings to file to make them default on next load
		this->stateInfo->graphicsSettings->saveSettingsToFile("Config/graphicsSettings.ini");
		

	}

	// Drop Down Menu

	for (auto dropDownIt : this->dropDown)
	{
		dropDownIt.second->updateDropDown(this->mousPositView);
	}
}

void SettingsMenuState::updateInput(const float & deltaTime)
{
}

void SettingsMenuState::updateState(const float & deltaTime)
{
	this->updateButtons();
	this->updateMousePositions();
	this->updateInput(deltaTime);
}

void SettingsMenuState::renderGUI(sf::RenderTarget * target)
{
	for (auto &iterator : this->buttons)
	{
		iterator.second->renderButton(*target);
	}
	for (auto dropDownIt : this->dropDown)
	{
		dropDownIt.second->renderDropDown(*target);
	}
}

void SettingsMenuState::renderState(sf::RenderTarget * target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);
	this->renderGUI(target);

}
SettingsMenuState::~SettingsMenuState()
{
	// Clean Buttons
	auto iterator = this->buttons.begin();
	for (iterator; iterator != this->buttons.end(); ++iterator)
	{
		delete iterator->second;
	}

	// Clean Drop Down Menu
	auto dropDownIt = this->dropDown.begin();
	for (dropDownIt; dropDownIt != this->dropDown.end(); ++dropDownIt)
	{
		delete dropDownIt->second;
	}
}
