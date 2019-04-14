#pragma once

/* gui is a namespace that handles the button interface for the game. Specifically,
   it houses the Button class (which makes buttons) and the DropDownMenu class
   which handles running multiple buttons and a keytimer to ensure tha button presses
   don't affect multiple states. */

enum button_States { BUTN_IDLE = 0, BUTN_HOVER, BUTN_PRESSED};

namespace gui
{
	class Button
	{
	private:

		short unsigned buttonState;
		short unsigned buttonID;
	
		std::string file;
		sf::Texture buttonTexture;
		sf::Texture newTexture;
		sf::RectangleShape button;

	public:
		// Constructor
		Button(float x, float y, float width, float height, 
			std::string file, short unsigned buttonID = 0);

		// Assessors
		const bool isPressed() const;
		const std::string getTexture() const;
		const short unsigned& getButtonID() const;
		// Button Management

		void changeTexture(std::string textureName);
		void changeID(const short unsigned newID);
		void updateButton(const sf::Vector2f mousePosition);
		void renderButton(sf::RenderTarget& target);

	};

	class DropDownMenu
	{
	private:

		gui::Button* activeElement;
		std::vector<gui::Button*> dropDownElements;
		bool listVisable;
	public:
		DropDownMenu(float xPos, float yPos, float width, float height,
			std::string list[], unsigned numOfElements, unsigned defaultIndex = 0);

		// Accessor
		const unsigned short& getActiveElementID() const;

		void updateDropDown(const sf::Vector2f mousePosition);
		void renderDropDown(sf::RenderTarget& target);
		virtual ~DropDownMenu();
	};
}
