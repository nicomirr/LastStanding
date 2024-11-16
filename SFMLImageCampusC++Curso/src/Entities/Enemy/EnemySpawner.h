#pragma once
#include <vector>
#include "Enemy.h"
#include "Wave.h"
#include "../../Collisions/CollisionHandler.h"
#include "../TimeClock/TimeClock.h"
#include "../../SceneManager/SceneManager.h"

class EnemySpawner
{
private:	
	SceneManager* sceneManager;
	int currentWaveIndex;
	float waveTimer;
	int totalWaves;
	int enemyIndex;
	float spawnTime;
	float spawnTimer;

	int spawnPositionIndex;
	std::vector<sf::Vector2f> spawnPositions;
	std::vector<Enemy*> enemies;
	std::vector<Wave*> waves;
	void SpawnEnemy();

public:
	EnemySpawner(GridManager* nodesGrid, PathFinder* pathfinder, SceneManager* sceneManager);
	void Update(float deltaTime, sf::Vector2f playerPos);
	std::vector<Enemy*> GetEnemies() { return enemies; }
	void ResetEnemySpawner();
	
};

/*
HACER UN VECTOR QUE CONTENGA LAS OLEADAS CON  CADA UNO DE LOS ENEMIGOS YA PREPARADOS (vectores para
oleadas).


*/