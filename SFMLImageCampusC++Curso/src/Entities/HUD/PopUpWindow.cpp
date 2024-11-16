#include "PopUpWindow.h"

bool PopUpWindow::popUpWindowOpen;

PopUpWindow::PopUpWindow()
{
	isActive = false;

	std::string backgroundImageFilePath = "res\\textures\\time\\HoursInterface.png";
	sf::Vector2i backgroundSpriteSheetSize = { 168, 107 };
	background = new Entity(backgroundImageFilePath, backgroundSpriteSheetSize);

	background->Graphic().setOrigin(84, 53);
	background->Graphic().setPosition(600, 440);
	background->Graphic().setScale({ 2, 2 });

	std::string buttonCloseImageFilePath = "res\\textures\\time\\ButtonClose.png";
	sf::Vector2i buttonCloseSpriteSheetSize = { 10, 10 };
	buttonClose = new Entity(buttonCloseImageFilePath, buttonCloseSpriteSheetSize);

	buttonClose->Graphic().setOrigin(5, 5);
	buttonClose->Graphic().setPosition(730, 365);
	buttonClose->Graphic().setScale({ 2, 2 });

	buttonClose->SetTag(Tag::ClosePopUpWindow);

	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Roboto.ttf";

	font->loadFromFile(fontPath);

	text = new sf::Text("", *font, 18);
	text->setFillColor(sf::Color(88, 83, 74, 255));

	std::string okButtonImageFilePath = "res\\textures\\time\\OkButton.png";
	sf::Vector2i okButtonSpriteSheetSize = { 25, 23 };
	okButton = new Entity(okButtonImageFilePath, okButtonSpriteSheetSize);

	okButton->Graphic().setOrigin(12, 11);
	okButton->Graphic().setPosition(552, 480);
	okButton->Graphic().setScale({ 2, 2});

	std::string cancelButtonButtonImageFilePath = "res\\textures\\time\\CancelButton.png";
	sf::Vector2i cancelButtonButtonSpriteSheetSize = { 25, 23 };
	cancelButton = new Entity(cancelButtonButtonImageFilePath, cancelButtonButtonSpriteSheetSize);

	cancelButton->Graphic().setOrigin(12, 11);
	cancelButton->Graphic().setPosition(642, 480);
	cancelButton->Graphic().setScale({ 2, 2 });

	cancelButton->SetTag(Tag::ClosePopUpWindow);

}

void PopUpWindow::Update()
{
	if (!isActive)
	{
		buttonClose->Graphic().setPosition(1330, 365);
		okButton->Graphic().setPosition(1330, 365);
		cancelButton->Graphic().setPosition(1330, 365);
	}
	else
	{
		buttonClose->Graphic().setPosition(730, 365);
		okButton->Graphic().setPosition(540, 440);
		cancelButton->Graphic().setPosition(640, 440);
	}

}
