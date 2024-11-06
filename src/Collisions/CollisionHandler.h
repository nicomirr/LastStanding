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

class CollisionHandler
{
private: 
	static std::vector<Entity*> entities;
	static float addSubstractHoursTimer;
	static float okButtonTimer;

public:
	static void AddCollision(Entity* entity);
	static void SolveCollisions(float deltaTime, SceneManager* sceneManager, sf::RenderWindow* window, HoursInterface* carHoursInterface,
		HoursInterface* toolboxHoursInterface, HoursInterface* planksHoursInterface, HoursInterface* bricksHoursInterface,
		HoursInterface* bedHoursInterface, DayTasksManager* dayTasksManager);
	static std::vector<Entity*> GetEntities() { return entities; };
};

/*
ARMAR LISTA DE ENTITYS.
CON EL TAG QUE ESTARA EN ENTITY SE DIFERENCIARA ENTRE ENTITIES Y SE RESOLVERAN ACA
LAS COLISIONES.

*/