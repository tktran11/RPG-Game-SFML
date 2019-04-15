#include "stdafx.h"
#include "Gui.h"

/* gui::Button is a class that handles the buttons of the game. It creates
   the button, and houses functions that check if the user is hovering or
   clicking that button */

   /* Constructor for the button class. It sets the initial state and position then
	  loads the texture for that button */
gui::Button::Button(float x, float y, float width, float height, std::string file, short unsigned buttonID)
{
	this->file = file;
	this->buttonState = BUTN_IDLE;
	this->buttonID = buttonID;
	this->button.setPosition(sf::Vector2f(x, y));
	this->button.setSize(sf::Vector2f(width, height));
	this->button.setOrigin(sf::Vector2f(width / 2, height / 2));
	if (!this->buttonTexture.loadFromFile(this->file))
	{
		throw "ERROR:FAILED_TO_LOAD_BUTTON_TEXTURE";
	}

	this->button.setTexture(&this->buttonTexture);
}

/* isPressed() returns a boolean stating if the button is being pressed */
const bool gui::Button::isPressed() const
{
	return (this->buttonState == BUTN_PRESSED);
}

const std::string gui::Button::getTexture() const
{
	return std::string(this->file);
}

const short unsigned & gui::Button::getButtonID() const
{
	return this->buttonID;
}

void gui::Button::changeTexture(std::string textureName)
{
	this->file = textureName;
	sf::Texture newTexture;
	if (!this->newTexture.loadFromFile(this->file) || (this->newTexture.getSize() != this->buttonTexture.getSize()))
	{
		throw "ERROR:FAILED_TO_LOAD_BUTTON_TEXTURE";
	}
	this->button.setTexture(&this->newTexture);
}

void gui::Button::changeID(const short unsigned newID)
{
	this->buttonID = newID;
}

/* updateButton() updates the current state of the button (checking to see whats happening)
   based on mouse position. */
void gui::Button::updateButton(const sf::Vector2f mousePosition)
{
	this->buttonState = BUTN_IDLE;
	if (this->button.getGlobalBounds().contains(mousePosition))
	{
		this->buttonState = BUTN_HOVER;

		while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BUTN_PRESSED;
		}
	}
	switch (this->buttonState)
	{
	case BUTN_IDLE:
		// Note to self, for enlarging buttons, set origin first then set scale.
		this->button.setScale(1, 1);
		break;
	case BUTN_HOVER:
		this->button.setScale(1.25, 1.25);
		break;
	case BUTN_PRESSED:
		this->button.setScale(1.5, 1.5);
		break;
	default:
		break;
	}
}

/* renderButton() draws the button onto the screen*/
void gui::Button::renderButton(sf::RenderTarget& target)
{
	target.draw(this->button);
}

// ------------------------------------ DROP DOWN BUTTON MENU -----------------------------------------------------
gui::DropDownMenu::DropDownMenu(float xPos, float yPos, float width, float height, 
	std::string list[], unsigned numOfElements, unsigned defaultIndex) :listVisable(false)
{
	
	this->activeElement = new gui::Button(xPos, yPos, width, height, list[defaultIndex]);

	for (unsigned i = 0; i < numOfElements; i++)
	{
		this->dropDownElements.push_back(new gui::Button(xPos + ((i + 1) * width), yPos, width, height, list[i], i));
	}
}

const unsigned short & gui::DropDownMenu::getActiveElementID() const
{
	return this->activeElement->getButtonID();
}

void gui::DropDownMenu::updateDropDown(const sf::Vector2f mousePosition)
{
	this->activeElement->updateButton(mousePosition);

	// Change menu visability
	if (this->activeElement->isPressed())
	{
		if (this->listVisable)
		{
			this->listVisable = false;
		}
		else
		{
			this->listVisable = true;
		}
	}
	if (this->listVisable)
	{

		for (auto &iterator : this->dropDownElements)
		{
			iterator->updateButton(mousePosition);

			if (iterator->isPressed())
			{
				this->listVisable = false;
				this->activeElement->changeTexture(iterator->getTexture());
				this->activeElement->changeID(iterator->getButtonID());
			}
		}
	}
}

void gui::DropDownMenu::renderDropDown(sf::RenderTarget & target)
{
	this->activeElement->renderButton(target);

	if (this->listVisable)
	{
		for (auto &iterator : this->dropDownElements)
		{
			iterator->renderButton(target);
		}
	}
}

gui::DropDownMenu::~DropDownMenu()
{
	delete this->activeElement;
	for (size_t i = 0; i < this->dropDownElements.size(); i++)
	{
		delete this->dropDownElements[i];
	}
}
