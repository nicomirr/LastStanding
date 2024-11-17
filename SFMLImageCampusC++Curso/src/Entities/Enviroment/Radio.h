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
	sf::Text* radioMessageText;
	sf::Text* radioMessageDialogueText;

	sf::FloatRect GetBounds() override;
	
	static bool wasUsed;

	static bool showCheckText;
	static bool showRadioDialogueText;
	static bool showRadioText;

	static bool showRadioMessageText;
	static bool showRadioMessageDialogueText;
	
	static bool isListeningRadio;

	float showCheckTextTimer;

	float listenRadioTimer;

public:
	Radio(std::string imageFilePath, sf::Vector2i spriteSheetSize);
	
	void Update(sf::Vector2f playerPos, float deltaTime, SceneManager* sceneManager);
	
	sf::Text* GetRadioText() { return radioText; }
	sf::Text* GetCheckRadioText() { return checkRadioText; }
	sf::Text* GetRadioDialogueText() { return radioDialogueText; }
	sf::Text* GetRadioMessageText() { return radioMessageText; }
	sf::Text* GetRadioMessageDialogueText() { return radioMessageDialogueText; }

	static bool GetWasUsed() { return wasUsed; }
	static void SetWasUsed(bool value) { wasUsed = value; }

	static bool GetShowCheckText() { return showCheckText; }
	static void SetShowCheckText(bool value) { showCheckText = value; }

	static bool GetIsListeningRadio() { return isListeningRadio; }
	static void SetIsListeningRadio(bool value) { isListeningRadio = value; }

	static bool GetShowRadioDialogueText() { return showRadioDialogueText; }

	static bool GetShowRadioText() { return showRadioText; }
	static void SetShowRadioText(bool value) { showRadioText = value; }

	static bool GetShowRadioMessageText() { return showRadioMessageText; }
	static void SetShowRadioMessageText(bool value) { showRadioMessageText = value; }

	static bool GetShowRadioMessageDialogueText() { return showRadioMessageDialogueText; }
	static void SetShowRadioMessageDialogueText(bool value) { showRadioMessageDialogueText = value; }

	void ListenRadio(float deltaTime, SceneManager* sceneManager, sf::Vector2f playerPos);

	void ResetRadio();

	void Destroy();
};

