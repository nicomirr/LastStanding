#include "HoursInterface.h"

bool HoursInterface::isOpen;
int HoursInterface::hoursToSpend;
bool HoursInterface::scrapNotEnoughShowText;
sf::Text* HoursInterface::notEnoughScrapText;

HoursInterface::HoursInterface()
{
	isActive = false;

	hoursToSpend = 1;

	std::string backgroundImageFilePath = "res\\textures\\time\\HoursInterface.png";
	sf::Vector2i backgroundSpriteSheetSize = { 168, 107 };
	background = new Entity(backgroundImageFilePath, backgroundSpriteSheetSize);

	background->Graphic().setOrigin(84, 53);
	background->Graphic().setPosition(600, 440);
	background->Graphic().setScale({ 2, 2 });


	std::string buttonLeftImageFilePath = "res\\textures\\time\\ButtonLeft.png";
	sf::Vector2i buttonLeftSpriteSheetSize = { 9, 8 };
	buttonLeft = new Entity(buttonLeftImageFilePath, buttonLeftSpriteSheetSize);

	buttonLeft->Graphic().setOrigin(4, 4);
	buttonLeft->Graphic().setPosition(562, 505);
	buttonLeft->Graphic().setScale({ 2, 2 });

	buttonLeft->SetTag(Tag::SubstractHoursButton);

	std::string buttonRightImageFilePath = "res\\textures\\time\\ButtonRight.png";
	sf::Vector2i buttonRightSpriteSheetSize = { 9, 8 };
	buttonRight = new Entity(buttonRightImageFilePath, buttonRightSpriteSheetSize);

	buttonRight->Graphic().setOrigin(4, 4);
	buttonRight->Graphic().setPosition(632, 505);
	buttonRight->Graphic().setScale({ 2, 2 });

	buttonRight->SetTag(Tag::AddHoursButton);

	std::string buttonCloseImageFilePath = "res\\textures\\time\\ButtonClose.png";
	sf::Vector2i buttonCloseSpriteSheetSize = { 10, 10 };
	buttonClose = new Entity(buttonCloseImageFilePath, buttonCloseSpriteSheetSize);

	buttonClose->Graphic().setOrigin(5, 5);
	buttonClose->Graphic().setPosition(730, 365);
	buttonClose->Graphic().setScale({ 2, 2 });

	buttonClose->SetTag(Tag::CloseHoursInterfaceButton);

	std::string buttonOkImageFilePath = "res\\textures\\time\\ButtonOk.png";
	sf::Vector2i buttonOkSpriteSheetSize = { 16, 15 };
	buttonOk = new Entity(buttonOkImageFilePath, buttonOkSpriteSheetSize);

	buttonOk->Graphic().setOrigin(8, 7);
	buttonOk->Graphic().setPosition(730, 510);
	buttonOk->Graphic().setScale({ 2, 2 });
				

	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Pixel.otf";

	font->loadFromFile(fontPath);

	sf::Color* color = new sf::Color(88, 83, 74, 255);
		
	interfaceText = new sf::Text("", *font, 12);
	interfaceText->setFillColor(*color);

	hoursLeftText = new sf::Text("Hours left: 01", *font, 12);
	hoursLeftText->setFillColor(*color);
	hoursLeftText->setPosition(537, 470);

	hoursToSpendText = new sf::Text("12", *font, 12);
	hoursToSpendText->setFillColor(*color);
	hoursToSpendText->setPosition(587, 500);
	
	resourcesText = new sf::Text("", *font, 12);
	resourcesText->setFillColor(*color);
	resourcesText->setPosition(480, 442);

	scrapCostText = new sf::Text("50 scrap \\ h", *font, 12);
	scrapCostText->setFillColor(*color);
	scrapCostText->setPosition(610, 442);

	hoursSleptText = new sf::Text("", *font, 10);
	hoursSleptText->setFillColor(*color);
	hoursSleptText->setPosition(495, 420);

	notEnoughScrapText = new sf::Text("Not enough scrap", *font, 12);
	notEnoughScrapText->setFillColor(sf::Color(255, 255, 255, 255));
	notEnoughScrapText->setPosition(515, 555);
}

void HoursInterface::Update(int resources, float deltaTime)
{
	if (scrapNotEnoughShowText)
	{
		scrapNotEnoughTimer += deltaTime;

		if (scrapNotEnoughTimer >= 1.4)
		{
			scrapNotEnoughShowText = false;
			scrapNotEnoughTimer = 0;
		}
	}
	else
		scrapNotEnoughTimer = 0;

	if (!isActive)
	{
		buttonOk->Graphic().setPosition(1300, 510);
	}
	else
	{
		buttonOk->Graphic().setPosition(730, 510);
	}

	if (!isOpen)
	{
		isActive = false;
		return;
	}

	std::ostringstream hoursLeftStream;
	std::ostringstream hoursToSpendStream;

	std::string hoursLeftString;
	std::string hoursToSpendString;


	hoursLeftStream << std::setw(2) << std::setfill('0') << TimeClock::GetHours();
	hoursLeftString = hoursLeftStream.str();

	hoursToSpendStream << std::setw(2) << std::setfill('0') << hoursToSpend;
	hoursToSpendString = hoursToSpendStream.str();


	hoursLeftText->setString("Hours left: " + hoursLeftString);
	hoursToSpendText->setString(hoursToSpendString);



	std::ostringstream resourcesLeftStream;

	std::string resourcesLeftString;


	resourcesLeftStream << std::setw(2) << std::setfill('0') << resources;
	resourcesLeftString = resourcesLeftStream.str();

	resourcesText->setString("Scrap: " + resourcesLeftString);


	std::ostringstream hoursSleptStream;

	std::string hoursSleptString;


	hoursSleptStream << std::setw(2) << std::setfill('0') << Player::GetHoursSlept();
	hoursSleptString = hoursSleptStream.str();

	hoursSleptText->setString("    Hours slept: " + hoursSleptString + "\\06 \n  Sleeping affects aim");

}

void HoursInterface::SubstractHoursToSpend()
{
	hoursToSpend--;
	hoursToSpend = std::clamp(hoursToSpend, 1, TimeClock::GetHours());
}

void HoursInterface::AddHoursToSpend()
{
	hoursToSpend++;
	hoursToSpend = std::clamp(hoursToSpend, 1, TimeClock::GetHours());
}
//JUGADOR DEBE FRENAR AL ABRIRSE.

//	DIBUJAR HORAS
// SETEAR POSICION