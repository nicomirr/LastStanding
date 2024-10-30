#pragma once
#include "../AnimatedEntity.h"
#include "../HealthBar/HealthBar.h"

class Car :
    public AnimatedEntity
{
private:
    float maxHealth;
    float currentHealth;
    HealthBar* healthBar;
    static bool isDestroyed;
    float collissionRadius;
    void CarAppearance();
    void HealthBarAppearance();

public:

    Car();
    Car(sf::Vector2f pos, sf::Vector2i animationFrameSize, std::string imageFilePath, 
        sf::Vector2i spriteSheetSize);
    void Update(float deltaTime);
    sf::FloatRect GetBounds() override;
    HealthBar* GetHealthBar() { return healthBar; }
    static bool GetIsDestroyed() { return isDestroyed; }
    void SetIsDestroyed(bool isDestroyed) { this->isDestroyed = isDestroyed; }
    float GetCollissionRadius() { return collissionRadius; }
    void ReceiveDamage(float damage);
};

