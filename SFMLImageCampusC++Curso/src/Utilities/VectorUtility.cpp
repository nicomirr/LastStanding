#include "VectorUtility.h"

sf::Vector2f VectorUtility::UP = sf::Vector2f(0, -1);
sf::Vector2f VectorUtility::DOWN = sf::Vector2f({ 0, 1 });
sf::Vector2f VectorUtility::LEFT = sf::Vector2f({ -1, 0 });
sf::Vector2f VectorUtility::RIGHT = sf::Vector2f({ 1, 0 });

sf::Vector2f VectorUtility::Normalize(sf::Vector2f vector)
{
	sf::Vector2f normalized;

	float lenght = sqrt(vector.x * vector.x + vector.y * vector.y);
	normalized = lenght > 0 ? vector / lenght : sf::Vector2f(0, 0);

	return normalized;
}