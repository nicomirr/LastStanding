#pragma once
#include <SFML/System/Vector2.hpp>
#include <iostream>

class Moveable
{
protected:
	sf::Vector2f direction;
	sf::Vector2f previousDirection;
	sf::Vector2f currentPos;
};