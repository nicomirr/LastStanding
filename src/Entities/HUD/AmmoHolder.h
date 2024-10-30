#pragma once

#include "../AnimatedEntity.h"

class AmmoHolder : public AnimatedEntity
{
public:
	AmmoHolder(sf::Vector2i animationFrameSize, std::string imageFilePath,
		sf::Vector2i spriteSheetSize);
	void Update(int currentAmmo, float deltaTime);
};