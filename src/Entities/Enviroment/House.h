#pragma once

#include "../AnimatedEntity.h"
#include "../HealthBar/HealthBar.h"

class House :  public AnimatedEntity
{
private:
    float maxHealth;
    float currentHealth;
    bool isDestroyed;
    HealthBar* healthBar;
    void HouseAppearance();
    void HealthBarAppearance();

public:
    House();
    House(sf::Vector2f pos, sf::Vector2i animationFrameSize, std::string imageFilePath, 
        sf::Vector2i spriteSheetSize);
    void Update(float deltaTme);
    sf::FloatRect GetBounds() override;
    HealthBar* GetHealthBar() { return healthBar; }
    void ReceiveDamage(float damage);
};

