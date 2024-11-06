#pragma once
#include "../Entity.h"
class Bullet : public Entity
{
private:
	bool isActive;
	float minDamage;
	float maxDamage;
	float damage;
	float damageMod;
	float speed;
	float maxPosX;
	float maxPosY;
	sf::Vector2f bulletTrayectory;
	void CheckBounds();
	void AimMod(int hoursSlept);


public:
	Bullet();
	Bullet(float minDamage, float maxDamage, float speed, std::string imageFilePath, 
		sf::Vector2i spriteSheetSize, float maxPosX, float maxPosY);
	void Update(float deltaTime, int hoursSlept);
	void SetBulletTrayectory(sf::Vector2f bulletTrayectory);
	void SetIsActive(bool isActive);
	bool GetIsActive() { return isActive; }
	float GetDamage();
	sf::FloatRect GetBounds() override;
};

