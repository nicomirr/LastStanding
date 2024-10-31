#include "HoursInterface.h"

HoursInterface::HoursInterface()
{
	std::string backgroundImageFilePath = "res\\textures\\time\\HoursInterface.png";
	sf::Vector2i backgroundSpriteSheetSize = { 168, 107 };
	background = new Entity(backgroundImageFilePath, backgroundSpriteSheetSize);

	background->Graphic().setOrigin(84, 53);
	background->Graphic().setPosition(600, 440);
	background->Graphic().setScale({ 2, 2 });


	std::string buttonLeftImageFilePath = "res\\textures\\time\\ButtonLeft.png";
	sf::Vector2i buttonLeftSpriteSheetSize = { 9, 8 };
	buttonLeft = new Entity(buttonLeftImageFilePath, buttonLeftSpriteSheetSize);


	std::string buttonRightImageFilePath = "res\\textures\\time\\ButtonRight.png";
	sf::Vector2i buttonRightSpriteSheetSize = { 9, 8 };
	buttonRight = new Entity(buttonRightImageFilePath, buttonRightSpriteSheetSize);


	std::string buttonCloseImageFilePath = "res\\textures\\time\\ButtonClose.png";
	sf::Vector2i buttonCloseSpriteSheetSize = { 10, 10 };
	buttonClose = new Entity(buttonCloseImageFilePath, buttonCloseSpriteSheetSize);



	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Pixel.otf";

	font->loadFromFile(fontPath);

	sf::Color* color = new sf::Color(88, 83, 74, 255);
		
	interfaceText = new sf::Text("", *font, 12);
	interfaceText->setFillColor(*color);

	
}

//JUGADOR DEBE FRENAR AL ABRIRSE.