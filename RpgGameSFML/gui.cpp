#include "stdafx.h"
#include "Gui.h"

/* gui::Button is a class that handles the buttons of the game. It creates
   the button, and houses functions that check if the user is hovering or
   clicking that button */

/* Constructor for base buttons. It sets the initial state and position then
	  loads the texture for that button */
gui::Button::Button(float x, float y, float width, float height, std::string file, short unsigned buttonID)
{
	this->file = file; // texture loading
	this->buttonState = BUTN_IDLE;
	this->buttonID = buttonID;
	this->button.setPosition(sf::Vector2f(x, y));
	this->button.setSize(sf::Vector2f(width, height));
	this->button.setOrigin(sf::Vector2f(width / 2, height / 2));
	// exception
	if (!this->buttonTexture.loadFromFile(this->file))
	{
		throw "ERROR:FAILED_TO_LOAD_BUTTON_TEXTURE";
	}
	this->button.setTexture(&this->buttonTexture);
}

/* Alternative constructor for buttons with custom text, mostly for combat*/
gui::Button::Button(float x, float y, float width, float height, std::string file,
	std::string buttonText, short unsigned characterSize, short unsigned buttonID)
{
	this->file = file;
	this->buttonState = BUTN_IDLE;
	this->buttonID = buttonID;
	this->button.setPosition(sf::Vector2f(x, y));
	this->button.setSize(sf::Vector2f(width, height));
	this->button.setOrigin(sf::Vector2f(width / 2, height / 2));
	// loads texture from file, otherwise throws exception
	if (!this->buttonTexture.loadFromFile(this->file))
	{
		throw "ERROR:FAILED_TO_LOAD_BUTTON_TEXTURE";
	}
	this->button.setTexture(&this->buttonTexture);
	this->initializeFont();
	this->charSize = characterSize;
	this->textString = buttonText;
	this->initializeButtonText(this->textString, this->charSize);
	
}

// Font initialization for text based buttons
void gui::Button::initializeFont()
{
	this->font.loadFromFile("Fonts/MorrisRoman-Black.ttf");
}

// Initializes text to a button
void gui::Button::initializeButtonText(std::string buttonText, short unsigned size)
{
	this->text.setFont(this->font);
	this->text.setString(buttonText);
	this->text.setCharacterSize(size);
	this->text.setPosition(
		this->button.getPosition().x,
		this->button.getPosition().y * 0.95f
	);
	this->text.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
}

// Returns a boolean stating if the button is being pressed
const bool gui::Button::isPressed() const
{
	return (this->buttonState == BUTN_PRESSED);
}

// Returns the name of the file that stores the texture for the button
const std::string gui::Button::getTexture() const
{
	return std::string(this->file);
}

// Returns the button's ID
const short unsigned & gui::Button::getButtonID() const
{
	return this->buttonID;
}

// Sets the texture of a button to a new given texture 
void gui::Button::setTexture(std::string textureName)
{
	this->file = textureName;
	sf::Texture newTexture;
	// throws exception if file cannot be loaded
	if (!this->newTexture.loadFromFile(this->file) || (this->newTexture.getSize() != this->buttonTexture.getSize()))
	{
		throw "ERROR:FAILED_TO_LOAD_BUTTON_TEXTURE";
	}
	this->button.setTexture(&this->newTexture);
}

// Sets the button's ID to a new given ID
void gui::Button::setID(const short unsigned newID)
{
	this->buttonID = newID;
}

// Updates the current state of the button (checking to see whats happening) based on mouse position.
void gui::Button::updateButton(const sf::Vector2f mousePosition)
{
	this->buttonState = BUTN_IDLE;
	if (this->button.getGlobalBounds().contains(mousePosition))
	{
		this->buttonState = BUTN_HOVER;

		// While the button is being held down, set state to it being presed
		while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BUTN_PRESSED;
		}
	}
	switch (this->buttonState)
	{
	case BUTN_IDLE:
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

// Updates buttons and button text for text buttons
void gui::Button::updateTextButton(const sf::Vector2f mousePosition)
{
	this->buttonState = BUTN_IDLE;
	if (this->button.getGlobalBounds().contains(mousePosition))
	{
		this->buttonState = BUTN_HOVER;

		// While the button is being held down, set state to it being presed
		while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BUTN_PRESSED;
		}
	}
	switch (this->buttonState)
	{
	case BUTN_IDLE:
		this->button.setScale(1, 1);
		this->text.setScale(1, 1);
		break;
	case BUTN_HOVER:
		this->button.setScale(1.15, 1.15);
		this->text.setScale(1.15, 1.15);
		break;
	case BUTN_PRESSED:
		this->button.setScale(1.25, 1.25);
		this->text.setScale(1.25 , 1.25);
		break;
	default:
		break;
	}
}

// Draws the button onto the screen
void gui::Button::renderButton(sf::RenderTarget& target)
{
	target.draw(this->button);
}

// Alternative button drawing with text
void gui::Button::renderTextButton(sf::RenderTarget & target)
{
	this->renderButton(target);
	target.draw(this->text);
}

/* gui::DropDownMenu is a class that handles the drop down menus of the game. It creates
   the a drop down menu with changing elements, and houses functions that check if the user is hovering or
   clicking that various buttons within the drop down menu */

// ------------------------------------ DROP DOWN BUTTON MENU -----------------------------------------------------

// Costructor
gui::DropDownMenu::DropDownMenu(float xPos, float yPos, float width, float height, 
	std::string list[], unsigned numOfElements, unsigned defaultIndex) :listVisable(false)
{
	// Acitve element of a drop down menu is the button shown while all others are hiding
	this->activeElement = new gui::Button(xPos, yPos, width, height, list[defaultIndex]);

	for (unsigned i = 0; i < numOfElements; i++)
	{
		this->dropDownElements.push_back(new gui::Button(xPos + ((i + 1) * width), yPos, width, height, list[i], i));
	}
}

// Returns the ID of the active button
const unsigned short & gui::DropDownMenu::getActiveElementID() const
{
	return this->activeElement->getButtonID();
}

/* Updates the drop down menu to see whether or not the rest of the drop down should be visable.
   If it is, it updates the buttons and checks for any input on that drop down other than the active element
 */
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
		// Update the buttons in the drop down when visable
		for (auto &iterator : this->dropDownElements)
		{
			iterator->updateButton(mousePosition);

			if (iterator->isPressed())
			{
				this->listVisable = false;
				this->activeElement->setTexture(iterator->getTexture());
				this->activeElement->setID(iterator->getButtonID());
			}
		}
	}
}

// Renders the drop down menu to the window by rendering every button
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

// Destructor
gui::DropDownMenu::~DropDownMenu()
{
	delete this->activeElement;
	for (size_t i = 0; i < this->dropDownElements.size(); i++)
	{
		delete this->dropDownElements[i];
	}
}
