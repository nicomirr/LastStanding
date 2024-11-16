#pragma once
#include <iostream>
#include <algorithm>
#include <SFML/Audio.hpp>
#include "../Entities/Entity.h";

class AudioManager
{
private:
		
	static sf::Font* font;	
	static sf::Text* percentageText;

	static Entity* buttonLeft;
	static Entity* buttonRight;
	
	static int audioPercentage;
	static float audioRegulator;

public:
	static void Update();

	static float GetAudioRegulator() { return audioRegulator; }

	static Entity* GetButtonLeft() { return buttonLeft; }
	static Entity* GetButtonRight() { return buttonRight; }

	static sf::Text* GetPercentageText() { return percentageText; }
		
	static void CreateButtonLeft();
	static void CreateButtonRight();

	static void CreateFont();
	static void CreatePercentageText();

	static void AudioPercentageStatus();
	static void AddVolume();
	static void ReduceVolume();

	static void Destroy();
};

