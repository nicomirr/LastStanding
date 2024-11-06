#pragma once
#include "SFML/System.hpp"
#include "../../Utilities/VectorUtility.h"
#include "../AnimatedEntity.h"
#include "Bullet.h"

class Weapon : public AnimatedEntity
{
private:
	bool isActive;
	int capacity;
	int currentAmmo;
	float fireRate;
	float fireTimer;
	float reloadTime;
	float reloadTimer;
	bool isReloading;
	std::vector<Bullet*> bullets;
	void WeaponRotation();
	void FireTimer(float deltaTime);
	void Reload(float deltaTime);

public:
	Weapon();
	Weapon(float fireRate, float reloadTime, int capacity, float originXPos, float originYPos, sf::Vector2i animationFrameSize,
		std::string weaponImageFilePath, sf::Vector2i weaponSpriteSheetSize,float bulletMinDamage, 
		float bulletMaxDamage, float bulletSpeed, std::string bulletImageFilePath, 
		sf::Vector2i bulletSpriteSheetSize,	float bulletMaxPosX, float bulletMaxPosY);
	void Update(float deltaTime, int hoursSlept);
	std::vector<Bullet*> GetBullets() { return bullets; }
	sf::FloatRect GetBounds() override;
	void Shoot(sf::Vector2i bulletDirection);
	void ShootUzi(sf::Vector2i bulletDirection);
	bool GetIsReloading() { return isReloading; }
	void SetIsReloading(bool value) { isReloading = value; }
	int GetCurrentAmmo() { return currentAmmo; }

};

