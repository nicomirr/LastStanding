#pragma once
#include <vector>
#include "../Entities/Entity.h"
#include "../Entities/Enviroment/Fence.h"
#include "../Entities/Enemy/Enemy.h"
#include "../Entities/Player/Player.h"
#include "../SceneManager/SceneManager.h"
#include "../Entities/Enviroment/Bed.h"

class CollisionHandler
{
private: 
	static std::vector<Entity*> entities;

public:
	static void AddCollision(Entity* entity);
	static void SolveCollisions(float deltaTime, SceneManager* sceneManager);
	static std::vector<Entity*> GetEntities() { return entities; };
};

/*
ARMAR LISTA DE ENTITYS.
CON EL TAG QUE ESTARA EN ENTITY SE DIFERENCIARA ENTRE ENTITIES Y SE RESOLVERAN ACA
LAS COLISIONES.

*/