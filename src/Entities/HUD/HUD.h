#pragma once
#include "../AnimatedEntity.h"
#include "AmmoHolder.h"



class HUD : public Entity
{
private:
	Entity HUDBar;
	AmmoHolder* ammoHolder;
	sf::Font* font;
	sf::Text* ammoText;

public:
	HUD(std::string imageFilePath, sf::Vector2i spriteSheetSize);
	void Update(int currentAmmo, float deltaTime);
	AmmoHolder* GetAmmoHolder() { return ammoHolder; }
	sf::Text* GetAmmoText() { return ammoText; }
};

