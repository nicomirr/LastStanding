#include "Entity.h"


Entity::Entity(){}

Entity::Entity(std::string imageFilePath, sf::Vector2i spriteSheetSize)
{
	sf::IntRect area(0, 0, spriteSheetSize.x, spriteSheetSize.y);

	texture.loadFromFile(imageFilePath, area);	//hacer resource manager, cargar cuando sea necesario por primera vez
	sprite.setTexture(texture, false);

	bounds = sprite.getGlobalBounds();
}

void Entity::Update(float deltaTime){ }

sf::FloatRect Entity::GetBounds()
{
	return bounds;
}

void Entity::SetBounds(sf::FloatRect bounds)
{
	this->bounds = bounds;
}

bool Entity::onCollission(Entity& self, Entity& other)
{
	sf::FloatRect thisBounds = self.GetBounds();	

	sf::FloatRect otherBounds = other.GetBounds();

	return thisBounds.intersects(otherBounds);
}



