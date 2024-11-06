#pragma once
#include "../Entity.h"
#include "../../SceneManager/SceneManager.h"

class Radio :  public Entity
{
private:
	sf::Font* font;

	sf::Text* radioText;
	sf::Text* checkRadioText;
	sf::Text* radioDialogueText;

	sf::FloatRect GetBounds() override;
	
	static bool wasUsed;

	static bool showCheckText;
	static bool showRadioDialogueText;
	static bool showRadioText;
	
	static bool isListeningRadio;

	float showCheckTextTimer;

	float listenRadioTimer;

public:
	Radio(std::string imageFilePath, sf::Vector2i spriteSheetSize);
	
	void Update(sf::Vector2f playerPos, float deltaTime, SceneManager* sceneManager);
	
	sf::Text* GetRadioText() { return radioText; }
	sf::Text* GetCheckRadioText() { return checkRadioText; }
	sf::Text* GetRadioDialogueText() { return radioDialogueText; }

	static bool GetWasUsed() { return wasUsed; }
	static void SetWasUsed(bool value) { wasUsed = value; }

	static bool GetShowCheckText() { return showCheckText; }
	static void SetShowCheckText(bool value) { showCheckText = value; }

	static bool GetIsListeningRadio() { return isListeningRadio; }
	static void SetIsListeningRadio(bool value) { isListeningRadio = value; }

	static bool GetShowRadioDialogueText() { return showRadioDialogueText; }

	static bool GetShowRadioText() { return showRadioText; }
	static void SetShowRadioText(bool value) { showRadioText = value; }

	void ListenRadio(float deltaTime, SceneManager* sceneManager);

};

