#include "AmmoHolder.h"

AmmoHolder::AmmoHolder(sf::Vector2i animationFrameSize, std::string imageFilePath, sf::Vector2i spriteSheetSize) :
	AnimatedEntity(animationFrameSize, imageFilePath, spriteSheetSize)
{
	AnimationData ammoSeven{ 0, 0, 1, false };
	AnimationData ammoSix{ 0, 1, 1, false };
	AnimationData ammoFive{ 0, 2, 1, false };
	AnimationData ammoFour{ 0, 3, 1, false };
	AnimationData ammoThree{ 0, 4, 1, false };
	AnimationData ammoTwo{ 0, 5, 1, false };
	AnimationData ammoOne{ 0, 6, 1, false };
	AnimationData ammoEmpty{ 0, 7, 1, false };

	AddAnimation("ammoSeven", ammoSeven);
	AddAnimation("ammoSix", ammoSix);
	AddAnimation("ammoFive", ammoFive);
	AddAnimation("ammoFour", ammoFour);
	AddAnimation("ammoThree", ammoThree);
	AddAnimation("ammoTwo", ammoTwo);
	AddAnimation("ammoOne", ammoOne);
	AddAnimation("ammoEmpty", ammoEmpty);
		
	sprite.setPosition(115, 848);
	//sprite.setPosition(50, 30);


}

void AmmoHolder::Update(int currentAmmo, float deltaTime)
{
	AnimatedEntity::Update(deltaTime);

	if (currentAmmo == 7)
	{
		SetCurrentAnimation("ammoSeven");
	}
	else if (currentAmmo == 6)
	{
		SetCurrentAnimation("ammoSix");
	}
	else if (currentAmmo == 5)
	{
		SetCurrentAnimation("ammoFive");
	}
	else if (currentAmmo == 4)
	{
		SetCurrentAnimation("ammoFour");
	}
	else if (currentAmmo == 3)
	{
		SetCurrentAnimation("ammoThree");
	}
	else if (currentAmmo == 2)
	{
		SetCurrentAnimation("ammoTwo");
	}
	else if (currentAmmo == 1)
	{
		SetCurrentAnimation("ammoOne");
	}
	else if (currentAmmo <= 0)
	{
		SetCurrentAnimation("ammoEmpty");
	}
}