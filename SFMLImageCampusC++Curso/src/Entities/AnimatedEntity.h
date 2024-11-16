#pragma once

#include <unordered_map>
#include <iostream>
#include "SFML/System.hpp"
#include "AnimationData.h"
#include "Entity.h"

class AnimatedEntity : public Entity
{
private:
	std::unordered_map<std::string, AnimationData> animations;
	sf::Vector2i frameSize;
	sf::Vector2i imagePosition;
	std::string currentAnimationName;
	float currentFrameTime;
	float animationTimer;

public:
	AnimatedEntity();
	AnimatedEntity(sf::Vector2i animationFrameSize, std::string imageFilePath,
		sf::Vector2i spriteSheetSize);
	
	void Update(float deltaTime) override;

	void AddAnimation(std::string animationName, AnimationData animationData);
	void RemoveAnimation(std::string animationName);
	std::string GetCurrentAnimation() { return currentAnimationName; }
	void SetCurrentAnimation(std::string animationName);
	void SetAnimationFrameSize(sf::Vector2i animationFrameSize);

};

//shift F12 se muestran TODAS las referencias