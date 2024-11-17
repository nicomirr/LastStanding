#pragma once
#include "../Entity.h"

class PopUpWindow
{
private:
	static bool popUpWindowOpen;

	sf::Font* font;
	sf::Text* text;

	Entity* background;
	Entity* buttonClose;

	Entity* okButton;
	Entity* cancelButton;

	bool isActive;

public:
	PopUpWindow();
	
	void Update();

	bool GetIsActive() { return isActive; }
	void SetIsActive(bool value) { isActive = value; }

	Entity* GetBackground() { return background; }
	Entity* GetButtonClose() { return buttonClose; }

	Entity* GetOkButton() { return okButton; }
	Entity* GetCancelButton() { return cancelButton; }

	sf::Text* GetText() { return text; }

	static bool GetPopUpWindowOpen() { return popUpWindowOpen; }
	static void SetPopUpWindowOpen(bool value) { popUpWindowOpen = value; }

	void Destroy();

};