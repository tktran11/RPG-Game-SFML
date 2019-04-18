#include "stdafx.h"
#include "Game.h"

// Constructor
Game::Game()
{
	this->initializeVariables();
	this->initializeGraphicsSettings();
	this->startWindow();
	this->initializeKeyboard();
	this->initializeStateData();
	this->startStates();

}
// Creates the window that the game is played on based on default settings 
void Game::startWindow()
{
	if (this->graphicsSettings.isFullScreen)
	{
		this->gameWindow = new sf::RenderWindow(this->graphicsSettings.windowResolution,
			this->graphicsSettings.gameTitle, sf::Style::Resize, this->graphicsSettings.contextSettings);
	}
	else
	{
		this->gameWindow = new sf::RenderWindow(this->graphicsSettings.windowResolution,
			this->graphicsSettings.gameTitle, sf::Style::Titlebar | sf::Style::Close, this->graphicsSettings.contextSettings);
	}
	
	this->gameWindow->setFramerateLimit(this->graphicsSettings.fpsLimit);
	this->gameWindow->setVerticalSyncEnabled(this->graphicsSettings.hasVerticalSync);
	sf::View properScreenView((sf::FloatRect(0, 0, 1280.f, 720.f)));
	this->gameWindow->setView(properScreenView);
}

// Begins the state engine that runs the game
void Game::startStates()
{
	this->states.push(new TitleScreenState(&this->stateData));
}

// Initializes state data to be passed from state to state
void Game::initializeStateData()
{
	this->stateData.gameWindow = this->gameWindow;
	this->stateData.graphicsSettings = &this->graphicsSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
}

// Initializes graphics settings to be passed from state to state
void Game::initializeGraphicsSettings()
{
	this->graphicsSettings.loadSettingsFromFile("Config/graphicsSettings.ini");
}

// Sets starting values for the game to avoid garbage
void Game::initializeVariables()
{
	this->gameWindow = nullptr;
	this->deltaTime = 0.f;
}

/* Initializes the list of supported keys for the entire game. Each state has the opportunity to assign any of these 
   keys to specific functionality within the state itself 
*/
void Game::initializeKeyboard()
{
	std::ifstream readKeys("Config/supportedKeys.ini");
	if (readKeys.is_open()) {
		std::string key = "";
		int keyValue = 0;

		while (readKeys >> key >> keyValue)
		{
			this->supportedKeys[key] = keyValue;
		}
	}
	readKeys.close();
}

/* updates DeltaTime to the time it took to render one frame of our game. Needed for
   less hardware dependant playability 
*/
void Game::updateDeltaTime()
{
	this->deltaTime = this->deltaClock.restart().asSeconds();
}

/* Polls game window for SFML events, specifically if the game is still running or not. Closes and destroys
   window when applicable 
 */
void Game::updateEvents()
{
	while (this->gameWindow->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
		{
			this->gameWindow->close();
		}
	}
}

// Updates the game by checking the top of the state stack and updating that single state
void Game::updateGame()
{
	this->updateEvents();
	if (!this->states.empty())
	{
		this->states.top()->updateState(this->deltaTime);
		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			this->states.pop();
		}
	}
	// End Game or Application
	else {
		this->gameWindow->close();
	}
}

// Renders the game to the window, by clearing it and rendering the top state
void Game::renderToWindow()
{
	this->gameWindow->clear();

	if (!this->states.empty()) {
		this->states.top()->renderState();
	}
	// Displays everything to the game window
	this->gameWindow->display();
}

// Runs the game
void Game::runGame()
{
	while (this->gameWindow->isOpen())
	{
		this->updateDeltaTime();
		this->updateGame();
		this->renderToWindow();
	}
}

// Destructor
Game::~Game()
{
	delete this->gameWindow;
	while (!this->states.empty())
	{
		this->states.top()->endState();
		delete this->states.top();
		this->states.pop();
	}
}
