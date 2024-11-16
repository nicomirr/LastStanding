#pragma once
#include "../Entity.h"
#include "../../DayTasksManager/DayTasksManager.h"

class TimeClock : public Entity
{
private:
	sf::Text* endDayText;

	Entity* background;
	Entity* buttonClose;

	float endDayTextTimer;

	static int day;

	sf::Font* font;

	sf::Text* dateText;
	sf::Text* timeText;

	static bool resetClockAndLight;

	static bool endDayTextOpened;

	static bool startClockRotation;
	static bool isNight;
	static bool isDay;

	static bool endDayTextShown;

	static int hours;

	Entity* skyNight;

	void ClockRotation(float deltaTime);

public:
	TimeClock();
	TimeClock(Entity* skyNight, std::string imageFilePath, sf::Vector2i spriteSheetSize);
	void Update(float deltaTime);
	static int GetCurrentDay() { return day; }
	static void SetCurrentDay(int value) { day = value; }
	static void AddDay() { day++; }

	sf::Text* GetDateText() { return dateText; }
	sf::Text* GetTimeText() { return timeText; }

	static bool GetIsNight() { return isNight; }
	static void SetIsNight(bool value) { isNight =  value; }

	static bool GetIsDay() { return isDay; }
	static void SetIsDay(bool value) { isDay = value; }

	static int GetHours() { return hours; }
	static void SetHours(int time) { hours = time; }

	static bool GetEndDayTextOpened() { return endDayTextOpened; }
	static void SetEndDayTextOpened(bool value) { endDayTextOpened = value; }

	static void SetEndDayTextShown(bool value) { endDayTextShown = value; }

	sf::Text* GetEndDayText() { return endDayText; };
	Entity* GetBackground() { return background; };
	Entity* GetButtonClose() { return buttonClose; };

	static void SubstractHours(int time) { hours -= time; }

	static void StartClockRotation() { startClockRotation = true; }
	
	static void ResetClockAndLight() { resetClockAndLight = true; }

	void ResetTimeClock();
};

