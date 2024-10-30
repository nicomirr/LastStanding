#include "TimeClock.h"

int TimeClock::day = 1;
bool TimeClock::isNight = true;		//true 
bool TimeClock::isDay = false;			//false
bool TimeClock::startClockRotation = false;
int TimeClock::hours = 0;



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


}

void TimeClock::Update(float deltaTime)
{
	ClockRotation(deltaTime);

	if (isDay)
		dateText->setString("DAY " + std::to_string(day));
	else if (isNight)
		dateText->setString("NIGHT " + std::to_string(day));

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