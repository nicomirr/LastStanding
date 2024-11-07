#include "HUD.h"


HUD::HUD(sf::Vector2i animationFrameSize, std::string imageFilePath, sf::Vector2i spriteSheetSize)
	: AnimatedEntity(animationFrameSize, imageFilePath, spriteSheetSize)
{
	AnimationData hudWithGun = { 0, 0, 1, false };
	AnimationData hudWithShotgun = { 0, 1, 1, false };
	AnimationData hudWithUzi = { 0, 2, 1, false };

	AddAnimation("hudWithGun", hudWithGun);
	AddAnimation("hudWithShotgun", hudWithShotgun);
	AddAnimation("hudWithUzi", hudWithUzi);

	SetCurrentAnimation("hudWithGun");

	sf::Vector2i gunAmmoHolderAnimationFrameSize = { 60, 18 };
	std::string gunAmmoHolderImageFilePath = "res\\textures\\HUD\\AmmoHolder.png";
	sf::Vector2i gunAmmoHolderSpriteSheetSize = { 60, 144 };

	gunAmmoHolder = new AmmoHolder(gunAmmoHolderAnimationFrameSize, gunAmmoHolderImageFilePath, gunAmmoHolderSpriteSheetSize);

	sf::Vector2i shotgunAmmoHolderAnimationFrameSize = { 33, 18 };
	std::string shotgunAmmoHolderImageFilePath = "res\\textures\\HUD\\AmmoHolder.png";
	sf::Vector2i shotgunAmmoHolderSpriteSheetSize = { 33, 144 };

	shotgunAmmoHolder = new AmmoHolder(shotgunAmmoHolderAnimationFrameSize, shotgunAmmoHolderImageFilePath, shotgunAmmoHolderSpriteSheetSize);

	sprite.setPosition(0, 805);

	sf::Vector2i uziAmmoHolderAnimationFrameSize = { 58, 17 };
	std::string uziAmmoHolderImageFilePath = "res\\textures\\HUD\\UziAmmoHolder.png";
	sf::Vector2i uziAmmoHolderSpriteSheetSize = { 58, 357 };

	uziAmmoHolder = new AmmoHolder(uziAmmoHolderAnimationFrameSize, uziAmmoHolderImageFilePath, uziAmmoHolderSpriteSheetSize);

	sprite.setPosition(0, 805);


	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Pixel.otf";

	font->loadFromFile(fontPath);

	sf::Color color = sf::Color(88, 83, 74, 255);

	std::string text = "Ammo";
	ammoText = new sf::Text(text, *font, 12);
	ammoText->setPosition(49, 852);
	ammoText->setFillColor(color);



}

void HUD::Update(int resources, int currentAmmo, float deltaTime, Weapon weapon)
{
	AnimatedEntity::Update(deltaTime);

	HUDAppearance();

	if (weapon.GetTag() == Tag::Gun)
		gunAmmoHolder->Update(weapon, currentAmmo, deltaTime);
	else if (weapon.GetTag() == Tag::Shotgun)
		shotgunAmmoHolder->Update(weapon, currentAmmo, deltaTime);
	else
		uziAmmoHolder->Update(weapon, currentAmmo, deltaTime);
}

void HUD::HUDAppearance()
{
	if (Player::GetHasUzi())
	{
		SetCurrentAnimation("hudWithUzi");
	}
	else if (Player::GetHasShotgun())
	{
		SetCurrentAnimation("hudWithShotgun");
	}
	else
		SetCurrentAnimation("hudWithGun");
	
}


