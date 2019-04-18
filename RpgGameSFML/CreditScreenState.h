#pragma once
#include "gui.h"
#include "State.h"

/* CreditScreenState.h is the header file for the credit screen state, which
houses a simple picture of the contributors to this project, including the programmers
and our artist friend
*/
class CreditScreenState :
	public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	gui::Button* backButton;

	// Initializations
	void initializeBackground();
	void initializeKeybinds();
	void initializeButtons();
public:
	// Constructor
	CreditScreenState(StateData* stateInfo);

	// State Updating
	void updateInput(const float& deltaTime);
	void updateState(const float& deltaTime);

	// State Rendering
	void renderButtons(sf::RenderTarget* target);
	void renderState(sf::RenderTarget* target = nullptr);

	// Destructor
	virtual ~CreditScreenState();
};

