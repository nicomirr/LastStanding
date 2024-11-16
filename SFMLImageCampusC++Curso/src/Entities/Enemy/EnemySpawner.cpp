#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(GridManager* nodesGrid, PathFinder* pathfinder, SceneManager* sceneManager)
{
	this->sceneManager = sceneManager;

	currentWaveIndex = 0;
	totalWaves = 6;
	enemyIndex = 0;
	
	float xSpawnPos = 0;
	float ySpawnPos = 0;

	spawnTime = 5;
	spawnTimer = 0;

	for (int i = 0; i < 13; i++)
	{		
		spawnPositions.push_back({ xSpawnPos,0 });
		spawnPositions.push_back({ xSpawnPos,880 });
		xSpawnPos += 100;
	}

	for (int i = 0; i < 8; i++)
	{
		spawnPositions.push_back({ 0,ySpawnPos });
		spawnPositions.push_back({ 1200,ySpawnPos });
		ySpawnPos += 88;
	}

	sf::Vector2f zombieScale = { 1.2f, 1.0f };
	float zombieMinHealth = 18;
	float zombieMaxHealth = 24;
	float zombieRegularSpeed = 70;
	float zombieSpeedNearPlayer = 2.0f;
	float zombieDamage = 4;
	float zombieAttackDelay = 2.5f;
	float zombieAnimationSpeed = 3;
	float zombieDeathAnimationSpeed = 3;
	sf::Vector2i zombieAnimationFrameSize = { 33, 49 };
	sf::Vector2i zombieDeathAnimationFrameSize = { 49, 49 };
	std::string zombieFilePath = "res\\textures\\enemies\\zombie\\Zombie.png";
	sf::Vector2i zombieSpriteSheetSize = { 146, 294 };

	sf::Vector2f zombieKidScale = { 1.1f, 1.0f };
	float zombieKidMinHealth = 12;
	float zombieKidMaxHealth = 17;
	float zombieKidRegularSpeed = 100;
	float zombieKidSpeedNearPlayer = 0.6f;
	float zombieKidDamage = 3;
	float zombieKidAttackDelay = 2.5f;
	float zombieKidAnimationSpeed = 5;
	float zombieKidDeathAnimationSpeed = 5;
	sf::Vector2i zombieKidAnimationFrameSize = { 36, 33 };
	sf::Vector2i zombieKidDeathAnimationFrameSize = { 36, 33 };
	std::string zombieKidFilePath = "res\\textures\\enemies\\zombiekid\\ZombieKid.png";
	sf::Vector2i zombieKidSpriteSheetSize = { 108, 198 };

	sf::Vector2f zombieFatScale = { 1.3f, 1.3f };
	float zombieFatMinHealth = 26;
	float zombieFatMaxHealth = 30;
	float zombieFatRegularSpeed = 55;
	float zombieFatSpeedNearPlayer = 1.0f;
	float zombieFatDamage = 6;
	float zombieFatAttackDelay = 2.5f;
	float zombieFatAnimationSpeed = 2;
	float zombieFatDeathAnimationSpeed = 1;
	sf::Vector2i zombieFatAnimationFrameSize = { 55, 48 };
	sf::Vector2i zombieFatDeathAnimationFrameSize = { 55, 48 };
	std::string zombieFatFilePath = "res\\textures\\enemies\\zombiefat\\ZombieFat.png";
	sf::Vector2i zombieFatSpriteSheetSize = { 163, 288 };

	for (int i = 0; i < 150; i++)
	{
		if (i > 99)
		{
			enemies.push_back(new Enemy(nodesGrid, pathfinder, zombieFatScale, zombieFatMinHealth, zombieFatMaxHealth, zombieFatRegularSpeed, 
				zombieFatSpeedNearPlayer,zombieFatDamage, zombieFatAttackDelay, zombieFatAnimationSpeed, 
				zombieFatDeathAnimationSpeed, zombieFatAnimationFrameSize, zombieFatDeathAnimationFrameSize, 
				zombieFatFilePath, zombieFatSpriteSheetSize));

			enemies[i]->SetTag(Tag::Enemy);
			CollisionHandler::AddCollision(enemies[i]);
		}
		else if (i > 49)
		{

			enemies.push_back(new Enemy(nodesGrid, pathfinder, zombieKidScale, zombieKidMinHealth, zombieKidMaxHealth, zombieKidRegularSpeed,
				zombieKidSpeedNearPlayer, zombieKidDamage, zombieKidAttackDelay, zombieKidAnimationSpeed, 
				zombieKidDeathAnimationSpeed, zombieKidAnimationFrameSize, zombieKidDeathAnimationFrameSize, 
				zombieKidFilePath, zombieKidSpriteSheetSize));

			enemies[i]->SetTag(Tag::Enemy);
			CollisionHandler::AddCollision(enemies[i]);

		}
		else
		{
			enemies.push_back(new Enemy(nodesGrid, pathfinder, zombieScale, zombieMinHealth, zombieMaxHealth, zombieRegularSpeed,
				zombieSpeedNearPlayer, zombieDamage, zombieAttackDelay,	zombieAnimationSpeed, zombieDeathAnimationSpeed, 
				zombieAnimationFrameSize, zombieDeathAnimationFrameSize, zombieFilePath, zombieSpriteSheetSize));			

			enemies[i]->SetTag(Tag::Enemy);
			CollisionHandler::AddCollision(enemies[i]);
		}
		
	}	


	int totalEnemies = 50;
	int normalZombiesIndex = 0;
	int kidZombiesIndex = 0;
	int fatZombiesIndex = 0;
	

	//OLEADA 1

	std::vector<Enemy*> waveOneEnemies;

	for (int i = 0; i < totalEnemies; i++)
	{
		waveOneEnemies.push_back(enemies[normalZombiesIndex]);
		normalZombiesIndex++;
	}

	int waveOneMinSpawnEnemies = 1;
	int waveOneMaxSpawnEnemies = 2;
	float waveOneMinSpawnTime = 4.5;
	float waveOneMaxSpawnTime = 7;
	float waveOneDuration = 45;

	//OLEADA 2

	std::vector<Enemy*> waveTwoEnemies;
	
	normalZombiesIndex = 0;
	kidZombiesIndex = 50;
	
	for (int i = 0; i < totalEnemies; i++)
	{
		if (i > 30)
		{
			waveTwoEnemies.push_back(enemies[kidZombiesIndex]);
			kidZombiesIndex++;
		}
		else
		{
			waveTwoEnemies.push_back(enemies[normalZombiesIndex]);
			normalZombiesIndex++;
		}
	}

	int waveTwoMinSpawnEnemies = 1;
	int waveTwoMaxSpawnEnemies = 2;
	float waveTwoMinSpawnTime = 4.5;
	float waveTwoMaxSpawnTime = 6;
	float waveTwoDuration = 60;

	//OLEADA 3

	std::vector<Enemy*> waveThreeEnemies;

	normalZombiesIndex = 0;
	kidZombiesIndex = 50;
	fatZombiesIndex = 100;

	for (int i = 0; i < totalEnemies; i++)
	{
		if (i > 40)
		{
			waveThreeEnemies.push_back(enemies[fatZombiesIndex]);
			fatZombiesIndex++;
		}
		else if (i > 17)
		{
			waveThreeEnemies.push_back(enemies[kidZombiesIndex]);
			kidZombiesIndex++;
		}
		else
		{
			waveThreeEnemies.push_back(enemies[normalZombiesIndex]);
			normalZombiesIndex++;
		}

	}

	int waveThreeMinSpawnEnemies = 2;
	int waveThreeMaxSpawnEnemies = 2;
	float waveThreeMinSpawnTime = 5.5;
	float waveThreeMaxSpawnTime = 7;
	float waveThreeDuration = 60;

	//OLEADA 4

	std::vector<Enemy*> waveFourEnemies;

	normalZombiesIndex = 0;
	kidZombiesIndex = 50;
	fatZombiesIndex = 100;

	for (int i = 0; i < totalEnemies; i++)
	{
		if (i > 34)
		{
			waveFourEnemies.push_back(enemies[fatZombiesIndex]);
			fatZombiesIndex++;
		}
		else if (i > 15)
		{
			waveFourEnemies.push_back(enemies[kidZombiesIndex]);
			kidZombiesIndex++;
		}
		else
		{
			waveFourEnemies.push_back(enemies[normalZombiesIndex]);
			normalZombiesIndex++;
		}
	}

	int waveFourMinSpawnEnemies = 2;
	int waveFourMaxSpawnEnemies = 2;
	float waveFourMinSpawnTime = 5;
	float waveFourMaxSpawnTime = 6.5;
	float waveFourDuration = 80;

	//OLEADA 5

	std::vector<Enemy*> waveFiveEnemies;

	normalZombiesIndex = 0;
	kidZombiesIndex = 50;
	fatZombiesIndex = 100;

	for (int i = 0; i < totalEnemies; i++)
	{
		if (i > 30)
		{
			waveFiveEnemies.push_back(enemies[fatZombiesIndex]);
			fatZombiesIndex++;
		}
		else if (i > 10)
		{
			waveFiveEnemies.push_back(enemies[kidZombiesIndex]);
			kidZombiesIndex++;
		}
		else
		{
			waveFiveEnemies.push_back(enemies[normalZombiesIndex]);
			normalZombiesIndex++;
		}
	}


	int waveFiveMinSpawnEnemies = 2;
	int waveFiveMaxSpawnEnemies = 3;
	float waveFiveMinSpawnTime = 6;
	float waveFiveMaxSpawnTime = 9;
	float waveFiveDuration = 80;


	//OLEADA 6

	std::vector<Enemy*> waveSixEnemies;

	normalZombiesIndex = 0;
	kidZombiesIndex = 50;
	fatZombiesIndex = 100;

	for (int i = 0; i < totalEnemies; i++)
	{
		if (i > 25)
		{
			waveSixEnemies.push_back(enemies[fatZombiesIndex]);
			fatZombiesIndex++;
		}
		else if (i > 10)
		{
			waveSixEnemies.push_back(enemies[kidZombiesIndex]);
			kidZombiesIndex++;
		}
		else
		{
			waveSixEnemies.push_back(enemies[normalZombiesIndex]);
			normalZombiesIndex++;
		}
	}


	int waveSixMinSpawnEnemies = 2;
	int waveSixMaxSpawnEnemies = 3;
	float waveSixMinSpawnTime = 6;
	float waveSixMaxSpawnTime = 8;
	float waveSixDuration = 100;

	

	waves.push_back( new Wave({ waveOneEnemies, waveOneMinSpawnEnemies, waveOneMaxSpawnEnemies, 0, waveOneMinSpawnTime, 
		waveOneMaxSpawnTime, false, waveOneDuration }));

	waves.push_back(new Wave({ waveTwoEnemies, waveTwoMinSpawnEnemies, waveTwoMaxSpawnEnemies, 0, waveTwoMinSpawnTime,
		waveTwoMaxSpawnTime, false, waveTwoDuration }));

	waves.push_back(new Wave({ waveThreeEnemies, waveThreeMinSpawnEnemies, waveThreeMaxSpawnEnemies, 0, waveThreeMinSpawnTime,
		waveThreeMaxSpawnTime, false, waveThreeDuration }));

	waves.push_back(new Wave({ waveFourEnemies, waveFourMinSpawnEnemies, waveFourMaxSpawnEnemies, 0, waveFourMinSpawnTime,
		waveFourMaxSpawnTime, false, waveFourDuration }));

	waves.push_back(new Wave({ waveFiveEnemies, waveFiveMinSpawnEnemies, waveFiveMaxSpawnEnemies, 0, waveFiveMinSpawnTime,
		waveFiveMaxSpawnTime, false, waveFiveDuration }));
	
	waves.push_back(new Wave({ waveSixEnemies, waveSixMinSpawnEnemies, waveSixMaxSpawnEnemies, 0, waveSixMinSpawnTime,
		waveSixMaxSpawnTime, false, waveSixDuration }));

}

void EnemySpawner::Update(float deltaTime, sf::Vector2f playerPos)
{	

	if (!TimeClock::GetIsNight() && !TimeClock::GetIsDay())
	{
		if (TimeClock::GetCurrentDay() < 6)
		{
			sceneManager->SceneTransitionEndNightDayCicle(deltaTime);
			return;
		}
		else
			SceneManager::SetIsEnding(true);
		
	}
			
	int activeEnemies = 0;

	
	if (!waves[currentWaveIndex]->spawnTimeSet)
	{		
		waves[currentWaveIndex]->spawnTime = RandomNum::RandomRange(waves[currentWaveIndex]->minSpawnTime, waves[currentWaveIndex]->maxSpawnTime);
		waves[currentWaveIndex]->spawnTimeSet = true;

	}	

	for (int i = 0; i < waves[currentWaveIndex]->enemies.size(); i++)
	{		
		waves[currentWaveIndex]->enemies[i]->Update(deltaTime, playerPos);
		
		if (waves[currentWaveIndex]->enemies[i]->GetIsActive())
			activeEnemies++;

		if (i >= waves[currentWaveIndex]->enemies.size() - 1 && !waves[currentWaveIndex]->enemies[i]->GetIsActive())
		{
			if (waveTimer >= waves[currentWaveIndex]->waveDuration && activeEnemies <= 0)
			{
				TimeClock::SetIsNight(false);
				TimeClock::SetHours(12);
				Player::ResetHoursSlept();

				if (currentWaveIndex < waves.size() - 1)
				{
					waveTimer = 0;
					currentWaveIndex++;

					for (int j = 0; j < waves[currentWaveIndex]->enemies.size(); j++)
					{
						waves[currentWaveIndex]->enemies[j]->SetIsActive(false);
					}
				}
			}
		}
	}

	if (!TimeClock::GetIsNight()) return;
	if (waveTimer >= waves[currentWaveIndex]->waveDuration) return;

	waveTimer += deltaTime;

	std::cout << (int)waveTimer << std::endl;
	std::cout << waves[currentWaveIndex]->waveDuration - 10 << std::endl;

	if (waveTimer >= (waves[currentWaveIndex]->waveDuration - 10))
	{
		TimeClock::StartClockRotation();
	}

	spawnTimer += deltaTime;

	
	if (spawnTimer >= waves[currentWaveIndex]->spawnTime)
	{
		spawnTimer -= waves[currentWaveIndex]->spawnTime;
		SpawnEnemy();
		waves[currentWaveIndex]->spawnTimeSet = false;
	}

}



void EnemySpawner::SpawnEnemy()
{
	int i = 0;
	int maxEnemies = RandomNum::RandomRange(waves[currentWaveIndex]->minSpawnEnemies, waves[currentWaveIndex]->maxSpawnEnemies);
	int previousSpawnPositionIndex = -1;


	while (i < maxEnemies)
	{		
		spawnPositionIndex = rand() % spawnPositions.size();

		if (spawnPositionIndex != previousSpawnPositionIndex)
		{
			enemyIndex = RandomNum::RandomRange(0, waves[currentWaveIndex]->enemies.size() - 1);

			if (!waves[currentWaveIndex]->enemies[enemyIndex]->GetIsActive())
			{
				waves[currentWaveIndex]->enemies[enemyIndex]->Graphic().setPosition(spawnPositions[spawnPositionIndex]);
				waves[currentWaveIndex]->enemies[enemyIndex]->SetIsActive(true);

				previousSpawnPositionIndex = spawnPositionIndex;				
				i++;
			}			
		}		
	}		
		
}

void EnemySpawner::ResetEnemySpawner()
{
	waveTimer = 0;

	for (int i = 0; i < waves[currentWaveIndex]->enemies.size(); i++)
	{
		waves[currentWaveIndex]->enemies[i]->SetIsActive(false);
		waves[currentWaveIndex]->enemies[i]->ResetEnemy();
	}

	currentWaveIndex = 0;

}
