#pragma once
#include <iomanip>
#include <sstream>
#include "../Entity.h"
#include "../TimeClock/TimeClock.h"


class HoursInterface
{
private:
	
	static bool isOpen;
	bool isActive;
	
	static int hoursToSpend;

	Entity* background;
	Entity* buttonRight;
	Entity* buttonLeft;
	Entity* buttonClose;
	Entity* buttonOk;

	sf::Font* font;
	
	sf::Text* interfaceText;

	sf::Text* hoursLeftText;
	sf::Text* hoursToSpendText;


public:
	HoursInterface();

	void Update();

	Entity* GetBackground() { return background; }
	Entity* GetButtonRight() { return buttonRight; }
	Entity* GetButtonLeft() { return buttonLeft; }
	Entity* GetButtonClose() { return buttonClose; }
	Entity* GetButtonOk() { return buttonOk; }

	void SetInterfaceText(std::string text) { interfaceText->setString(text); }
	sf::Text* GetInterfaceText() { return interfaceText; }

	static void SubstractHoursToSpend();
	static void AddHoursToSpend();

	sf::Text* GetHoursLeftText() { return hoursLeftText; }
	sf::Text* GetHoursToSpendText() { return hoursToSpendText; }

	static bool GetIsOpen() { return isOpen; }
	static void SetIsOpen(bool value) { isOpen = value; }

	bool GetIsActive() { return isActive; }
	void SetIsActive(bool value) { isActive = value; }

};