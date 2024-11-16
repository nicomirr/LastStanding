#pragma once

#include "Enemy.h"

struct Wave
{
	std::vector<Enemy*> enemies;
	int minSpawnEnemies;
	int maxSpawnEnemies;
	float spawnTime;
	float minSpawnTime;
	float maxSpawnTime;
	bool spawnTimeSet;
	float waveDuration;
};