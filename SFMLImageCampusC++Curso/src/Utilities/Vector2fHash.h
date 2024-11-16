#pragma once

#ifndef VECTOR2F_HASH_H
#define VECTOR2F_HASH_H

#include <SFML/Graphics.hpp>
#include <functional>


struct Vector2fHash {
    std::size_t operator()(const sf::Vector2f& vec) const {
        return std::hash<float>()(vec.x) ^ std::hash<float>()(vec.y);
    }
};


struct Vector2fEqual {
    bool operator()(const sf::Vector2f& lhs, const sf::Vector2f& rhs) const {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

#endif 