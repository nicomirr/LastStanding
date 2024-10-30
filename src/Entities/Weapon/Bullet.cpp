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

void Bullet::Update(float deltaTime)
{
	if (!isActive) return;

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
		return damage;
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
