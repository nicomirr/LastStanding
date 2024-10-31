#pragma once
#include "../Entity.h"
class Radio :  public Entity
{
public:
	Radio(std::string imageFilePath, sf::Vector2i spriteSheetSize);
	sf::Text* GetRadioText() { return radioText; }

private:
	sf::Font* font;
	sf::Text* radioText;
	sf::FloatRect GetBounds() override;
};

