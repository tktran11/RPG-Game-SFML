#include "stdafx.h"
#include "SettingsMenuState.h"

SettingsMenuState::SettingsMenuState(sf::RenderWindow* window, GraphicsSettings& graphics,
	std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states), graphicsSettings(graphics)
{
	this->initializeVariables();
	this->initializeBackground();
	this->initializeKeybinds();
	this->initializeGUI();
}


void SettingsMenuState::initializeVariables()
{
	int resolutionChoices = 3;
	unsigned short widths[] = { 1280, 1152, 1366 };
	unsigned short heights[] = { 720, 648, 768 };
	for (int i = 0; i < resolutionChoices; i++)
	{
		this->mode.width = widths[i];
		this->mode.height = heights[i];
		this->screenModes.push_back(this->mode);
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

	this->buttons["BACK"] = new gui::Button(850.f, 650.f, 200.f, 80.f, "SettingsMenuTextures/Back.png");
	this->buttons["APPLY"] = new gui::Button(1100.f, 650.f, 200.f, 80.f, "SettingsMenuTextures/Apply.png");
	std::vector<std::string> videoModes;
	std::string	resolutions[] = { "SettingsMenuTextures/1280x720.png", "SettingsMenuTextures/1152x648.png",
		 "SettingsMenuTextures/1366x768.png" };

	this->dropDown["SCREEN_SIZE"] = new gui::DropDownMenu(650, 250, 150, 75, resolutions, this->screenModes.size());
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
	if (this->buttons["APPLY"]->isPressed())
	{
		// Scale actual window size
		this->graphicsSettings.windowResolution = this->screenModes[this->dropDown["SCREEN_SIZE"]->getActiveElementID()];
		this->window->create(this->graphicsSettings.windowResolution, this->graphicsSettings.gameTitle, sf::Style::Default);
		// Resize window view to properly scale contents of the screen
		sf::View properScreenView((sf::FloatRect(0, 0, 1280.f, 720.f)));
		this->window->setView(properScreenView);
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
