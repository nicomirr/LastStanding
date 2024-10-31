#include "Radio.h"

Radio::Radio(std::string imageFilePath, sf::Vector2i spriteSheetSize) : Entity(imageFilePath, spriteSheetSize)
{
	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Pixel.otf";

	font->loadFromFile(fontPath);
	
	radioText = new sf::Text("", *font, 10);

	radioText->setPosition(762, 282);
	radioText->setFillColor(sf::Color(255, 255, 255, 255));

}

sf::FloatRect Radio::GetBounds()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();

	bounds.height *= 0.5;

	return bounds;
}