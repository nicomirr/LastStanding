#pragma once
#include <iomanip>
#include <sstream>
#include "../Entity.h"
#include "../TimeClock/TimeClock.h"
#include "../Player/Player.h"


class HoursInterface
{
private:

	static bool isOpen;
	bool isActive;

	static int hoursToSpend;
	static bool scrapNotEnoughShowText;

	float scrapNotEnoughTimer;

	Entity* background;
	Entity* buttonRight;
	Entity* buttonLeft;
	Entity* buttonClose;
	Entity* buttonOk;

	sf::Font* font;

	sf::Text* interfaceText;

	sf::Text* hoursLeftText;
	sf::Text* hoursToSpendText;

	sf::Text* resourcesText;
	sf::Text* scrapCostText;

	sf::Text* hoursSleptText;

	static sf::Text* notEnoughScrapText;

public:
	HoursInterface();

	void Update(int resources, float deltaTime);

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
	sf::Text* GetResourcesText() { return resourcesText; }
	sf::Text* GetScrapCostText() { return scrapCostText; }
	sf::Text* GetHoursSleptText() { return hoursSleptText; }

	static sf::Text* GetNotEnoughScrapText() { return notEnoughScrapText; }

	static bool GetIsOpen() { return isOpen; }
	static void SetIsOpen(bool value) { isOpen = value; }

	static bool GetScrapNotEnoughShowText() { return scrapNotEnoughShowText; }
	static void SetScrapNotEnoughShowText(bool value) { scrapNotEnoughShowText = value; }

	bool GetIsActive() { return isActive; }
	void SetIsActive(bool value) { isActive = value; }

	static int GetHoursToSpend() { return hoursToSpend; }

	static void ResetHoursToSpend() { hoursToSpend = 1; }

	void Destroy();

};