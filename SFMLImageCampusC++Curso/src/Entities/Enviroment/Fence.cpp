#include "Fence.h"

int Fence::healthPercentage;
sf::Text* Fence::percentageText;

Fence::Fence(float health, std::string fenceType, sf::Vector2f fencePos, sf::Vector2i animationFrameSize,
	std::string imageFilePath, sf::Vector2i spriteSheetSize)
	: AnimatedEntity(animationFrameSize, imageFilePath, spriteSheetSize)
{
	sprite.setOrigin(sf::Vector2f{ 0, 0 });

	this->fenceType = fenceType;
	maxHealth = health;
	currentHealth = maxHealth;

	AnimationData topLeftCorner = { 0, 0, 1, false };
	AnimationData topSide = { 0, 1, 1, false };
	AnimationData topRightCorner = { 0, 2, 1, false };
	AnimationData rightSide = { 0, 3, 1, false };
	AnimationData leftSide = { 0, 4, 1, false };
	AnimationData bottomLeftCorner = { 0, 5, 1, false };
	AnimationData bottomSide = { 0, 6, 1, false };
	AnimationData bottomRightCorner = { 0, 7, 1, false };

	AnimationData topLeftCornerDamaged = { 0, 9, 1, false };
	AnimationData topSideDamaged = { 0, 10, 1, false };
	AnimationData topRightCornerDamaged = { 0, 11, 1, false };
	AnimationData rightSideDamaged = { 0, 12, 1, false };
	AnimationData leftSideDamaged = { 0, 13, 1, false };
	AnimationData bottomLeftCornerDamaged = { 0, 14, 1, false };
	AnimationData bottomSideDamaged = { 0, 15, 1, false };
	AnimationData bottomRightCornerDamaged = { 0, 16, 1, false };

	AnimationData topLeftCornerBadlyDamaged = { 0, 17, 1, false };
	AnimationData topSideBadlyDamaged = { 0, 18, 1, false };
	AnimationData topRightCornerBadlyDamaged = { 0, 19, 1, false };
	AnimationData rightSideBadlyDamaged = { 0, 20, 1, false };
	AnimationData leftSideBadlyDamaged = { 0, 21, 1, false };
	AnimationData bottomLeftCornerBadlyDamaged = { 0, 22, 1, false };
	AnimationData bottomSideBadlyDamaged = { 0, 23, 1, false };
	AnimationData bottomRightCornerBadlyDamaged = { 0, 24, 1, false };
		
	AnimationData topLeftCornerBroken = { 0, 25, 1, false };
	AnimationData topSideBroken = { 0, 26, 1, false };
	AnimationData topRightCornerBroken = { 0, 27, 1, false };
	AnimationData rightSideBroken = { 0, 28, 1, false };
	AnimationData leftSideBroken = { 0, 29, 1, false };
	AnimationData bottomLeftCornerBroken = { 0, 30, 1, false };
	AnimationData bottomSideBroken = { 0, 31, 1, false };
	AnimationData bottomRightCornerBroken = { 0, 32, 1, false };

	
	AnimationData door = { 0, 8, 1, false };
	AnimationData doorDamaged = { 0, 33, 1, false };
	AnimationData doorBadlyDamaged = { 0, 34, 1, false };
	AnimationData doorBroken = { 0, 35, 1, false };


	AddAnimation("topLeftCorner", topLeftCorner);
	AddAnimation("topSide", topSide);
	AddAnimation("topRightCorner", topRightCorner);
	AddAnimation("rightSide", rightSide);
	AddAnimation("leftSide", leftSide);
	AddAnimation("bottomLeftCorner", bottomLeftCorner);
	AddAnimation("bottomSide", bottomSide);
	AddAnimation("bottomRightCorner", bottomRightCorner);
	AddAnimation("door", door);

	AddAnimation("topLeftCornerDamaged", topLeftCornerDamaged);
	AddAnimation("topSideDamaged", topSideDamaged);
	AddAnimation("topRightCornerDamaged", topRightCornerDamaged);
	AddAnimation("rightSideDamaged", rightSideDamaged);
	AddAnimation("leftSideDamaged", leftSideDamaged);
	AddAnimation("bottomLeftCornerDamaged", bottomLeftCornerDamaged);
	AddAnimation("bottomSideDamaged", bottomSideDamaged);
	AddAnimation("bottomRightCornerDamaged", bottomRightCornerDamaged);
	AddAnimation("doorDamaged", doorDamaged);

	AddAnimation("topLeftCornerBadlyDamaged", topLeftCornerBadlyDamaged);
	AddAnimation("topSideBadlyDamaged", topSideBadlyDamaged);
	AddAnimation("topRightCornerBadlyDamaged", topRightCornerBadlyDamaged);
	AddAnimation("rightSideBadlyDamaged", rightSideBadlyDamaged);
	AddAnimation("leftSideBadlyDamaged", leftSideBadlyDamaged);
	AddAnimation("bottomLeftCornerBadlyDamaged", bottomLeftCornerBadlyDamaged);
	AddAnimation("bottomSideBadlyDamaged", bottomSideBadlyDamaged);
	AddAnimation("bottomRightCornerBadlyDamaged", bottomRightCornerBadlyDamaged);
	AddAnimation("doorBadlyDamaged", doorBadlyDamaged);

	AddAnimation("topLeftCornerBroken", topLeftCornerBroken);
	AddAnimation("topSideBroken", topSideBroken);
	AddAnimation("topRightCornerBroken", topRightCornerBroken);
	AddAnimation("rightSideBroken", rightSideBroken);
	AddAnimation("leftSideBroken", leftSideBroken);
	AddAnimation("bottomLeftCornerBroken", bottomLeftCornerBroken);
	AddAnimation("bottomSideBroken", bottomSideBroken);
	AddAnimation("bottomRightCornerBroken", bottomRightCornerBroken);
	AddAnimation("doorBroken", doorBroken);


	SetCurrentAnimation(fenceType);
	sprite.setPosition(fencePos);	

	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Roboto.ttf";

	font->loadFromFile(fontPath);
	sf::Color* color = new sf::Color(88, 83, 74, 255);

	percentageText = new sf::Text("", *font, 18);

	percentageText->setPosition(480, 410);
	percentageText->setFillColor(*color);
}

void Fence::Update(float deltaTime)
{
	percentageText->setString("Health: " + std::to_string(healthPercentage) + "%				 X% /h");

	FenceAppearance();
}

sf::FloatRect Fence::GetBounds()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();

	if (GetCurrentAnimation() == "topSide" || GetCurrentAnimation() == "topLeftCorner" 
		|| GetCurrentAnimation() == "topRightCorner" || GetCurrentAnimation() == "topSideDamaged" || GetCurrentAnimation() == "topLeftCornerDamaged"
		|| GetCurrentAnimation() == "topRightCornerDamaged" || GetCurrentAnimation() == "topSideBadlyDamaged" 
		|| GetCurrentAnimation() == "topLeftCornerBadlyDamaged" || GetCurrentAnimation() == "topRightCornerBadlyDamaged" 
		|| GetCurrentAnimation() == "topSideBroken" || GetCurrentAnimation() == "topLeftCornerBroken" 
		|| GetCurrentAnimation() == "topRightCornerBroken")
	{
		bounds.height *= 0.5;
	}
	else if (GetCurrentAnimation() == "bottomSide" || GetCurrentAnimation() == "bottomLeftCorner" || 
		GetCurrentAnimation() == "bottomRightCorner" || GetCurrentAnimation() == "bottomSideDamaged" 
		|| GetCurrentAnimation() == "bottomLeftCornerDamaged" || GetCurrentAnimation() == "bottomRightCornerDamaged" 
		|| GetCurrentAnimation() == "bottomSideBadlyDamaged"	|| GetCurrentAnimation() == "bottomLeftCornerBadlyDamaged" 
		|| GetCurrentAnimation() == "bottomRightCornerBadlyDamaged" || GetCurrentAnimation() == "bottomSideBroken"
		|| GetCurrentAnimation() == "bottomLeftCornerBroken" || GetCurrentAnimation() == "bottomRightCornerBroken")
	{
		bounds.top += (bounds.height - (bounds.height * 0.5));
		bounds.height *= 0.5;
	}
	else if (GetCurrentAnimation() == "door" || GetCurrentAnimation() == "doorDamaged" || GetCurrentAnimation() == "doorBadlyDamaged" 
		|| GetCurrentAnimation() == "doorBroken")
	{		
		bounds.top += (bounds.height - (bounds.height * 0.65));
		bounds.height *= 0.5;		
	}

	return bounds;
}

void Fence::FenceAppearance()
{
	if (fenceType == "topLeftCorner")
	{
		if (currentHealth <= 0)
		{
			SetCurrentAnimation("topLeftCornerBroken");
		}
		else if (currentHealth < maxHealth * 0.25f)
		{
			SetCurrentAnimation("topLeftCornerBadlyDamaged");
		}
		else if (currentHealth < maxHealth * 0.5f)
		{
			SetCurrentAnimation("topLeftCornerDamaged");
		}
		else
		{
			SetCurrentAnimation("topLeftCorner");
		}
		
	}
	else if (fenceType == "topSide")
	{
		if (currentHealth <= 0)
		{
			SetCurrentAnimation("topSideBroken");
		}
		else if (currentHealth < maxHealth * 0.25f)
		{
			SetCurrentAnimation("topSideBadlyDamaged");
		}
		else if (currentHealth < maxHealth * 0.5f)
		{
			SetCurrentAnimation("topSideDamaged");
		}
		else
		{
			SetCurrentAnimation("topSide");
		}
	}
	else if (fenceType == "topRightCorner")
	{
		if (currentHealth <= 0)
		{
			SetCurrentAnimation("topRightCornerBroken");
		}
		else if (currentHealth < maxHealth * 0.25f)
		{
			SetCurrentAnimation("topRightCornerBadlyDamaged");
		}
		else if (currentHealth < maxHealth * 0.5f)
		{
			SetCurrentAnimation("topRightCornerDamaged");
		}
		else
		{
			SetCurrentAnimation("topRightCorner");
		}

	}
	else if (fenceType == "leftSide")
	{
		if (currentHealth <= 0)
		{
			SetCurrentAnimation("leftSideBroken");
		}
		else if (currentHealth < maxHealth * 0.25f)
		{
			SetCurrentAnimation("leftSideBadlyDamaged");
		}
		else if (currentHealth < maxHealth * 0.5f)
		{
			SetCurrentAnimation("leftSideDamaged");
		}
		else
		{
			SetCurrentAnimation("leftSide");
		}
	}
	else if (fenceType == "rightSide")
	{
		if (currentHealth <= 0)
		{
			SetCurrentAnimation("rightSideBroken");
		}
		else if (currentHealth < maxHealth * 0.25f)
		{
			SetCurrentAnimation("rightSideBadlyDamaged");
		}
		else if (currentHealth < maxHealth * 0.5f)
		{
			SetCurrentAnimation("rightSideDamaged");
		}
		else
		{
			SetCurrentAnimation("rightSide");
		}
	}
	else if (fenceType == "bottomLeftCorner")
	{
		if (currentHealth <= 0)
		{
			SetCurrentAnimation("bottomLeftCornerBroken");
		}
		else if (currentHealth < maxHealth * 0.25f)
		{
			SetCurrentAnimation("bottomLeftCornerBadlyDamaged");
		}
		else if (currentHealth < maxHealth * 0.5f)
		{
			SetCurrentAnimation("bottomLeftCornerDamaged");
		}
		else
		{
			SetCurrentAnimation("bottomLeftCorner");
		}
	}
	else if (fenceType == "bottomSide")
	{
		if (currentHealth <= 0)
		{
			SetCurrentAnimation("bottomSideBroken");
		}
		else if (currentHealth < maxHealth * 0.25f)
		{
			SetCurrentAnimation("bottomSideBadlyDamaged");
		}
		else if (currentHealth < maxHealth * 0.5f)
		{
			SetCurrentAnimation("bottomSideDamaged");
		}
		else
		{
			SetCurrentAnimation("bottomSide");
		}
	}
	else if (fenceType == "bottomRightCorner")
	{
		if (currentHealth <= 0)
		{
			SetCurrentAnimation("bottomRightCornerBroken");
		}
		else if (currentHealth < maxHealth * 0.25f)
		{
			SetCurrentAnimation("bottomRightCornerBadlyDamaged");
		}
		else if (currentHealth < maxHealth * 0.5f)
		{
			SetCurrentAnimation("bottomRightCornerDamaged");
		}
		else
		{
			SetCurrentAnimation("bottomRightCorner");
		}
	}
	else if (fenceType == "door")
	{
		if (currentHealth <= 0)
		{
			SetCurrentAnimation("doorBroken");
		}
		else if (currentHealth < maxHealth * 0.25f)
		{
			SetCurrentAnimation("doorBadlyDamaged");
		}
		else if (currentHealth < maxHealth * 0.5f)
		{
			SetCurrentAnimation("doorDamaged");
		}
		else
		{
			SetCurrentAnimation("door");
		}
	}


}

void Fence::ReceiveDamage(float damage)
{
	currentHealth -= damage;

	if (currentHealth <= 0)
		isFenceBroken = true;

}

void Fence::GetHealthPercentage(std::vector<Fence*> fences)
{
	int fencesMaxHealth = 0;
	int fencesCurrentHealth = 0;

	for (int i = 0; i < fences.size(); i++)
	{
		fencesMaxHealth += fences[i]->GetMaxHealth();
		fencesCurrentHealth += fences[i]->GetHealth();
	}

	healthPercentage = (fencesCurrentHealth * 100) / fencesMaxHealth;	

}

void Fence::ResetFence()
{
	currentHealth = maxHealth;
	isFenceBroken = false;
}





