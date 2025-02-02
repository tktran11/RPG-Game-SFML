#pragma once

/* gui is a namespace that handles the button interface for the game. Specifically,
   it houses the Button class (which makes buttons) and the DropDownMenu class
   which handles running multiple buttons and a keytimer to ensure tha button presses
   don't affect multiple states. */

// Enums for the button states
enum button_States { BUTN_IDLE = 0, BUTN_HOVER, BUTN_PRESSED};

namespace gui
{
	class Button
	{
	private:
		// Data values
		short unsigned buttonState;
		short unsigned buttonID;
	
		// Texture Based Button
		std::string file;
		sf::Texture buttonTexture;
		sf::Texture newTexture;
		sf::RectangleShape button;

		// Text Based Button Alternatives
		sf::Font font;
		std::string textString;
		sf::Text text;
		short unsigned charSize;
		
		//Initializer functions
		void initializeFont();
		void initializeButtonText(std::string buttonText, short unsigned size);

	public:
		// Constructor
		Button(float x, float y, float width, float height, 
			std::string file, short unsigned buttonID = 0);
		Button(float x, float y, float width, float height,
			std::string file, std::string buttonText, short unsigned characterSize, short unsigned buttonID = 0);

		// Assessors
		const bool isPressed() const;
		const std::string getTexture() const;
		const short unsigned& getButtonID() const;

		// Mutators
		void setTexture(std::string textureName);
		void setID(const short unsigned newID);

		// Button Management
		void updateButton(const sf::Vector2f mousePosition);
		void updateTextButton(const sf::Vector2f mousePosition);

		// Renders the button type
		void renderButton(sf::RenderTarget& target);
		void renderTextButton(sf::RenderTarget& target);
	};

	class DropDownMenu
	{
	private:
		gui::Button* activeElement;
		bool listVisable;
	public:
		// Constructor
		DropDownMenu(float xPos, float yPos, float width, float height,
			std::string list[], unsigned numOfElements, unsigned defaultIndex = 0);
		
		// Accessor
		const unsigned short& getActiveElementID() const;
		// Vector of elements
		std::vector<gui::Button*> dropDownElements;

		// Update and render drop down menu
		void updateDropDown(const sf::Vector2f mousePosition);
		void renderDropDown(sf::RenderTarget& target);

		//Virtual Destructor
		virtual ~DropDownMenu();
	};
}