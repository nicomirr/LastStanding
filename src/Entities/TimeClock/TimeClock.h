#pragma once
#include "../Entity.h"

class TimeClock : public Entity
{
private:
	static int day;

	sf::Font* font;

	sf::Text* dateText;
	sf::Text* timeText;

	static bool startClockRotation;
	static bool isNight;
	static bool isDay;

	static int hours;

	Entity* skyNight;

	void ClockRotation(float deltaTime);

public:
	TimeClock();
	TimeClock(Entity* skyNight, std::string imageFilePath, sf::Vector2i spriteSheetSize);
	void Update(float deltaTime);
	int GetCurrentDay() { return day; }

	sf::Text* GetDateText() { return dateText; }
	sf::Text* GetTimeText() { return timeText; }

	static bool GetIsNight() { return isNight; }
	static void SetIsNight(bool value) { isNight =  value; }

	static bool GetIsDay() { return isDay; }
	static void SetIsDay(bool value) { isDay = value; }

	static int GetHours() { return hours; }
	static void SetHours(int time) { hours = time; }

	static void StartClockRotation() { startClockRotation = true; }
	

};

