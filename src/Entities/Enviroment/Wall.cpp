#include "Wall.h"

Wall::Wall(std::string imageFilePath, sf::Vector2i spriteSheetSize) : Entity (imageFilePath, spriteSheetSize)
{

}

sf::FloatRect Wall::GetBounds()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();

	bounds.top -= (bounds.height - (bounds.height * 1.3));
	bounds.height *= 0.3;

	return bounds;
}