#pragma once
#include "../Entity.h"
class Bullet : public Entity
{
private:
	bool isActive;
	float minDamage;
	float maxDamage;
	float damage;
	float speed;
	float maxPosX;
	float maxPosY;
	sf::Vector2f bulletTrayectory;
	void CheckBounds();

public:
	Bullet();
	Bullet(float minDamage, float maxDamage, float speed, std::string imageFilePath, 
		sf::Vector2i spriteSheetSize, float maxPosX, float maxPosY);
	void Update(float deltaTime);
	void SetBulletTrayectory(sf::Vector2f bulletTrayectory);
	void SetIsActive(bool isActive);
	bool GetIsActive() { return isActive; }
	float GetDamage();
	sf::FloatRect GetBounds() override;
};

