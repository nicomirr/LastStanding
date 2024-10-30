#pragma once
#include "../AnimatedEntity.h";

class HealthBar : public AnimatedEntity
{
private:
	float maxHealth;
	float currentHealth;

public:
	HealthBar(float maxHealth, sf::Vector2i animationFrameSize, std::string imageFilePath,
		sf::Vector2i spriteSheetSize);

	void Update(float deltaTime, sf::Vector2f position, float yOffset, float xOffset, float currentHealth);
	void SetMaxHealth(float maxHealth) { this->maxHealth = maxHealth; }
	float GetMaxHealth() { return maxHealth; }
	float GetCurrentHealth() { return currentHealth; }
	
};

