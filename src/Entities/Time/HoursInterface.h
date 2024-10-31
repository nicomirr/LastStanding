#pragma once
#include "../Entity.h"

class HoursInterface
{
private:
	bool isActive;
	
	Entity* background;
	Entity* buttonRight;
	Entity* buttonLeft;
	Entity* buttonClose;


	sf::Font* font;
	sf::Text* interfaceText;

public:
	HoursInterface();

	Entity* GetBackground() { return background; }
	Entity* GetButtonRight() { return buttonRight; }
	Entity* GetButtonLeft() { return buttonLeft; }
	Entity* GetButtonClose() { return buttonClose; }

	void SetInterfaceText(std::string text) { interfaceText->setString(text); }

	bool GetIsActive() { return isActive; }
	void SetIsActive(bool value) { isActive = value; }

};