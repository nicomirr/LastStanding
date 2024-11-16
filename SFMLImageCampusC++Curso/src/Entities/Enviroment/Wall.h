#pragma once
#include "../Entity.h"
class Wall : public Entity
{
public:
	Wall(std::string imageFilePath, sf::Vector2i spriteSheetSize);

private:
	sf::FloatRect GetBounds() override;

};

