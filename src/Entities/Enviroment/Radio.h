#pragma once
#include "../Entity.h"
class Radio :  public Entity
{
public:
	Radio(std::string imageFilePath, sf::Vector2i spriteSheetSize);

private:
	sf::FloatRect GetBounds() override;
};

