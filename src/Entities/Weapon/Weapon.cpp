#include "Weapon.h"
#include "../../Program/Program.h"

const int Weapon::totalBullets = 35;

Weapon::Weapon(){}

Weapon::Weapon(float fireRate, float reloadTime, int capacity, float originXPos, float originYPos, sf::Vector2i animationFrameSize, 
	std::string weaponImageFilePath, sf::Vector2i weaponSpriteSheetSize, float bulletMinDamage, float bulletMaxDamage, float bulletSpeed, 
	std::string bulletImageFilePath, sf::Vector2i bulletSpriteSheetSize, float bulletMaxPosX, float bulletMaxPosY)
	: AnimatedEntity(animationFrameSize, weaponImageFilePath, weaponSpriteSheetSize)
{
	this->fireRate = fireRate;
	this->capacity = capacity;
	currentAmmo = this->capacity;
	this->reloadTime = reloadTime;

	for (int i = 0; i < totalBullets; i++)	//35
	{
		bullets.push_back(new Bullet(bulletMinDamage, bulletMaxDamage, bulletSpeed, bulletImageFilePath,
			bulletSpriteSheetSize, bulletMaxPosX, bulletMaxPosY));

		bullets[i]->SetTag(Tag::Bullet);
		CollisionHandler::AddCollision(bullets[i]);
	}

	sf::Vector2f graphicOrigin;
	graphicOrigin.x = originXPos;
	graphicOrigin.y = originYPos;

	sprite.setOrigin(graphicOrigin);

	sf::Vector2f graphicScale = { 3, 3};
	sprite.setScale(graphicScale);

	AnimationData weaponLeft = { 0, 0, 1, false };
	AnimationData weaponRight = { 0, 1 , 1, false };

	AddAnimation("weaponLeft", weaponLeft);
	AddAnimation("weaponRight", weaponRight);	

	SetCurrentAnimation("weaponRight");
		
}

void Weapon::Update(float deltaTime, int hoursSlept)
{
	AnimatedEntity::Update(deltaTime);

	WeaponRotation();
	FireTimer(deltaTime);
	Reload(deltaTime);

	for (int i = 0; i < totalBullets; i++)
	{
		bullets[i]->Update(deltaTime, hoursSlept);
	}
}

void Weapon::Shoot(sf::Vector2i bulletDirection)
{		
	if (fireTimer < fireRate) return;
	if (currentAmmo <= 0) return;
	if (isReloading) return;

	sf::Vector2f bulletTrajectory = sf::Vector2f(bulletDirection) - sprite.getPosition();
	bulletTrajectory = VectorUtility::Normalize(bulletTrajectory);

	currentAmmo--;

	for (int i = 0; i < totalBullets; i++)
	{
		if (!bullets[i]->GetIsActive())
		{
			bullets[i]->Graphic().setPosition(sprite.getPosition());
			bullets[i]->SetBulletTrayectory(bulletTrajectory);
			bullets[i]->SetIsActive(true);

			fireTimer = 0;
			return;
		}
	}

}

void Weapon::ShootUzi(sf::Vector2i bulletDirection)
{	
	if (fireTimer < fireRate) return;
	if (currentAmmo <= 0) return;
	if (isReloading) return;

	sf::Vector2f bulletTrajectory = sf::Vector2f(bulletDirection) - sprite.getPosition();
	bulletTrajectory = VectorUtility::Normalize(bulletTrajectory);

	currentAmmo--;

	for (int i = 0; i < totalBullets; i++)
	{
		if (!bullets[i]->GetIsActive())
		{
			bullets[i]->Graphic().setPosition(sprite.getPosition());
			bullets[i]->SetBulletTrayectory(bulletTrajectory);
			bullets[i]->SetIsActive(true);

			fireTimer -= fireRate;
			return;
		}
	}
}



void Weapon::Reload(float deltaTime)
{
	if (isReloading)
	{
		reloadTimer += deltaTime;

		if (reloadTimer >= reloadTime)
		{
			currentAmmo = capacity;
			isReloading = false;
			reloadTimer = 0;
		}
	}	
}

sf::FloatRect Weapon::GetBounds()
{
	return sprite.getGlobalBounds();
}

void Weapon::WeaponRotation()
{
	sf::Vector2f relativePosition = sf::Vector2f(Program::GetMousePosition()) - sprite.getPosition();
	float angle = atan2(relativePosition.y, relativePosition.x) * 180 / 3.14159f;

	sprite.setRotation(angle);
	
}

void Weapon::FireTimer(float deltaTime)
{
	if (fireTimer < fireRate)
	{
		fireTimer += deltaTime;
	}
}
