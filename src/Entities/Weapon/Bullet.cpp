#include "Bullet.h"

Bullet::Bullet(){}

Bullet::Bullet(float minDamage, float maxDamage, float speed, std::string imageFilePath, sf::Vector2i spriteSheetSize, 
	float maxPosX,	float maxPosY)
	: Entity(imageFilePath, spriteSheetSize)
{
	isActive = false;

	this->minDamage = minDamage;
	this->maxDamage = maxDamage;

	this->speed = speed;

	this->maxPosX = maxPosX;
	this->maxPosY = maxPosY;
}

void Bullet::Update(float deltaTime, int hoursSlept)
{
	if (!isActive) return;

	AimMod(hoursSlept);

	sprite.setPosition(sprite.getPosition() + bulletTrayectory * speed * deltaTime);
	CheckBounds();
}

void Bullet::SetBulletTrayectory(sf::Vector2f bulletTrayectory)
{
	this->bulletTrayectory = bulletTrayectory;
}

void Bullet::SetIsActive(bool isActive)
{
	this->isActive = isActive;
}

sf::FloatRect Bullet::GetBounds()
{
	return sprite.getGlobalBounds();
}

float Bullet::GetDamage()
{
	if (isActive)
	{
		damage = RandomNum::RandomRange(minDamage, maxDamage);
		return damage * damageMod;
	}
	else
		return 0;
}

void Bullet::CheckBounds()
{
	if ((sprite.getPosition().x < 0 || sprite.getPosition().x > maxPosX) ||
		(sprite.getPosition().y < 0 || sprite.getPosition().y > maxPosY))
		isActive = false;
}

void Bullet::AimMod(int hoursSlept)
{
	damageMod = 1;
	int random;

	if (hoursSlept == 5)
	{
		random = RandomNum::RandomRange(1, 10);
		if (random == 10)
			damageMod = 0;
	}
	else if (hoursSlept == 4)
	{
		random = RandomNum::RandomRange(1, 12);
		if (random > 9)
			damageMod = 0;
	}
	else if (hoursSlept == 3)
	{
		random = RandomNum::RandomRange(1, 11);
		if (random > 6)
			damageMod = 0;
	}
	else if (hoursSlept == 2)
	{
		random = RandomNum::RandomRange(1, 10);
		if (random > 4)
			damageMod = 0;
	}
	else if (hoursSlept == 1)
	{
		random = RandomNum::RandomRange(1, 12);
		if (random > 3)
			damageMod = 0;
	}
	else if (hoursSlept == 0)
	{
		random = RandomNum::RandomRange(1, 10);
		if (random > 1)
			damageMod = 0;
	}
}
