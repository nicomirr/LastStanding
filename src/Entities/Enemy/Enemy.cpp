#include "Enemy.h"




Enemy::Enemy(GridManager* nodesGrid, PathFinder* pathfinder, sf::Vector2f scale, float minHealth, float maxHealth, float regularSpeed, 
	float speedNearPlayer,	float damage, float attackDelay, float animationSpeed, float deathAnimationSpeed, sf::Vector2i animationFrameSize,
	sf::Vector2i deathAnimationFrameSize, std::string imageFilePath, sf::Vector2i spriteSheetSize) 
	: AnimatedEntity(animationFrameSize, imageFilePath, spriteSheetSize)
{

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

}

void Enemy::Attack(House* house, float deltaTime)
{
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
}

void Enemy::Attack(Car* car, float deltaTime)
{
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
		isAttackingCar = false;
		car->SetIsDestroyed(true);
	}
}

void Enemy::TakeDamage(float damage)
{
	health -= damage;

	if (health <= 0)	
		Die();
	
}

void Enemy::Die()
{
	if (!isAlive) return;

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