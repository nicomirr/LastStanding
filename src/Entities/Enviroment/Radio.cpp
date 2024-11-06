#include "Radio.h"

bool Radio::wasUsed = false;
bool Radio::showCheckText = false;
bool Radio::isListeningRadio = false;
bool Radio::showRadioDialogueText = false;
bool Radio::showRadioText = false;

Radio::Radio(std::string imageFilePath, sf::Vector2i spriteSheetSize) : Entity(imageFilePath, spriteSheetSize)
{
	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Roboto.ttf";

	font->loadFromFile(fontPath);
	
	radioText = new sf::Text("		...", *font, 18);

	radioText->setPosition(730, 300);
	radioText->setFillColor(sf::Color(255, 255, 255, 255));

	checkRadioText = new sf::Text(" I should check \n  the radio first", *font, 16);

	radioDialogueText = new sf::Text("Nothing", *font, 16);

}

void Radio::Update(sf::Vector2f playerPos, float deltaTime, SceneManager* sceneManager)
{
	float radioDialogueTextXPos = playerPos.x - 5;
	float radioDialogueTextYPos = playerPos.y - 30;

	radioDialogueText->setPosition({ radioDialogueTextXPos, radioDialogueTextYPos });

	if (showCheckText)
	{
		showCheckTextTimer += deltaTime;

		if (showCheckTextTimer >= 3)
		{
			showCheckTextTimer = 0;
			showCheckText = false;
		}
	}

	ListenRadio(deltaTime, sceneManager);

	float radioXPos = playerPos.x -35;
	float radioYPos = playerPos.y - 43;
	
	checkRadioText->setPosition({radioXPos, radioYPos});
}

void Radio::ListenRadio(float deltaTime, SceneManager* sceneManager)
{
	if (!isListeningRadio) return;

	if (!wasUsed)
	{
		listenRadioTimer += deltaTime;
		
		if (listenRadioTimer >= 6)
		{
			showRadioDialogueText = false;
			wasUsed = true;
			isListeningRadio = false;
			listenRadioTimer = 0;

			sceneManager->SetIsTransitioning(false);
		}
		else if (listenRadioTimer >= 3)
		{
			showRadioDialogueText = true;

		}
		else if (listenRadioTimer >= 2)
		{
			showRadioText = false;
		}
	}
	else
	{
		listenRadioTimer += deltaTime;
		showRadioText = true;


		if (listenRadioTimer >= 3)
		{
			isListeningRadio = false;
			showRadioText = false;
			listenRadioTimer = 0;
		}

	}

}

sf::FloatRect Radio::GetBounds()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();

	bounds.height *= 0.5;

	return bounds;
}

 //SACAR LA E AL ESCUCHAR RADIO