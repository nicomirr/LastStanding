#include "House.h"

House::House(){}

House::House(sf::Vector2f pos, sf::Vector2i animationFrameSize, std::string imageFilePath, sf::Vector2i spriteSheetSize) :
	AnimatedEntity(animationFrameSize, imageFilePath, spriteSheetSize)
{	
	AnimationData houseFullHealth = { 0, 0, 1, false };
	AnimationData houseHalfHealth = { 0, 1, 1, false };
	AnimationData houseDestroyed = { 0, 2, 1, false };

	AddAnimation("houseFullHealth", houseFullHealth);
	AddAnimation("houseHalfHealth", houseHalfHealth);
	AddAnimation("houseDestroyed", houseDestroyed);

	SetCurrentAnimation("houseFullHealth");

	sf::Vector2i healthBarAnimationFrameSize = { 71, 8 };
	std::string healthBarImageFilePath = "res\\textures\\healthbar\\HouseHealthBar.png";
	sf::Vector2i healthBarSpriteSheetSize = { 71, 56 };

	maxHealth = 250;
	currentHealth = maxHealth;

	healthBar = new HealthBar(currentHealth, healthBarAnimationFrameSize, healthBarImageFilePath, healthBarSpriteSheetSize);

	AnimationData emptyBar = { 0, 0, 1 , false };
	AnimationData oneSixthBar = { 0, 1, 1 , false };
	AnimationData twoSixhtBar = { 0, 2, 1 , false };
	AnimationData threeSixthBar = { 0, 3, 1 , false };
	AnimationData fourSixthBar = { 0, 4, 1 , false };
	AnimationData fiveSixthBar = { 0, 5, 1 , false };
	AnimationData fullBar = { 0, 6, 1 , false };

	healthBar->AddAnimation("emptyBar", emptyBar);
	healthBar->AddAnimation("oneSixthBar", oneSixthBar);
	healthBar->AddAnimation("twoSixthBar", twoSixhtBar);
	healthBar->AddAnimation("threeSixthBar", threeSixthBar);
	healthBar->AddAnimation("fourSixthBar", fourSixthBar);
	healthBar->AddAnimation("fiveSixthBar", fiveSixthBar);
	healthBar->AddAnimation("fullBar", fullBar);

	healthBar->SetCurrentAnimation("fullBar");
	healthBar->Graphic().scale({ 1.4f,1.4f });

	sprite.setPosition(pos);

	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Roboto.ttf";

	font->loadFromFile(fontPath);

	sf::Color* color = new sf::Color(88, 83, 74, 255);

	percentageText = new sf::Text("", *font, 18);

	percentageText->setPosition(480, 410);
	percentageText->setFillColor(*color);
}

void House::Update(float deltaTime)
{	
	percentageText->setString("Health: " + std::to_string(healthPercentage) + "%				10% /h");

	HouseAppearance();

	float yOffset = 0;
	float xOffset = 70;

	healthBar->Update(deltaTime, sprite.getPosition(), yOffset, xOffset, currentHealth);
	HealthBarAppearance();
}

sf::FloatRect House::GetBounds()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();

	bounds.top -= (bounds.height - (bounds.height * 1.3));
	bounds.height *= 0.5;

	return bounds;
}

void House::ReceiveDamage(float damage)
{
	currentHealth -= damage;

	if (currentHealth < 0)
		currentHealth = 0;
}

void House::RepairHouse()
{
	currentHealth += (maxHealth * 0.1f);
	currentHealth = std::clamp(currentHealth, 0.0f, maxHealth);
}

void House::GetHealthPercentage() 
{
	healthPercentage = (currentHealth * 100) / maxHealth;	
}

void House::HouseAppearance()
{
	if (currentHealth <= 0)
	{
		SetCurrentAnimation("houseDestroyed");

	}
	else if (currentHealth <= maxHealth * 0.5f)
	{
		SetCurrentAnimation("houseHalfHealth");
	}
	else
	{
		SetCurrentAnimation("houseFullHealth");
	}
}

void House::HealthBarAppearance()
{
	if (healthBar->GetCurrentHealth() <= 0)
	{
		healthBar->SetCurrentAnimation("emptyBar");
	}
	else if (healthBar->GetCurrentHealth() <= healthBar->GetMaxHealth() * 0.16f)
	{
		healthBar->SetCurrentAnimation("oneSixthBar");
	}
	else if (healthBar->GetCurrentHealth() <= healthBar->GetMaxHealth() * 0.32f)
	{
		healthBar->SetCurrentAnimation("twoSixthBar");
	}
	else if (healthBar->GetCurrentHealth() <= healthBar->GetMaxHealth() * 0.48f)
	{
		healthBar->SetCurrentAnimation("threeSixthBar");
	}
	else if (healthBar->GetCurrentHealth() <= healthBar->GetMaxHealth() * 0.64f)
	{
		healthBar->SetCurrentAnimation("fourSixthBar");
	}
	else if (healthBar->GetCurrentHealth() <= healthBar->GetMaxHealth() * 0.80f)
	{
		healthBar->SetCurrentAnimation("fiveSixthBar");
	}
	else
	{
		healthBar->SetCurrentAnimation("fullBar");
	}
	
}
