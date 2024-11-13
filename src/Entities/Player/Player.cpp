#include "Player.h"
#include "../../Program/Program.h"

int Player::resources;
int Player::hoursSlept;
bool Player::hasShotgun;
bool Player::hasUzi;
bool Player::isAlive;

int Player::score = 2000;

Player::Player(float speed, Weapon* gun, Weapon* shotgun, Weapon* uzi, float windowWidth, float windowHeight, sf::Vector2i animationFrameSize,
	std::string imageFilePath,	sf::Vector2i spriteSheetSize)
	: AnimatedEntity(animationFrameSize, imageFilePath, spriteSheetSize)
{	
	resources = 150;

	hoursSlept = 6;

	isAlive = true;

	this->speed = speed;

	weapons.push_back(gun);
	weapons.push_back(shotgun);
	weapons.push_back(uzi);
	
	canShoot = true;

	hasShotgun = false;
	hasUzi = false;

	currentWeapon = 0;

	sf::Vector2f graphicOrigin;
	graphicOrigin.x =  0;
	graphicOrigin.y = 0;

	sprite.setOrigin(graphicOrigin);
		
	sf::Vector2f graphicScale = { 3, 3};
	sprite.setScale(graphicScale);

	AnimationData idleRight = { 0, 0, 1, false };
	AnimationData idleLeft = { 0, 1, 1, false };
	
	AnimationData walkRight = { 10, 2, 2, true };
	AnimationData walkLeft = { 10, 3, 2, true };

	AnimationData dieRight = { 1, 4, 3, false };
	AnimationData dieLeft = { 1, 5, 3, false };


	AddAnimation("idleRight", idleRight);
	AddAnimation("idleLeft", idleLeft);

	AddAnimation("walkRight", walkRight);
	AddAnimation("walkLeft", walkLeft);

	AddAnimation("dieRight", dieRight);
	AddAnimation("dieLeft", dieLeft);

	SetCurrentAnimation("idleRight");
	currentPos = sf::Vector2f{ 720,windowWidth / 2 - 100};
	//currentPos = sf::Vector2f{ 720,150 };


	std::string eButtonFilePath = "res\\textures\\player\\EButton.png";
	sf::Vector2i eButtonSpriteSheetSize = { 14, 14 };

	eButton = new Entity(eButtonFilePath, eButtonSpriteSheetSize);	
	

	eButton->Graphic().scale(sf::Vector2f(1.6f, 1.6f));
	
}

void Player::Input(sf::Event event)
{	
	if (!isAlive) return;
	if (HoursInterface::GetIsOpen()) return;
	if (SceneManager::GetIsTransitioning()) return;
	if (DayTasksManager::GetScavengeResultsOpen()) return;
	if (PopUpWindow::GetPopUpWindowOpen()) return;

	Movement();
	LookDirection();

	if (GetCurrentWeapon().GetTag() != Tag::Uzi)
		FireWeapon(event);
	

	SwitchWeapons();
}

void Player::Update(float deltaTime)
{			
	/*std::cout << sprite.getPosition().x << std::endl;
	std::cout << sprite.getPosition().y << std::endl;*/
		
	if (!SceneManager::GetIsTransitioning())
	{
		if(!HoursInterface::GetIsOpen())
			AnimatedEntity::Update(deltaTime);
	}

	if (SceneManager::GetIsTransitioning())
	{
		direction = { 0, 0 };
	}

	EButtonOff();

	sf::Vector2f eButtonOffset = { 10, -25 };
	eButton->Graphic().setPosition(sprite.getPosition() + eButtonOffset);

	if (isAlive)
	{		
		if (!PopUpWindow::GetPopUpWindowOpen())
		{
			if (!HoursInterface::GetIsOpen())
			{
				if (!SceneManager::GetIsTransitioning() && !DayTasksManager::GetScavengeResultsOpen())
				{
					if (GetCurrentWeapon().GetTag() == Tag::Uzi)
						FireUzi();
				}

				if (!DayTasksManager::GetScavengeResultsOpen())
				{
					if (SceneManager::GetIsTransitionToDay())
					{
						sprite.setPosition({ 461, 346 });
						currentPos = { 461, 346 };
						SceneManager::SetIsTransitionToDay(false);

					}
					else if (SceneManager::GetIsTransitionToInside())
					{
						sprite.setPosition({ 660, 511 });
						currentPos = { 660, 511 };
						SceneManager::SetIsTransitionToInside(false);
					}
					else if (SceneManager::GetIsTransitionToOutside())
					{
						sprite.setPosition({ 717, 413 });
						currentPos = { 717, 413 };
						SceneManager::SetIsTransitionToOutside(false);
					}
					else if (SceneManager::GetIsTransitionToNight())
					{
						sprite.setPosition({ 717, 413 });
						currentPos = { 717, 413 };
						SceneManager::SetIsTransitionToNight(false);
					}
					

					if (!SceneManager::GetIsTransitioning())
					{
						ReloadWeapon(deltaTime);

						weapons[currentWeapon]->Update(deltaTime, hoursSlept);

						direction = VectorUtility::Normalize(direction);
						currentPos += direction * speed * deltaTime;
					}
				}
			}
		}	
	}	

	if (!HoursInterface::GetIsOpen())
	{
		if (!DayTasksManager::GetScavengeResultsOpen())
		WeaponPosition();
	}

	sprite.setPosition(currentPos);

}

void Player::Movement()
{
	direction = sf::Vector2f({ 0, 0 });

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction += VectorUtility::UP + VectorUtility::LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction += VectorUtility::UP + VectorUtility::RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction += VectorUtility::DOWN + VectorUtility::LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction += VectorUtility::DOWN + VectorUtility::RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction += VectorUtility::UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction += VectorUtility::LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction += VectorUtility::DOWN;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction += VectorUtility::RIGHT;
	}
	else
	{
		direction = sf::Vector2f({ 0, 0 });		
	}		

}


void Player::LookDirection()
{
	sf::Vector2f relativePosition = sf::Vector2f(Program::GetMousePosition()) - sprite.getPosition();
	
	if (direction != sf::Vector2f({ 0, 0 }))
	{		
		if (relativePosition.x <= 0)
			SetCurrentAnimation("walkLeft");
		else 
			SetCurrentAnimation("walkRight");
	}
	else
	{
		if (relativePosition.x <= 0)
			SetCurrentAnimation("idleLeft");
		else 
			SetCurrentAnimation("idleRight");
	}
	
}

void Player::WeaponPosition()
{	
	if (GetCurrentWeapon().GetTag() == Tag::Gun)
	{
		if (GetCurrentAnimation() == "idleRight" || GetCurrentAnimation() == "walkRight")
		{			
			weapons[currentWeapon]->Graphic().setPosition(currentPos + sf::Vector2f({ 43, 22 }));
			weapons[currentWeapon]->SetCurrentAnimation("weaponRight");
		}
		else if (GetCurrentAnimation() == "idleLeft" || GetCurrentAnimation() == "walkLeft")
		{
			weapons[currentWeapon]->Graphic().setPosition(currentPos + sf::Vector2f({ 0, 22 }));
			weapons[currentWeapon]->SetCurrentAnimation("weaponLeft");
		}		
	}
	else if (GetCurrentWeapon().GetTag() == Tag::Shotgun)
	{
		if (GetCurrentAnimation() == "idleRight" || GetCurrentAnimation() == "walkRight")
		{								
			weapons[currentWeapon]->Graphic().setPosition(currentPos + sf::Vector2f({33, 24 }));
			weapons[currentWeapon]->SetCurrentAnimation("weaponRight");
		}
		else if (GetCurrentAnimation() == "idleLeft" || GetCurrentAnimation() == "walkLeft")
		{
			weapons[currentWeapon]->Graphic().setPosition(currentPos + sf::Vector2f({ 10, 24 }));
			weapons[currentWeapon]->SetCurrentAnimation("weaponLeft");
		}
	}
	if (GetCurrentWeapon().GetTag() == Tag::Uzi)
	{
		if (GetCurrentAnimation() == "idleRight" || GetCurrentAnimation() == "walkRight")
		{
			weapons[currentWeapon]->Graphic().setPosition(currentPos + sf::Vector2f({ 43, 22 }));
			weapons[currentWeapon]->SetCurrentAnimation("weaponRight");
		}
		else if (GetCurrentAnimation() == "idleLeft" || GetCurrentAnimation() == "walkLeft")
		{
			weapons[currentWeapon]->Graphic().setPosition(currentPos + sf::Vector2f({ 0, 22 }));
			weapons[currentWeapon]->SetCurrentAnimation("weaponLeft");
		}
	}
	

}

void Player::FireWeapon(sf::Event event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i bulletDirection = Program::GetMousePosition();
		
		
				
		if (!canShoot) return;		

		weapons[currentWeapon]->Shoot(bulletDirection);
		canShoot = false;
	}
	else if (event.type == sf::Event::MouseButtonReleased)	
		if (event.mouseButton.button == sf::Mouse::Left)
			canShoot = true;			
}

void Player::FireUzi()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i bulletDirection = Program::GetMousePosition();
		weapons[currentWeapon]->ShootUzi(bulletDirection);
	}
		
}

void Player::ReloadWeapon(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !weapons[currentWeapon]->GetIsReloading())
	{
		weapons[currentWeapon]->SetIsReloading(true);
	}
}

void Player::SwitchWeapons()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		currentWeapon = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		if (!hasShotgun) return;
		currentWeapon = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		if (!hasUzi) return;
		currentWeapon = 2;
	}
	
}

sf::FloatRect Player::GetBounds()
{
	return sprite.getGlobalBounds();
}

void Player::EButtonOn()
{
	sf::Color color(eButton->Graphic().getColor().r, eButton->Graphic().getColor().g, eButton->Graphic().getColor().b, 255);
	eButton->Graphic().setColor(color);
}

void Player::EButtonOff()
{
	sf::Color color(eButton->Graphic().getColor().r, eButton->Graphic().getColor().g, eButton->Graphic().getColor().b, 0);
	eButton->Graphic().setColor(color);
}

void Player::AddHoursSlept(int hours)
{
	hoursSlept += hours;
	hoursSlept = std::clamp(hoursSlept, 0, 6);

}

void Player::RigidObjectCollision(float deltaTime)
{
	sf::Vector2f collissionOffset = direction * speed * deltaTime;
	collissionOffset *= 1.0f;

	currentPos -= collissionOffset;

}

void Player::Die()
{
	if (!isAlive) return;

	sf::Vector2f relativePosition = sf::Vector2f(Program::GetMousePosition()) - sprite.getPosition();
	
	if (relativePosition.x <= 0)
		SetCurrentAnimation("dieLeft");
	else
		SetCurrentAnimation("dieRight");	

	isAlive = false;	

}

void Player::ResetPlayer()
{
	isAlive = true;
	hasShotgun = false;
	hasUzi = false;
	resources = 150;
	hoursSlept = 6;
	currentWeapon = 0;

	score = 0;

	currentPos = sf::Vector2f{ 720,1200/ 2 - 100 };

}

