#pragma once

#include "../AnimatedEntity.h"
#include "../Weapon/Weapon.h"

class AmmoHolder : public AnimatedEntity
{
public:
	AmmoHolder(sf::Vector2i animationFrameSize, std::string imageFilePath,
		sf::Vector2i spriteSheetSize);
	void Update(Weapon weapon, int currentAmmo, float deltaTime);
};