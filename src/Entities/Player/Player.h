#pragma once

#include <iostream>
#include "SFML/System.hpp"
#include "../Entity.h"
#include "../AnimatedEntity.h"
#include "../Moveable.h"
#include "../../Utilities/VectorUtility.h"
#include "../Weapon/Weapon.h"
#include "../Time/HoursInterface.h"


class Player :  public AnimatedEntity, public Moveable
{
private:
	Entity* eButton;

	int yMapLimit;
	bool isAlive;
	float speed;
	std::vector<Weapon*> weapons;
	bool canShoot;
	bool hasShotgun;
	int currentWeapon;
	sf::Vector2f gunOffset;

	void Movement();
	void LookDirection();
	void WeaponPosition();
	void FireWeapon(sf::Event event);
	void ReloadWeapon(float deltaTime);
	void SwitchWeapons();

public:
	Player(float speed, Weapon* weapon, float windowWidth, float windowHeight, sf::Vector2i frameSize,
		std::string imageFilePath, sf::Vector2i spriteSheetSize);
	void Update(float deltaTime) override;
	void Input(sf::Event event);
	Weapon GetCurrentWeapon() { return *weapons[currentWeapon]; }
	bool GetIsAlive() const { return isAlive; }
	void SetIsAlive(bool value) { isAlive = value; }
	void RigidObjectCollision(float deltaTime);
	sf::FloatRect GetBounds() override;
	Entity* GetEButton() { return eButton; }
	void EButtonOn();
	void EButtonOff();
	void Die();



};

