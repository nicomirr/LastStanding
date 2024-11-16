#pragma once

#include "../AnimatedEntity.h"
#include "../HealthBar/HealthBar.h"
#include <iomanip>
#include <sstream>

class House :  public AnimatedEntity
{
private:
    int healthPercentage;

    sf::Font* font;
    sf::Text* percentageText;

    float maxHealth;
    static float currentHealth;
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
    static float GetHealth() { return currentHealth; }
    float GetMaxHealth() { return maxHealth; }
    void GetHealthPercentage();
    void ReceiveDamage(float damage);
    void RepairHouse();

    sf::Text* GetPercentageText() { return percentageText; }

    void ResetHouse();
};

