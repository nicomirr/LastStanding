#include "Car.h"

bool Car::isDestroyed;
float Car::currentHealth;

Car::Car() {}

Car::Car(sf::Vector2f pos, sf::Vector2i animationFrameSize, std::string imageFilePath, sf::Vector2i spriteSheetSize)
	: AnimatedEntity(animationFrameSize, imageFilePath, spriteSheetSize)
{
	collissionRadius = 60;

	AnimationData carFullHealth = { 0, 0, 1, false };
	AnimationData carHalfHealth = { 0, 1, 1, false };
	AnimationData carBroken = { 0, 2, 1, false };

	AddAnimation("carFullHealth", carFullHealth);
	AddAnimation("carHalfHealth", carHalfHealth);
	AddAnimation("carBroken", carBroken);

	SetCurrentAnimation("carFullHealth");

	sf::Vector2i healthBarAnimationFrameSize = { 59, 8 };
	std::string healthBarImageFilePath = "res\\textures\\healthbar\\CarHealthBar.png";
	sf::Vector2i healthBarSpriteSheetSize = { 59, 48 };
	
	maxHealth = 200;
	currentHealth = maxHealth;

	healthBar = new HealthBar(currentHealth, healthBarAnimationFrameSize, healthBarImageFilePath, healthBarSpriteSheetSize);

	AnimationData emptyBar = { 0, 0, 1 , false };
	AnimationData oneSixthBar = { 0, 1, 1 , false };
	AnimationData twoSixhtBar = { 0, 2, 1 , false };
	AnimationData threeSixthBar = { 0, 3, 1 , false };
	AnimationData fourSixthBar = { 0, 4, 1 , false };
	AnimationData fullBar = { 0, 5, 1 , false };

	healthBar->AddAnimation("emptyBar", emptyBar);
	healthBar->AddAnimation("oneSixthBar", oneSixthBar);
	healthBar->AddAnimation("twoSixthBar", twoSixhtBar);
	healthBar->AddAnimation("threeSixthBar", threeSixthBar);
	healthBar->AddAnimation("fourSixthBar", fourSixthBar);
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

void Car::Update(float deltaTime)
{
	percentageText->setString("Health: " + std::to_string(healthPercentage) + "%				10% /h");

	float yOffset = 20;
	float xOffset = -5;

	CarAppearance();

	healthBar->Update(deltaTime, sprite.getPosition(), yOffset, xOffset, currentHealth);
	HealthBarAppearance();
}

sf::FloatRect Car::GetBounds()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();

	bounds.top -= (bounds.height - (bounds.height * 1.05));
	bounds.height *= 0.75;

	return bounds;
}

void Car::RepairCar()
{
	currentHealth += (maxHealth * 0.1f);
	currentHealth = std::clamp(currentHealth, 0.0f, maxHealth);
}

void Car::ReceiveDamage(float damage)
{
	currentHealth -= damage;

	if (currentHealth < 0)
		currentHealth = 0;
}

void Car::GetHealthPercentage()
{
	healthPercentage = (currentHealth * 100) / maxHealth;
}

void Car::CarAppearance()
{
	if (currentHealth <= 0)
	{
		SetCurrentAnimation("carBroken");

	}
	else if (currentHealth <= maxHealth * 0.5f)
	{
		SetCurrentAnimation("carHalfHealth");
	}
	else
	{
		SetCurrentAnimation("carFullHealth");
	}
}

void Car::HealthBarAppearance()
{
	if (healthBar->GetCurrentHealth() <= 0)
	{
		healthBar->SetCurrentAnimation("emptyBar");
	}
	else if (healthBar->GetCurrentHealth() <= healthBar->GetMaxHealth() * 0.2f)
	{
		healthBar->SetCurrentAnimation("oneSixthBar");
	}
	else if (healthBar->GetCurrentHealth() <= healthBar->GetMaxHealth() * 0.4f)
	{
		healthBar->SetCurrentAnimation("twoSixthBar");
	}
	else if (healthBar->GetCurrentHealth() <= healthBar->GetMaxHealth() * 0.6f)
	{
		healthBar->SetCurrentAnimation("threeSixthBar");
	}
	else if (healthBar->GetCurrentHealth() <= healthBar->GetMaxHealth() * 0.8f)
	{
		healthBar->SetCurrentAnimation("fourSixthBar");
	}
	else
	{
		healthBar->SetCurrentAnimation("fullBar");
	}
	
}

void Car::ResetCar()
{
	currentHealth = maxHealth;
	isDestroyed = false;
}

//ESTADO DE AUTO DEBE AFECTAR BUSQUEDA