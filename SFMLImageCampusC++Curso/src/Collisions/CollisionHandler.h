#pragma once
#include <vector>
#include "../Entities/Entity.h"
#include "../Entities/Enviroment/Fence.h"
#include "../Entities/Enemy/Enemy.h"
#include "../Entities/Player/Player.h"
#include "../SceneManager/SceneManager.h"
#include "../Entities/Enviroment/Bed.h"
#include "../DayTasksManager/DayTasksManager.h"
#include "../Entities/Enviroment/Radio.h"
#include "../Entities/Enviroment/SOSSign.h"
#include "../Entities/HUD/PopUpWindow.h"

class CollisionHandler
{
private: 
	static std::vector<Entity*> entities;
	static float addSubstractHoursTimer;
	static float okButtonTimer;

	static sf::SoundBuffer doorBuffer;
	static sf::Sound doorSound;

	static sf::SoundBuffer bookBuffer;
	static sf::Sound bookSound;


public:
	static void AddCollision(Entity* entity);
	static void SolveCollisions(float deltaTime, SceneManager* sceneManager, sf::RenderWindow* window, HoursInterface* carHoursInterface,
		HoursInterface* toolboxHoursInterface, HoursInterface* planksHoursInterface, HoursInterface* bricksHoursInterface,
		HoursInterface* bedHoursInterface, HoursInterface* sosSignHoursInterface, DayTasksManager* dayTasksManager,
		PopUpWindow* carWindow, PopUpWindow* bookWindow, PopUpWindow* calendarWindow, PopUpWindow* boardWindow, PopUpWindow* bedWindow,
		PopUpWindow* radioWindow);
	static std::vector<Entity*> GetEntities() { return entities; };

	static void CreateSounds();

	static void Destroy();
};

