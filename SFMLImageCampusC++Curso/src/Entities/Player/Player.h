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
	static bool playerStopSound;
	static int score;

	sf::SoundBuffer insideFootstepsBuffer;
	sf::Sound insideFootstepsSound;

	sf::SoundBuffer outsideFootstepsBuffer;
	sf::Sound outsideFootstepsSound;

	Entity* eButton;

	static int resources;

	static int hoursSlept;

	int yMapLimit;
	static bool isAlive;
	float speed;
	std::vector<Weapon*> weapons;
	bool canShoot;

	static bool hasShotgun;
	static bool hasUzi;

	int currentWeapon;
	sf::Vector2f gunOffset;

	void Movement();
	void LookDirection();
	void WeaponPosition();
	void FireWeapon(sf::Event event);
	void FireUzi();
	void ReloadWeapon(float deltaTime);
	void SwitchWeapons();

public:
	Player(float speed, Weapon* gun, Weapon* shotgun, Weapon* uzi, float windowWidth, float windowHeight, sf::Vector2i frameSize,
		std::string imageFilePath, sf::Vector2i spriteSheetSize);
	void Update(float deltaTime) override;
	void Input(sf::Event event);
	
	static void SpendResources(int value) { resources -= value; }
	static int GetResources() { return resources; }
	static void AddResources(int resourcesFound) { resources += resourcesFound; }

	Weapon GetCurrentWeapon() { return *weapons[currentWeapon]; }
	
	static int GetHoursSlept() { return hoursSlept; }
	static void AddHoursSlept(int hours);
	static void ResetHoursSlept() { hoursSlept = 0; }

	static bool GetHasShotgun() { return hasShotgun; }
	static bool GetHasUzi() { return hasUzi; }

	static void SetHasShotgun(bool value) { hasShotgun = true; }
	static void SetHasUzi(bool value) { hasUzi = true; }

	static void SetStopSound(bool value) { playerStopSound = value; }

	static int GetScore() { return score; }
	static void AddScore(int value) { score += value; }

	static bool GetIsAlive() { return isAlive; }
	static void SetIsAlive(bool value) { isAlive = value; }
	void RigidObjectCollision(float deltaTime);
	sf::FloatRect GetBounds() override;
	Entity* GetEButton() { return eButton; }
	void EButtonOn();
	void EButtonOff();
	void Die();

	void UpdateSound();

	void ResetPlayer();
	
	void Destroy();

};

