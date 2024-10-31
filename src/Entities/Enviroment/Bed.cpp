#include "Bed.h"

HoursInterface* Bed::hoursInterface;

Bed::Bed(std::string imageFilePath, sf::Vector2i spriteSheetSize) : Entity(imageFilePath, spriteSheetSize)
{
	hoursInterface = new HoursInterface();
}

sf::FloatRect Bed::GetBounds()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();

	bounds.height *= 0.7;

	return bounds;
}