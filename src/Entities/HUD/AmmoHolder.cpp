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

	AnimationData uziAmmoTwenty{ 0, 0, 1, false };
	AnimationData uziAmmoNineteen{ 0, 1, 1, false };
	AnimationData uziAmmoEighteen{ 0, 2, 1, false };
	AnimationData uziAmmoSeventeen{ 0, 3, 1, false };
	AnimationData uziAmmoSixteen{ 0, 4, 1, false };
	AnimationData uziAmmoFifteen{ 0, 5, 1, false };
	AnimationData uziAmmoFourteen{ 0, 6, 1, false };
	AnimationData uziAmmoThirdteen{ 0, 7, 1, false };
	AnimationData uziAmmoTwelve{ 0, 8, 1, false };
	AnimationData uziAmmoEleven{ 0, 9, 1, false };
	AnimationData uziAmmoTen{ 0, 10, 1, false };
	AnimationData uziAmmoNine{ 0, 11, 1, false };
	AnimationData uziAmmoEight{ 0, 12, 1, false };
	AnimationData uziAmmoSeven{ 0, 13, 1, false };
	AnimationData uziAmmoSix{ 0, 14, 1, false };
	AnimationData uziAmmoFive{ 0, 15, 1, false };
	AnimationData uziAmmoFour{ 0, 16, 1, false };
	AnimationData uziAmmoThree{ 0, 17, 1, false };
	AnimationData uziAmmoTwo{ 0, 18, 1, false };
	AnimationData uziAmmoOne{ 0, 19, 1, false };
	AnimationData uziAmmoEmpty{ 0, 20, 1, false };

	AddAnimation("ammoSeven", ammoSeven);
	AddAnimation("ammoSix", ammoSix);
	AddAnimation("ammoFive", ammoFive);
	AddAnimation("ammoFour", ammoFour);
	AddAnimation("ammoThree", ammoThree);
	AddAnimation("ammoTwo", ammoTwo);
	AddAnimation("ammoOne", ammoOne);
	AddAnimation("ammoEmpty", ammoEmpty);

	AddAnimation("uziAmmoTwenty", uziAmmoTwenty);
	AddAnimation("uziAmmoNineteen", uziAmmoNineteen);
	AddAnimation("uziAmmoEighteen", uziAmmoEighteen);
	AddAnimation("uziAmmoSeventeen", uziAmmoSeventeen);
	AddAnimation("uziAmmoSixteen", uziAmmoSixteen);
	AddAnimation("uziAmmoFifteen", uziAmmoFifteen);
	AddAnimation("uziAmmoFourteen", uziAmmoFourteen);
	AddAnimation("uziAmmoThirdteen", uziAmmoThirdteen);
	AddAnimation("uziAmmoTwelve", uziAmmoTwelve);
	AddAnimation("uziAmmoEleven", uziAmmoEleven);
	AddAnimation("uziAmmoTen", uziAmmoTen);
	AddAnimation("uziAmmoNine", uziAmmoNine);
	AddAnimation("uziAmmoEight", uziAmmoEight);
	AddAnimation("uziAmmoSeven", uziAmmoSeven);
	AddAnimation("uziAmmoSix", uziAmmoSix);
	AddAnimation("uziAmmoFive", uziAmmoFive);
	AddAnimation("uziAmmoFour", uziAmmoFour);
	AddAnimation("uziAmmoThree", uziAmmoThree);
	AddAnimation("uziAmmoTwo", uziAmmoTwo);
	AddAnimation("uziAmmoOne", uziAmmoOne);
	AddAnimation("uziAmmoEmpty", uziAmmoEmpty);
		
	sprite.setPosition(115, 848);
	//sprite.setPosition(50, 30);


}

void AmmoHolder::Update(Weapon weapon, int currentAmmo, float deltaTime)
{
	AnimatedEntity::Update(deltaTime);
	
	if (weapon.GetTag() != Tag::Uzi)
	{
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
	else
	{
		if (currentAmmo == 20)
		{
			SetCurrentAnimation("uziAmmoTwenty");
		}
		else if (currentAmmo == 19)
		{
			SetCurrentAnimation("uziAmmoNineteen");
		}
		else if (currentAmmo == 18)
		{
			SetCurrentAnimation("uziAmmoEighteen");
		}
		else if (currentAmmo == 17)
		{
			SetCurrentAnimation("uziAmmoSeventeen");
		}
		else if (currentAmmo == 16)
		{
			SetCurrentAnimation("uziAmmoSixteen");
		}
		else if (currentAmmo == 15)
		{
			SetCurrentAnimation("uziAmmoFifteen");
		}
		else if (currentAmmo == 14)
		{
			SetCurrentAnimation("uziAmmoFourteen");
		}
		else if (currentAmmo == 13)
		{
			SetCurrentAnimation("uziAmmoThirdteen");
		}
		else if (currentAmmo == 12)
		{
			SetCurrentAnimation("uziAmmoTwelve");
		}
		else if (currentAmmo == 11)
		{
			SetCurrentAnimation("uziAmmoEleven");
		}
		else if (currentAmmo == 10)
		{
			SetCurrentAnimation("uziAmmoTen");
		}
		else if (currentAmmo == 9)
		{
			SetCurrentAnimation("uziAmmoNine");
		}
		else if (currentAmmo == 8)
		{
			SetCurrentAnimation("uziAmmoEight");
		}
		else if (currentAmmo == 7)
		{
			SetCurrentAnimation("uziAmmoSeven");
		}
		else if (currentAmmo == 6)
		{
			SetCurrentAnimation("uziAmmoSix");
		}
		else if (currentAmmo == 5)
		{
			SetCurrentAnimation("uziAmmoFive");
		}
		else if (currentAmmo == 4)
		{
			SetCurrentAnimation("uziAmmoFour");
		}
		else if (currentAmmo == 3)
		{
			SetCurrentAnimation("uziAmmoThree");
		}
		else if (currentAmmo == 2)
		{
			SetCurrentAnimation("uziAmmoTwo");
		}
		else if (currentAmmo == 1)
		{
			SetCurrentAnimation("uziAmmoOne");
		}
		else if (currentAmmo <= 0)
		{
			SetCurrentAnimation("uziAmmoEmpty");
		}
	}

}