#pragma once
#include "../AnimatedEntity.h"
#include "../../Utilities/VectorUtility.h"
#include "../Enviroment/Fence.h"
#include "../HealthBar/HealthBar.h"
#include "../../BreadthFirstSearch/PathFinder.h"
#include "../Enviroment/House.h"
#include "../Enviroment/Car.h"
#include "../Player/Player.h"
#include "../../Audio/AudioManager.h"

class Enemy : public AnimatedEntity
{
private:

	sf::SoundBuffer zombieHurtBuffer;
	sf::Sound zombieHurtSound;

	GridManager* nodesGrid;
	PathFinder* pathfinder;	
	std::vector <Node*> path;

	sf::Vector2f startingNodePos;
	int pathPosIndex = 0;
	float pathTimer;
	
	float collisionRadius = 30.0f;
	bool isActive;
	bool isAlive;

	bool isAttackingFence;
	bool isAttackingHouse;
	bool isAttackingCar;
	bool isAttackingPlayer;
	
	float minHealth;
	float maxHealth;
	float health;
	HealthBar* healthBar;
	float speed;
	float regularSpeed;
	float speedNearPlayer;
	float damage;
	float attackDelay;
	float attackTimer;
	float deathTimer;
	sf::Vector2i animationFrameSize;
	sf::Vector2i deathAnimationFrameSize;
	Fence* fenceObjective;
	sf::Vector2f objective;
	sf::Vector2f playerPos;
	sf::Vector2f newPosition;
	sf::Vector2f direction;

	void EnemyDirection();
	void Die();
	void DeathTimer(float deltaTime);
	float GetDistanceToObjective();

	void SetStartingNode();
	void FindPath();
	void FollowPath(float deltaTime);

	void HealthBarAppearance();

public:
	Enemy(GridManager* nodesGrid, PathFinder* pathfinder, sf::Vector2f scale, float minHealth, float maxHealth,
		float regularSpeed, float speedNearPlayer, float damage, float attackDelay, float animationSpeed,
		float deathAnimationSpeed, sf::Vector2i animationFrameSize, sf::Vector2i deathAnimationFrameSize,
		std::string imageFilePath, sf::Vector2i spriteSheetSize);
	void Update(float deltaTime, sf::Vector2f playerPos);
	void SetIsAttackingFence(bool value) {	isAttackingFence = value; }
	void SetIsAttackingHouse(bool value) {	isAttackingHouse = value; }
	void SetIsAttackingCar(bool value) {	isAttackingCar = value; }
	bool GetIsAlive() { return isAlive; }
	float GetSpeed() { return speed; }
	void SetIsActive(bool isActive) { this->isActive = isActive; }
	bool GetIsActive() { return isActive; }
	HealthBar* GetHealthBar() { return healthBar; }
	sf::FloatRect GetBounds() override;
	bool GetIsAttackingPlayer() { return isAttackingPlayer; }
	bool GetIsAttackingFence() { return isAttackingFence; }
	bool GetIsAttackingCar() { return isAttackingCar; }
	bool GetIsAttackingHouse() { return isAttackingHouse; }
	float GetCollissionRadius() { return collisionRadius; }
	sf::Vector2f GetDirection() { return direction; }
	sf::Vector2f GetNewPosition() { return newPosition; }
	sf::Vector2f GetStartingNodePos() { return startingNodePos; }
	void SetNewPosition(sf::Vector2f newPosition) { this->newPosition = newPosition; }
	void SetIsAttackingPlayer(bool value) { isAttackingPlayer = value; }
	void Attack(Fence* fence, float deltaTime);
	void Attack(House* house, float deltaTime);
	void Attack(Car* car, float deltaTime);
	void TakeDamage(float damage);
	void EnemyMovement(float deltaTime);

	void UpdateSound();

	void ResetEnemy();

	void Destroy();
};
