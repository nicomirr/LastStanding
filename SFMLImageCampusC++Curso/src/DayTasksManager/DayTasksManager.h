#pragma once
#include "../Entities/Enviroment/Car.h"
#include "../Entities/Enviroment/House.h"
#include "../Entities/Enviroment/Fence.h"
#include "../Entities/TimeClock/TimeClock.h"
#include "../Entities/Player/Player.h"
#include <algorithm>

class DayTasksManager
{
private:

	int weaponFindChance;
	static bool scavengeResultsOpen;

	int resourcesFound;

	static bool showShotgunHasBeenFoundText;
	static bool showUziHasBeenFoundText;

	std::vector<Fence*> fences;
	Car* car;
	House* house;

	Entity* background;
	Entity* buttonClose;

	sf::Font* font;
	
	sf::Text* resourcesFoundText;
	sf::Text* resourcesText;

	sf::Text* shotgunFoundText;
	sf::Text* uziFoundText;
		
public: 
	DayTasksManager(std::vector<Fence*> fences, Car* car, House* house);

	void Update();

	static bool GetScavengeResultsOpen() { return scavengeResultsOpen; }
	static void SetScavengeResultsOpen(bool value) { scavengeResultsOpen = value; }

	Entity* GetBackground() { return background; }
	Entity* GetButtonClose() { return buttonClose; }

	sf::Text* GetResourcesFoundText() { return resourcesFoundText; }
	sf::Text* GetResourcesText() { return resourcesText; }

	static bool GetShowShotgunHasBeenFoundText() { return showShotgunHasBeenFoundText; }
	static bool GetShowUziHasBeenFoundText() { return showUziHasBeenFoundText; }

	static void SetShowShotgunHasBeenFoundText(bool value) { showShotgunHasBeenFoundText = value; }
	static void SetShowUziHasBeenFoundText(bool value) { showUziHasBeenFoundText = value; }

	sf::Text* GetShotgunFoundText() { return shotgunFoundText; }
	sf::Text* GetUziFoundText() { return uziFoundText; }

	void RepairFences(int hours);
	void RepairCar(int hours);
	void RepairHouse(int hours);
	void Scavenge(int hours);
	void Sleep(int hours);

	void Destroy();
};

