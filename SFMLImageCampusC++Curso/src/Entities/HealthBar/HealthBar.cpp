#include "HealthBar.h"

HealthBar::HealthBar(float maxHealth, sf::Vector2i animationFrameSize, std::string imageFilePath, 
	sf::Vector2i spriteSheetSize) : AnimatedEntity(animationFrameSize, imageFilePath, spriteSheetSize)
{
	this->maxHealth = maxHealth;
	this->currentHealth = this->maxHealth;

}

void HealthBar::Update(float deltaTime, sf::Vector2f position,float yOffset, float xOffset, float currentHealth)
{
	AnimatedEntity::Update(deltaTime);

	this->currentHealth = currentHealth;

	position.y += yOffset;
	position.x += xOffset;

	sprite.setPosition(position);
}

