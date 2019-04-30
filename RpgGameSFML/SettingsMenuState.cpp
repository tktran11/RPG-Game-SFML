#include "stdafx.h"
#include "SettingsMenuState.h"

// Constructor
SettingsMenuState::SettingsMenuState(StateData* stateInfo)
	: State(stateInfo)
{
	// Resize window view to properly scale contents of the screen
	// PUT THIS SHIT EVERYWHERE
	sf::View properScreenView((sf::FloatRect(0.f, 0.f, this->window->getSize().x, this->window->getSize().y)));
	this->window->setView(properScreenView);

	this->initializeVariables();
	this->initializeBackground();
	this->initializeKeybinds("Config/SettingsStateKeybinds.ini");
	this->initializeGUI();
}

// Initializes the varying choices for the settings menu, including arrays that hold resolution options and such
void SettingsMenuState::initializeVariables()
{
	int choices = 3;
	// true = 1, false = 0
	this->hasVerticalSync = false;
	unsigned short widths[] = { 1280, 1152, 1366 };
	unsigned short heights[] = { 720, 648, 768 };
	unsigned frameRateChoices[] = { 144, 60, 30 };
	for (int i = 0; i < choices; i++)
	{
		this->mode.width = widths[i];
		this->mode.height = heights[i];
		this->resolutionModes.push_back(this->mode);

		this->fpsLimits.push_back(frameRateChoices[i]);
	}
}

// Creates the background by setting size and texture
void SettingsMenuState::initializeBackground()
{
	this->background.setSize(
		sf::Vector2f
		(static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("MenuTextures/Settings/SettingScreen.png"))
	{
		throw "ERROR::SETTINGS_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);
}

// Initializes the availible keybinds for the state
void SettingsMenuState::initializeKeybinds(std::string configFile)
{
	std::ifstream readKeybinds(configFile);
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

// Creates the GUI for the Settings state, including all its buttons and drop down menus
void SettingsMenuState::initializeGUI()
{

	this->buttons["BACK"] = new gui::Button((this->window->getSize().x * 0.703f),
		(this->window->getSize().y * 0.902f), (this->window->getSize().x * 0.156f),
		(this->window->getSize().y * 0.111f), "MenuTextures/Back.png");

	this->buttons["APPLY"] = new gui::Button((this->window->getSize().x * 0.898f),
		(this->window->getSize().y * 0.902f), (this->window->getSize().x * 0.156f),
		(this->window->getSize().y * 0.111f), "MenuTextures/Settings/Apply.png");

	this->buttons["VSYNC_ON"] = new gui::Button((this->window->getSize().x * 0.351f),
		(this->window->getSize().y * 0.743f), (this->window->getSize().x * 0.117f),
		(this->window->getSize().y * 0.104f), "MenuTextures/Settings/On.png");
	this->buttons["VSYNC_OFF"] = new gui::Button((this->window->getSize().x * 0.507f),
		(this->window->getSize().y * 0.743f), (this->window->getSize().x * 0.117f),
		(this->window->getSize().y * 0.104f), "MenuTextures/Settings/Off.png");

	// Resolution Textures
	std::string	resolutions[] = { "MenuTextures/Settings/1280x720.png", "MenuTextures/Settings/1152x648.png",
		 "MenuTextures/Settings/1366x768.png" };
	this->dropDown["RESOLUTIONS"] = new gui::DropDownMenu((this->window->getSize().x * 0.351f),
		(this->window->getSize().y * 0.326f), (this->window->getSize().x * 0.117f),
		(this->window->getSize().y * 0.104f), resolutions, this->resolutionModes.size());

	// Frame Rate Limit Choices
	std::string FPSChoices[] = { "MenuTextures/Settings/144.png", "MenuTextures/Settings/60.png",
	 "MenuTextures/Settings/30.png" };
	this->dropDown["FRAMERATE"] = new gui::DropDownMenu((this->window->getSize().x * 0.351f),
		(this->window->getSize().y * 0.465f), (this->window->getSize().x * 0.117f),
		(this->window->getSize().y * 0.104f), FPSChoices, 3);

	// Screen Type Textures
	std::string screenTypes[] = { "MenuTextures/Settings/Windowed.png", "MenuTextures/Settings/Fullscreen.png" };
	this->dropDown["SCREEN_MODE"] = new gui::DropDownMenu((this->window->getSize().x * 0.351f),
		(this->window->getSize().y * 0.604f), (this->window->getSize().x * 0.117f),
		(this->window->getSize().y * 0.104f), screenTypes, 2);


}

// Updates the buttons for the settings menu
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
		
			if (!this->stateInfo->graphicsSettings->isFullScreen)
			{
			
				this->window->create(this->stateInfo->graphicsSettings->windowResolution,
					this->stateInfo->graphicsSettings->gameTitle, sf::Style::Titlebar | sf::Style::Close);
			}
			else
			{
				this->window->create(this->stateInfo->graphicsSettings->windowResolution,
					this->stateInfo->graphicsSettings->gameTitle, sf::Style::Fullscreen);
			}
	
		// Set framerate

		this->stateInfo->graphicsSettings->fpsLimit = this->fpsLimits[this->dropDown["FRAMERATE"]->getActiveElementID()];
		this->window->setFramerateLimit(this->stateInfo->graphicsSettings->fpsLimit);

		// Set vertical sync
		this->stateInfo->graphicsSettings->hasVerticalSync = this->hasVerticalSync;
		this->window->setVerticalSyncEnabled(this->stateInfo->graphicsSettings->hasVerticalSync);

		// Resize window view to properly scale contents of the screen
		if (!this->stateInfo->graphicsSettings->isFullScreen)
		{
			sf::View properScreenView((sf::FloatRect(0, 0, 1920.f, 1080.f)));
			this->window->setView(properScreenView);
		}
		else
		{
			sf::View properScreenView((sf::FloatRect(0, 0, 1280, 720)));
			this->window->setView(properScreenView);
		}
		this->states->push(new MainMenuState(this->stateInfo));
	}

	// Drop Down Menu
	for (auto dropDownIt : this->dropDown)
	{
		dropDownIt.second->updateDropDown(this->mousPositView);
	}
}

// Updates any input on the state
void SettingsMenuState::updateInput(const float & deltaTime)
{
	this->updateButtons();
}

// Updates the state based on mouse movement and input
void SettingsMenuState::updateState(const float & deltaTime)
{
	this->updateMousePositions();
	this->updateInput(deltaTime);
}

// Renders GUI elements to the state
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

// Renders the entire state with the background to the window
void SettingsMenuState::renderState(sf::RenderTarget * target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);
	this->renderGUI(target);
}

// Destructor
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
