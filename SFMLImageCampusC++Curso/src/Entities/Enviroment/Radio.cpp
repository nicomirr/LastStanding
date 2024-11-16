#include "Radio.h"

bool Radio::wasUsed = false;
bool Radio::showCheckText = false;
bool Radio::isListeningRadio = false;
bool Radio::showRadioDialogueText = false;
bool Radio::showRadioText = false;
bool Radio::showRadioMessageText = false;
bool Radio::showRadioMessageDialogueText = false;

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

	radioMessageText = new sf::Text("...", *font, 16);

	radioMessageText->setPosition(763, 300);

	radioMessageDialogueText = new sf::Text("That's three days from now", *font, 16);

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

	ListenRadio(deltaTime, sceneManager, playerPos);

	float radioXPos = playerPos.x -35;
	float radioYPos = playerPos.y - 43;
	
	checkRadioText->setPosition({radioXPos, radioYPos});

}

void Radio::ListenRadio(float deltaTime, SceneManager* sceneManager, sf::Vector2f playerPos)
{
	if (!isListeningRadio) return;

	if (!wasUsed)
	{
		if (TimeClock::GetCurrentDay() <= 2)
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
		else if (TimeClock::GetCurrentDay() <= 3)
		{
			listenRadioTimer += deltaTime;

			if (listenRadioTimer >= 24)
			{
				showRadioMessageDialogueText = false;
				wasUsed = true;
				isListeningRadio = false;
				listenRadioTimer = 0;

				sceneManager->SetIsTransitioning(false);

			}
			else if (listenRadioTimer >= 21)
			{
				radioMessageDialogueText->setPosition((playerPos.x - 76), (playerPos.y - 40));
				radioMessageDialogueText->setString("Tomorrow I will begin preparing\n       some kind of signal");
			}
			else if (listenRadioTimer >= 19)
			{
				radioMessageDialogueText->setString("");
			}
			else if (listenRadioTimer >= 16)
			{
				radioMessageDialogueText->setPosition((playerPos.x - 66), (playerPos.y - 25));
				showRadioMessageDialogueText = true;
			}
			else if (listenRadioTimer >= 14)
			{
				showRadioMessageText = false;
			}
			else if (listenRadioTimer >= 11)
			{
				radioMessageText->setPosition(675, 300);
				radioMessageText->setString("...try ... make some signal ...");

			}
			else if (listenRadioTimer >= 9)
			{
				radioMessageText->setPosition(763, 300);
				radioMessageText->setString("...");
			}
			else if (listenRadioTimer >= 6)
			{
				radioMessageText->setPosition(635, 300);
				radioMessageText->setString("...emergency evacuation in infected area...");
			}
			else if (listenRadioTimer >= 4)
			{
				radioMessageText->setPosition(763, 300);
				radioMessageText->setString("...");
			}
			else if (listenRadioTimer >= 2)
			{
				radioMessageText->setPosition(727, 300);
				radioMessageText->setString("...on May 6...");
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

void Radio::ResetRadio()
{
	showCheckTextTimer = 0;
	listenRadioTimer = 0;
}

