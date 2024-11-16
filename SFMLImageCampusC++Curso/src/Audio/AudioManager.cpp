#include "AudioManager.h"

int AudioManager::audioPercentage;
float AudioManager::audioRegulator = 1.0f;

Entity* AudioManager::buttonLeft;
Entity* AudioManager::buttonRight;

sf::Font* AudioManager::font;
sf::Text* AudioManager::percentageText;

void AudioManager::Update()
{
	AudioPercentageStatus();

	std::string percentage = std::to_string(audioPercentage) + "%";
	percentageText->setString(percentage);
}

void AudioManager::CreateButtonLeft()
{
	std::string buttonLeftImageFilePath = "res\\textures\\time\\ButtonLeft.png";
	sf::Vector2i buttonLeftSpriteSheetSize = { 9, 8 };
	buttonLeft = new Entity(buttonLeftImageFilePath, buttonLeftSpriteSheetSize);

	buttonLeft->Graphic().setOrigin(4, 4);
	buttonLeft->Graphic().setPosition(552, 445);
	buttonLeft->Graphic().setScale({ 2, 2 });

	buttonLeft->SetTag(Tag::SubstractVolumeButton);	
}

void AudioManager::CreateButtonRight()
{
	std::string buttonRightImageFilePath = "res\\textures\\time\\ButtonRight.png";
	sf::Vector2i buttonRightSpriteSheetSize = { 9, 8 };
	buttonRight = new Entity(buttonRightImageFilePath, buttonRightSpriteSheetSize);

	buttonRight->Graphic().setOrigin(4, 4);
	buttonRight->Graphic().setPosition(642, 445);
	buttonRight->Graphic().setScale({ 2, 2 });

	buttonRight->SetTag(Tag::AddVolumeButton);
}

void AudioManager::CreateFont()
{
	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Roboto.ttf";

	font->loadFromFile(fontPath);
}

void AudioManager::CreatePercentageText()
{
	percentageText = new sf::Text("", *font, 15);
	percentageText->setPosition(586, 435);
	percentageText->setFillColor(sf::Color(60, 60, 60, 255));
}

void AudioManager::AudioPercentageStatus()
{
	audioRegulator = std::round(audioRegulator * 10) / 10;
	audioPercentage = audioRegulator * 100;
}

void AudioManager::AddVolume()
{
	audioRegulator += 0.1f;
	audioRegulator = std::clamp(audioRegulator, 0.0f, 1.0f);
}

void AudioManager::ReduceVolume()
{
	audioRegulator -= 0.1f;
	audioRegulator = std::clamp(audioRegulator, 0.0f, 1.0f);
}

void AudioManager::Destroy()
{
	if (font != nullptr)
	{
		delete font;
		font = nullptr;
	}

	if (percentageText != nullptr)
	{
		delete percentageText;
		percentageText = nullptr;
	}

	if (buttonLeft != nullptr)
	{
		delete buttonLeft;
		buttonLeft = nullptr;
	}

	if (buttonRight != nullptr)
	{
		delete buttonRight;
		buttonRight = nullptr;
	}

}
