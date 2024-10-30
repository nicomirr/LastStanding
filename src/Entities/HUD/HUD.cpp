#include "HUD.h"

HUD::HUD(std::string imageFilePath, sf::Vector2i spriteSheetSize) : Entity(imageFilePath, spriteSheetSize)
{
	sf::Vector2i ammoHolderAnimationFrameSize = { 60, 18 };
	std::string ammoHolderImageFilePath = "res\\textures\\HUD\\AmmoHolder.png";
	sf::Vector2i ammoHolderSpriteSheetSize = { 60, 144 };

	ammoHolder = new AmmoHolder(ammoHolderAnimationFrameSize, ammoHolderImageFilePath, ammoHolderSpriteSheetSize);

	sprite.setPosition(0, 753);

	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Pixel.otf";

	font->loadFromFile(fontPath);

	sf::Color* color = new sf::Color(88, 83, 74, 255);

	std::string text = "Ammo";
	ammoText = new sf::Text(text, *font, 12);
	ammoText->setPosition(49, 852);
	ammoText->setFillColor(*color);

}

void HUD::Update(int currentAmmo, float deltaTime)
{
	ammoHolder->Update(currentAmmo, deltaTime);
}

