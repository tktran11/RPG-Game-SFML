#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	this->initializeVariables();
	this->initializeGraphicsSettings();
	this->startWindow();
	this->initializeKeyboard();
	this->initializeStateData();
	this->startStates();

}

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

}

void Game::startStates()
{
	this->states.push(new TitleScreenState(&this->stateData));
}

void Game::initializeStateData()
{
	this->stateData.gameWindow = this->gameWindow;
	this->stateData.graphicsSettings = &this->graphicsSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
}

void Game::initializeGraphicsSettings()
{
	this->graphicsSettings.loadSettingsFromFile("Config/graphicsSettings.ini");
}

void Game::initializeVariables()
{
	this->gameWindow = nullptr;
	this->deltaTime = 0.f;
}

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

void Game::updateDeltaTime()
{
	// updates DeltaTime to the time it took to render one frame of our game. 
	this->deltaTime = this->deltaClock.restart().asSeconds();
}

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

void Game::updateGame()
{
	this->updateEvents();
	if (!this->states.empty())
	{
		this->states.top()->updateState(this->deltaTime);
		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	// End Game or Application
	else {
		this->gameWindow->close();
	}
}

void Game::renderToWindow()
{
	this->gameWindow->clear();

	if (!this->states.empty()) {
		this->states.top()->renderState();
	}
	this->gameWindow->display();
}

void Game::runGame()
{
	while (this->gameWindow->isOpen())
	{
		this->updateDeltaTime();
		this->updateGame();
		this->renderToWindow();
	}
}

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
