#pragma once
#include "../AnimatedEntity.h"

class Fence :
    public AnimatedEntity
{
private:
    std::string fenceType;
    bool isFenceBroken;
    float maxHealth;
    float currentHealth;
    void FenceAppearance();

public:
    Fence(float health, std::string fenceType, sf::Vector2f fencePos, 
        sf::Vector2i animationFrameSize, std::string imageFilePath, 
        sf::Vector2i spriteSheetSize);
    void Update(float deltaTime) override;
	sf::FloatRect GetBounds() override;
    bool GetIsFenceBroken() { return isFenceBroken; }
    void ReceiveDamage(float damage);
    float GetHealth() { return currentHealth; }
};
