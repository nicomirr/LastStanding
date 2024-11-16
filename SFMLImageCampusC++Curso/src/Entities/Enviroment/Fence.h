#pragma once
#include "../AnimatedEntity.h"
#include <iomanip>
#include <sstream>

class Fence :
    public AnimatedEntity
{
private:
    static int healthPercentage;

    sf::Font* font;
    static sf::Text* percentageText;

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
   
    float GetHealth() { return currentHealth; }
    float GetMaxHealth() { return maxHealth; }
    
    void ReceiveDamage(float damage);
    void RepairFence() { currentHealth = maxHealth; }

    static void GetHealthPercentage(std::vector<Fence*> fences);
    static sf::Text* GetPercentageText() { return percentageText; }

    void ResetFence();

    void Destroy();
};
