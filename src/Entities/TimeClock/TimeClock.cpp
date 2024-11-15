#include "TimeClock.h"

int TimeClock::day = 1;
bool TimeClock::isNight = true;		//true 
bool TimeClock::isDay = false;			//false
bool TimeClock::startClockRotation = false;
bool TimeClock::endDayTextOpened = false;
int TimeClock::hours = 0;
bool TimeClock::resetClockAndLight = false;
bool TimeClock::endDayTextShown = false;




TimeClock::TimeClock(Entity* skyNight, std::string imageFilePath, sf::Vector2i spriteSheetSize)
	: Entity(imageFilePath, spriteSheetSize)
{
	this->skyNight = skyNight;

	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Pixel.otf";

	font->loadFromFile(fontPath);

	sf::Color* color = new sf::Color(88, 83, 74, 255);

	std::string daysText = "DAY " + std::to_string(day);
	dateText = new sf::Text(daysText, *font, 10);
	dateText->setPosition(249, 816);
	dateText->setFillColor(*color);
		
	timeText = new sf::Text("Hours left: " + std::to_string(hours), *font, 12);
	timeText->setPosition(42, 852);
	timeText->setFillColor(*color);

	sprite.setOrigin(sf::Vector2f(71, 62));
	sprite.setPosition(270, 875);

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

	buttonClose->SetTag(Tag::CloseEndDay);
	
	endDayText = new sf::Text("Its almost nighttime", *font, 12);
	endDayText->setPosition(500, 435);
	endDayText->setFillColor(*color);

}

void TimeClock::Update(float deltaTime)
{
	ClockRotation(deltaTime);

	if (hours == 0 && isDay && !DayTasksManager::GetScavengeResultsOpen())	
	{		
		if (!endDayTextShown)
		{
			endDayTextTimer += deltaTime;

			if (endDayTextTimer >= 2)
			{
				buttonClose->Graphic().setPosition(730, 365);
				endDayTextOpened = true;
				endDayTextTimer = 0;
				endDayTextShown = true;
			}
		}
		
	}
	else
	{
		buttonClose->Graphic().setPosition(1330, 365);
	}

	if (isDay)
		dateText->setString("MAY " + std::to_string(day));
	else if (isNight)
	{
		if (resetClockAndLight)
		{
			sf::Color skyColor = skyNight->Graphic().getColor();

			sf::Color color(skyColor.r, skyColor.g, skyColor.b, 255);
			skyNight->Graphic().setColor(color);
			sprite.setRotation(0);

			resetClockAndLight = false;

		}

		dateText->setString("MAY " + std::to_string(day));

	}

	timeText->setString("Hours left: " + std::to_string(hours));
		
}


void TimeClock::ClockRotation(float deltaTime)
{
	sf::Color skyColor = skyNight->Graphic().getColor();


	if (!startClockRotation) return;

	if (sprite.getRotation() >= 180)
	{
		sf::Color color(skyColor.r, skyColor.g, skyColor.b, 60);
		skyNight->Graphic().setColor(color);
	}
	else if (sprite.getRotation() >= 160)
	{
		sf::Color color(skyColor.r, skyColor.g, skyColor.b, 100);
		skyNight->Graphic().setColor(color);
	}
	else if (sprite.getRotation() >= 130)
	{
		sf::Color color(skyColor.r, skyColor.g, skyColor.b, 140);
	}
	else if (sprite.getRotation() >= 90)
	{
		sf::Color color(skyColor.r, skyColor.g, skyColor.b, 180);
		skyNight->Graphic().setColor(color);
	}
	else if (sprite.getRotation() >= 50)
	{
		sf::Color color(skyColor.r, skyColor.g, skyColor.b, 220);
		skyNight->Graphic().setColor(color);
	}

	if ((int)sprite.getRotation() != 180)	//TARDA 10 segundos
		sprite.rotate(15 * deltaTime);
	else
		startClockRotation = false;
}

void TimeClock::ResetTimeClock()
{
	day = 1;
	isNight = true;
	isDay = false;	
	startClockRotation = false;
	endDayTextOpened = false;
	hours = 0;
	resetClockAndLight = false;
	endDayTextShown = false;
	ResetClockAndLight();

}



