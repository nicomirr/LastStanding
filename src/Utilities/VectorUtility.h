#pragma once
#include <cmath>
#include <SFML/System.hpp>


struct VectorUtility
{
public:

	static sf::Vector2f UP;
	static sf::Vector2f DOWN;
	static sf::Vector2f LEFT;
	static sf::Vector2f RIGHT;

	static sf::Vector2f Normalize(sf::Vector2f vector);
};