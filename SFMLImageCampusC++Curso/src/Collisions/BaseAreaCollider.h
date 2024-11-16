#pragma once
#include "../Entities/Entity.h";

struct BaseAreaCollider : public Entity
{
	BaseAreaCollider(std::string imageFilePath, sf::Vector2i spriteSheetSize) : Entity(imageFilePath, spriteSheetSize){}

	sf::FloatRect GetBounds() override
	{
		return sprite.getGlobalBounds();
	}
};