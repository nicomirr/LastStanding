#pragma once
#include "../AnimatedEntity.h"
#include "../Time/HoursInterface.h"
#include "../../Collisions/CollisionHandler.h"

class SOSSign : public AnimatedEntity
{
private:
	float health;
	static int scrap;
	static bool signBuilt;
	int neededScrap;

	sf::Font* font;
	sf::Text* buildPercentageText;

	sf::FloatRect GetBounds() override;
	static HoursInterface* hoursInterface;

public:
	SOSSign(sf::Vector2i animationFrameSize, std::string imageFilePath,
		sf::Vector2i spriteSheetSize);
	void Update();
	static HoursInterface* GetHoursInterface() { return hoursInterface; }
	sf::Text* GetScrapNeededText() { return buildPercentageText; }
	static void AddScrap(int value) { scrap += value; }
	void CheckSignBuiltStatus();
	void SignAppearance();

	static void BuildSOSSign();
		
	static bool GetSignBuilt() { return signBuilt; }

	void ResetSOSSign();
};

