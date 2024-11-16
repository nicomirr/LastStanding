#pragma once
#include "../AnimatedEntity.h"
#include "AmmoHolder.h"
#include "../Weapon/Weapon.h"
#include "../Player/Player.h"



class HUD : public AnimatedEntity
{
private:
	Entity HUDBar;

	AmmoHolder* gunAmmoHolder;
	AmmoHolder* shotgunAmmoHolder;
	AmmoHolder* uziAmmoHolder;

	sf::Font* font;
	sf::Text* ammoText;

	void HUDAppearance();

public:
	HUD(sf::Vector2i animationFrameSize, std::string imageFilePath, sf::Vector2i spriteSheetSize);
	void Update(int resources, int currentAmmo, float deltaTime, Weapon weapon);

	AmmoHolder* GetGunAmmoHolder() { return gunAmmoHolder; }
	AmmoHolder* GetShotgunAmmoHolder() { return shotgunAmmoHolder; }
	AmmoHolder* GetUziAmmoHolder() { return uziAmmoHolder; }


	sf::Text* GetAmmoText() { return ammoText; }
};

