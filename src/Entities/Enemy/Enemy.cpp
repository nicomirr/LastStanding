#include "Enemy.h"

//sf::SoundBuffer Enemy::zombieHittingBuffer;
//sf::SoundBuffer Enemy::zombieHittingTwoBuffer;
//sf::SoundBuffer Enemy::zombieHittingThreeBuffer;
//sf::SoundBuffer Enemy::zombieHittingFourBuffer;

//sf::Sound Enemy::zombieHittingSound;
//sf::Sound Enemy::zombieHittingTwoSound;
//sf::Sound Enemy::zombieHittingThreeSound;
//sf::Sound Enemy::zombieHittingFourSound;

//int Enemy::attackingZombies;

Enemy::Enemy(GridManager* nodesGrid, PathFinder* pathfinder, sf::Vector2f scale, float minHealth, float maxHealth, float regularSpeed, 
	float speedNearPlayer,	float damage, float attackDelay, float animationSpeed, float deathAnimationSpeed, sf::Vector2i animationFrameSize,
	sf::Vector2i deathAnimationFrameSize, std::string imageFilePath, sf::Vector2i spriteSheetSize) 
	: AnimatedEntity(animationFrameSize, imageFilePath, spriteSheetSize)
{
	std::string  zombieHurtFilePath = "res\\audio\\enemies\\ZombieHurt.mp3";
	zombieHurtBuffer.loadFromFile(zombieHurtFilePath);

	zombieHurtSound.setBuffer(zombieHurtBuffer);
	zombieHurtSound.setVolume(100);
	zombieHurtSound.setLoop(false);


	/*std::string  zombieHittingFilePath = "res\\audio\\enemies\\ZombieHitting2.mp3";
	zombieHittingBuffer.loadFromFile(zombieHittingFilePath);

	zombieHittingSound.setBuffer(zombieHittingBuffer);
	zombieHittingSound.setVolume(100);
	zombieHittingSound.setLoop(false);*/

	/*std::string  zombieHittingTwoFilePath = "res\\audio\\enemies\\ZombieHitting2.mp3";
	zombieHittingTwoBuffer.loadFromFile(zombieHittingTwoFilePath);

	zombieHittingTwoSound.setBuffer(zombieHittingTwoBuffer);
	zombieHittingTwoSound.setVolume(100);
	zombieHittingTwoSound.setLoop(false);

	std::string  zombieHittingThreeFilePath = "res\\audio\\enemies\\ZombieHitting3.mp3";
	zombieHittingThreeBuffer.loadFromFile(zombieHittingThreeFilePath);

	zombieHittingThreeSound.setBuffer(zombieHittingThreeBuffer);
	zombieHittingThreeSound.setVolume(100);
	zombieHittingThreeSound.setLoop(false);

	std::string  zombieHittingFourFilePath = "res\\audio\\enemies\\ZombieHitting4.mp3";
	zombieHittingFourBuffer.loadFromFile(zombieHittingFourFilePath);

	zombieHittingFourSound.setBuffer(zombieHittingFourBuffer);
	zombieHittingFourSound.setVolume(100);
	zombieHittingFourSound.setLoop(false);*/

	this->nodesGrid = nodesGrid;
	this->pathfinder = pathfinder;		

	isActive = false;
	isAlive = true;

	sprite.setScale(scale);
	
	this->minHealth = minHealth;
	this->maxHealth = maxHealth;
	health = RandomNum::RandomRange(minHealth, maxHealth);
	
	sf::Vector2i healthBarAnimationFrameSize = { 47, 8 };
	std::string healthBarImageFilePath = "res\\textures\\healthbar\\EnemyHealthBar.png";
	sf::Vector2i healthBarSpriteSheetSize = { 47, 40 };

	healthBar = new HealthBar(health, healthBarAnimationFrameSize, healthBarImageFilePath, healthBarSpriteSheetSize);


	AnimationData emptyBar = { 0, 0, 1 , false };
	AnimationData oneQuarterBar = { 0, 1, 1 , false };
	AnimationData halfBar = { 0, 2, 1 , false };
	AnimationData threeQuarterBar = { 0, 3, 1 , false };
	AnimationData fullBar = { 0, 4, 1 , false };

	healthBar->AddAnimation("emptyBar", emptyBar);
	healthBar->AddAnimation("oneQuarterBar", oneQuarterBar);
	healthBar->AddAnimation("halfBar", halfBar);
	healthBar->AddAnimation("threeQuarterBar", threeQuarterBar);
	healthBar->AddAnimation("fullBar", fullBar);

	healthBar->SetCurrentAnimation("fullBar");

	this->regularSpeed = regularSpeed;
	this->speedNearPlayer = speedNearPlayer;
	speed = regularSpeed;				//CAMBIAR ESTO Y PARAMETROS!!!!!!!

	this->damage = damage;
	
	this->attackDelay = attackDelay;

	this->animationFrameSize = animationFrameSize;
	this->deathAnimationFrameSize = deathAnimationFrameSize;


	AnimationData leftWalk = { animationSpeed, 0, 3, true };
	AnimationData rightWalk = { animationSpeed, 1, 3, true };
	AnimationData leftAttack = { animationSpeed, 2, 3, true };
	AnimationData rightAttack = { animationSpeed, 3, 3, true };
	AnimationData rightDeath = { deathAnimationSpeed, 4, 3, false };
	AnimationData leftDeath = { deathAnimationSpeed, 5, 3, false };

	AddAnimation("leftWalk", leftWalk);
	AddAnimation("rightWalk", rightWalk);
	AddAnimation("leftAttack", leftAttack);
	AddAnimation("rightAttack", rightAttack);
	AddAnimation("rightDeath", rightDeath);
	AddAnimation("leftDeath", leftDeath);

	objective = { 600, 440 };	
	
}

void Enemy::Update(float deltaTime, sf::Vector2f playerPos)
{
	UpdateSound();

	if (!isActive) return;
	if (Car::GetIsDestroyed())
		isAttackingCar = false;

	float yOffset = -10;
	float xOffset = 0;

	healthBar->Update(deltaTime, sprite.getPosition(), yOffset, xOffset, health);
	HealthBarAppearance();

	if (fenceObjective != nullptr)
	{
		if (fenceObjective->GetIsFenceBroken())
		{
			isAttackingFence = false;
			//attackZombieAdded = false;
		}
	}

	this->playerPos = playerPos;

	if (isAttackingPlayer)
	{
		objective = this->playerPos;
		pathfinder->Update();
	}

	DeathTimer(deltaTime);

	AnimatedEntity::Update(deltaTime);

	if (!isAlive) return;
	if (isAttackingFence) return;
	if (isAttackingHouse) return;
	if (isAttackingCar) return;

	EnemyMovement(deltaTime);
		
}

void Enemy::EnemyMovement(float deltaTime)
{	
	if (!Player::GetIsAlive()) return;

	direction = objective - sprite.getPosition();

	float distanceToObjective = GetDistanceToObjective();
	if (distanceToObjective > 0)
	{
		direction /= distanceToObjective;
	}

	newPosition = sprite.getPosition() + direction * speed * deltaTime;
	
	sprite.setPosition(newPosition);
	EnemyDirection();
	
	/*else
	{
		SetStartingNode();
		FindPath();
		FollowPath(deltaTime);
	}*/

}

void Enemy::UpdateSound()
{
	zombieHurtSound.setVolume(100 * AudioManager::GetAudioRegulator());
}

void Enemy::SetStartingNode()
{	
	/*if (startingNodePos == sf::Vector2f{0, 0})
	{
		for (auto node = nodesGrid->GetNodesGrid().begin(); node != nodesGrid->GetNodesGrid().end(); ++node)
		{
			if (this->bounds.intersects(node->second->Graphic().getGlobalBounds()))
			{
				pathfinder->SetStartingNode(node->second->GetCoordinates());
			}
		}
	}	*/
}

void Enemy::FindPath()
{
	path.clear();
	path = pathfinder->GetNewPath();

}

void Enemy::FollowPath(float deltaTime)
{	
	/*sf::Vector2f startPosition = sprite.getPosition();
	sf::Vector2f endPosition = path[pathPosIndex]->Graphic().getPosition();
	
	direction = endPosition - startPosition;

	float distanceToObjective = std::sqrt(std::pow(endPosition.x - startPosition.x, 2) +
		std::pow(endPosition.y - startPosition.y, 2));
	if (distanceToObjective > 0)
	{
		direction /= distanceToObjective;
	}

	newPosition = sprite.getPosition() + direction * speed * deltaTime;

	sprite.setPosition(newPosition);	

	pathTimer += deltaTime;

	if (pathTimer >= 10)
	{
		if (pathPosIndex < path.size() - 1)
		{
			pathPosIndex++;

		}

		pathTimer -= 0;
	}*/

	//float travelPercent = 0.0f;
	//sf::Vector2f startPosition;
	//sf::Vector2f endPosition;

	//// En tu función de actualización
	//if (travelPercent < 1.0f)
	//{
	//	travelPercent += deltaTime * speed;

	//	if (travelPercent > 1.0f) {
	//		travelPercent = 1.0f;
	//	}

	//	sprite.setPosition(Lerp(startPosition, endPosition, travelPercent));
	//}
	//else
	//{
	//	// Mueve al siguiente punto de la ruta
	//	if (currentIndex < path.size())
	//	{
	//		startPosition = sprite.getPosition();
	//		endPosition = path[currentIndex]->Graphic().getPosition();
	//		currentIndex++;
	//		travelPercent = 0.0f; // Reinicia el porcentaje para el nuevo segmento
	//	}
	//}

	//for (int i = 0; i < path.size(); i++)
	//{
	//	sf::Vector2f startPosition = sprite.getPosition();
	//	sf::Vector2f endPosition = path[i]->Graphic().getPosition();
	//	float travelPercent = 0.0f;

	//	while (travelPercent < 1.0f)
	//	{
	//		travelPercent += deltaTime * speed;

	//		if (travelPercent > 1.0f)
	//			travelPercent = 1.0f;

	//		sprite.setPosition(Lerp(startPosition, endPosition, travelPercent));

	//		while (pathTimer < 2)
	//		{
	//			pathTimer += deltaTime;
	//		}
	//	}
	//	
	//}

	//static int currentIndex = 0; // Índice del camino actual
	//static float travelPercent = 0.0f; // Porcentaje de viaje
	//static float pathTimer = 0.0f; // Temporizador para el retraso entre segmentos
	//static bool isMoving = false; // Bandera para controlar el movimiento
	//const float pathDelay = 2.0f; // Tiempo de espera entre movimientos

	//// Si estamos moviendo, actualizamos la posición
	//if (isMoving) {
	//	travelPercent += deltaTime * speed; // Incrementa el porcentaje de viaje

	//	// Limita travelPercent a un máximo de 1.0
	//	if (travelPercent >= 1.0f) {
	//		travelPercent = 1.0f; // Asegúrate de que no supere 1.0
	//		currentIndex++; // Avanza al siguiente punto en el path
	//		isMoving = false; // Detén el movimiento
	//		pathTimer = 0.0f; // Reinicia el temporizador
	//	}

	//	// Actualiza la posición del sprite
	//	if (currentIndex < path.size()) {
	//		sf::Vector2f startPosition = sprite.getPosition();
	//		sf::Vector2f endPosition = path[currentIndex]->Graphic().getPosition();
	//		sprite.setPosition(Lerp(startPosition, endPosition, travelPercent));
	//	}
	//}
	//else {
	//	// Si no estamos moviendo, maneja el temporizador
	//	pathTimer += deltaTime;

	//	// Cuando se acaba el temporizador, comienza el movimiento
	//	if (pathTimer >= pathDelay && currentIndex < path.size()) {
	//		isMoving = true; // Comienza el movimiento
	//		travelPercent = 0.0f; // Reinicia el porcentaje
	//	}
	//}

	//// Si hemos llegado al final del path, reinicia o haz algo apropiado
	//if (currentIndex >= path.size()) {
	//	currentIndex = 0; // O cualquier lógica que necesites
	//	isMoving = false; // Detén el movimiento
	//}

		
}
	

sf::FloatRect Enemy::GetBounds()
{
	return sprite.getGlobalBounds();
}

void Enemy::EnemyDirection()
{
	if (!isAttackingPlayer)
	{
		if (sprite.getPosition().x > 600)
		{
			SetCurrentAnimation("leftWalk");
		}
		else
		{
			SetCurrentAnimation("rightWalk");
		}
	}
	else
	{
		sf::Vector2f relativePosition = this->playerPos - sprite.getPosition();

		if (relativePosition.x < 0)
		{
			SetCurrentAnimation("leftWalk");
		}
		else
		{
			SetCurrentAnimation("rightWalk");
		}
	}



}

void Enemy::Attack(Fence* fence, float deltaTime)
{
	//if (!attackZombieAdded)
	//{
	//	if (attackingZombies < 4)
	//		attackingZombies++;

	//	attackZombieAdded = true;
	//}	

	fenceObjective = fence;

	if (!isAttackingCar)
	{
		if (sprite.getPosition().x > 600)
		{
			SetCurrentAnimation("leftAttack");
		}
		else
		{
			SetCurrentAnimation("rightAttack");
		}
	}
	
	attackTimer += deltaTime;

	if (attackTimer >= attackDelay)
	{
		fence->ReceiveDamage(damage);
		attackTimer -= attackDelay;
	}

	/*if (zombieHittingSound.getStatus() == sf::SoundSource::Stopped)
		zombieHittingSound.play();*/

	/*if (attackingZombies == 1)
	{
		
	}*/
	//else if (attackingZombies == 2)
	//{
	//	if (zombieHittingTwoSound.getStatus() == sf::SoundSource::Stopped)
	//		zombieHittingTwoSound.play();
	//}
	//else if (attackingZombies == 3)
	//{
	//	if (zombieHittingThreeSound.getStatus() == sf::SoundSource::Stopped)
	//		zombieHittingThreeSound.play();
	//}
	//else if (attackingZombies == 4)
	//{
	//	if (zombieHittingFourSound.getStatus() == sf::SoundSource::Stopped)
	//		zombieHittingFourSound.play();
	//}
		
}

void Enemy::Attack(House* house, float deltaTime)
{
	//if (!attackZombieAdded)
	//{
	//	if (attackingZombies < 4)
	//		attackingZombies++;

	//	attackZombieAdded = true;
	//}

	if (sprite.getPosition().x > 600)
	{
		SetCurrentAnimation("leftAttack");
	}
	else
	{
		SetCurrentAnimation("rightAttack");
	}

	attackTimer += deltaTime;

	if (attackTimer >= attackDelay)
	{
		house->ReceiveDamage(damage);
		attackTimer -= attackDelay;
	}

	//if (zombieHittingSound.getStatus() == sf::SoundSource::Stopped)
	//	zombieHittingSound.play();

	/*if (attackingZombies == 1)
	{
		
	}*/
//	else if (attackingZombies == 2)
//	{
//		if (zombieHittingTwoSound.getStatus() == sf::SoundSource::Stopped)
//			zombieHittingTwoSound.play();
//	}
//	else if (attackingZombies == 3)
//	{
//		if (zombieHittingThreeSound.getStatus() == sf::SoundSource::Stopped)
//			zombieHittingThreeSound.play();
//	}
//	else if (attackingZombies == 4)
//	{
//		if (zombieHittingFourSound.getStatus() == sf::SoundSource::Stopped)
//			zombieHittingFourSound.play();
//	}
}

void Enemy::Attack(Car* car, float deltaTime)
{
	/*if (!attackZombieAdded)
	{
		if (attackingZombies < 4)
			attackingZombies++;

		attackZombieAdded = true;
	}*/

	if (sprite.getPosition().x > 430)
	{
		SetCurrentAnimation("leftAttack");
	}
	else
	{
		SetCurrentAnimation("rightAttack");
	}

	attackTimer += deltaTime;

	if (attackTimer >= attackDelay)
	{
		car->ReceiveDamage(damage);
		attackTimer -= attackDelay;
	}

	if (car->GetHealthBar()->GetCurrentHealth() <= 0)
	{
		/*if (isAttackingCar)
		{
			attackingZombies = 0;
			attackZombieAdded = false;
		}*/

		isAttackingCar = false;
		car->SetIsDestroyed(true);

	}

	/*if (zombieHittingSound.getStatus() == sf::SoundSource::Stopped)
		zombieHittingSound.play();*/

	//if (attackingZombies == 1)
	//{
	//	
	//}
	//else if (attackingZombies == 2)
	//{
	//	if (zombieHittingTwoSound.getStatus() == sf::SoundSource::Stopped)
	//		zombieHittingTwoSound.play();
	//}
	//else if (attackingZombies == 3)
	//{
	//	if (zombieHittingThreeSound.getStatus() == sf::SoundSource::Stopped)
	//		zombieHittingThreeSound.play();
	//}
	//else if (attackingZombies == 4)
	//{
	//	if (zombieHittingFourSound.getStatus() == sf::SoundSource::Stopped)
	//		zombieHittingFourSound.play();
	//}
}

void Enemy::TakeDamage(float damage)
{
	health -= damage;


	if(zombieHurtSound.getStatus() == sf::SoundSource::Stopped)
		zombieHurtSound.play();

	if (health <= 0)	
		Die();
	
}

void Enemy::Die()
{
	if (!isAlive) return;

	/*if(attackingZombies > 0)
		attackingZombies--;*/

	SetAnimationFrameSize(deathAnimationFrameSize);

	if (!isAttackingPlayer)
	{
		if (sprite.getPosition().x > 600)
		{
			SetCurrentAnimation("leftDeath");
		}
		else
		{
			SetCurrentAnimation("rightDeath");
		}
	}
	else
	{
		sf::Vector2f relativePosition = this->playerPos - sprite.getPosition();

		if (relativePosition.x < 0)
		{
			SetCurrentAnimation("leftDeath");
		}
		else
		{
			SetCurrentAnimation("rightDeath");
		}
	}

	Player::AddScore(25);
	isAlive = false;
}

void Enemy::DeathTimer(float deltaTime)
{
	if (!isAlive)
	{
		deathTimer += deltaTime;

		if (deathTimer >= 4)
		{
			isActive = false;
			health = RandomNum::RandomRange(minHealth, maxHealth);
			healthBar->SetMaxHealth(health);
			isAlive = true;
			deathTimer = 0;
			SetAnimationFrameSize(animationFrameSize);
			isAttackingPlayer = false;
			isAttackingFence = false;	
			isAttackingCar = false;
			isAttackingPlayer = false;
			isAttackingHouse = false;
		}
	}
}

float Enemy::GetDistanceToObjective()
{
	float distance = std::sqrt(std::pow( objective.x - sprite.getPosition().x, 2) +
		std::pow(objective.y - sprite.getPosition().y, 2));

	return distance;

}

void Enemy::HealthBarAppearance()
{
	if (healthBar->GetCurrentHealth() <= 0)
	{
		healthBar->SetCurrentAnimation("emptyBar");
	}
	else if (healthBar->GetCurrentHealth() <= healthBar->GetMaxHealth() * 0.25f)
	{
		healthBar->SetCurrentAnimation("oneQuarterBar");
	}
	else if (healthBar->GetCurrentHealth() <= healthBar->GetMaxHealth() * 0.5f)
	{
		healthBar->SetCurrentAnimation("halfBar");
	}
	else if (healthBar->GetCurrentHealth() <= healthBar->GetMaxHealth() * 0.75f)
	{
		healthBar->SetCurrentAnimation("threeQuarterBar");
	}
	else
	{
		healthBar->SetCurrentAnimation("fullBar");
	}
}

void Enemy::ResetEnemy()
{
	isActive = false;
	health = RandomNum::RandomRange(minHealth, maxHealth);
	healthBar->SetMaxHealth(health);
	isAlive = true;
	deathTimer = 0;
	SetAnimationFrameSize(animationFrameSize);
	isAttackingPlayer = false;
	isAttackingFence = false;
	isAttackingCar = false;
	isAttackingPlayer = false;
	isAttackingHouse = false;
}