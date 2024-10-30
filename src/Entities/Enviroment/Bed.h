#pragma once
#include "../Entity.h"
#include "../../Collisions/CollisionHandler.h"

class Bed : public Entity
{
public:
	Bed(std::string imageFilePath, sf::Vector2i spriteSheetSize);

private:
	sf::FloatRect GetBounds() override;
};

