#include "stdafx.h"
#include "TitleScreenState.h"
/* TitleScreenState.cpp is the body file for the title screen. Here the player
   has the option of hitting the ENTER key on their keyboard to open the main menu 
*/

// Constructor for the Title Screen. It initializes the background, some keybinds (enter)
//   and the static button 
TitleScreenState::TitleScreenState(StateData* stateInfo)
	: State(stateInfo)
{
	this->initializeBackground();
	this->initializeKeybinds();
	this->initializeButtons();
}
// Sets the backround for the window by loading the
// appropriate texture
void TitleScreenState::initializeBackground()
{
	this->background.setSize(
		sf::Vector2f
		(static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("MenuTextures/StartScreen/TitleArt.png"))
	{
		throw "ERROR::TITLE_SCREEN_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);
}

/* Reads the keybind config file to determine what
   keys out of the game's supported keys are binded to actions for this 
    screen 
*/
void TitleScreenState::initializeKeybinds() 
{
	std::ifstream readKeybinds("Config/titleScreenKeybinds.ini");
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

// Creates any buttons
void TitleScreenState::initializeButtons()
{
	this->playButton = new gui::Button(640.f, 650.f, 431.f, 83.f, "MenuTextures/StartScreen/EnterButton.png");
}

// Checks to see if the enter button has been pressed
void TitleScreenState::updateInput(const float & deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("ENTER"))))
	{
		this->states->push(new MainMenuState(this->stateInfo));
	}
}

// updateState() checks to mouse position and input to update what is happening to the state 
void TitleScreenState::updateState(const float & deltaTime)
{
	this->updateMousePositions();
	this->updateInput(deltaTime);
}

// renderButtons() renders the button to the target window
void TitleScreenState::renderButtons(sf::RenderTarget * target)
{
	this->playButton->renderButton(*target);
}

// renderState() handles rendering the entire state to the window
void TitleScreenState::renderState(sf::RenderTarget * target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);
	this->renderButtons(target);
}

// Destructor
TitleScreenState::~TitleScreenState()
{
	delete this->playButton;
}
