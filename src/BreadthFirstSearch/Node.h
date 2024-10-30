#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "vector"
#include "../Entities/Entity.h"

class Node 
{
private:

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f coordinates;
	bool isWalkable;
	bool isObstacle;
	bool isExplored;
	bool isPath;
	bool isObjective;
	Node* connectedTo;
	sf::Color walkableColor;
	sf::Color blockedColor;
	sf::Color pathColor;
	sf::Color exploredColor;
	sf::Color objectiveColor;


public:
	Node();
	void Update(std::vector<Entity*> entities, Node* node);
	sf::Sprite& Graphic() { return sprite; }  //Simbolo & es pasaje por referencia
	void SetNodeState(std::vector<Entity*> entities, Node* node);
	void SetCoordinates(sf::Vector2f coordinates) { this->coordinates = coordinates; }
	sf::Vector2f GetCoordinates() { return coordinates; }
	void SetIsWalkable(bool isWalkable) { this->isWalkable = isWalkable; }
	bool GetIsWalkable() { return isWalkable; }
	void SetIsObstacle(bool isObstacle) { this->isObstacle = isObstacle; }
	void SetIsExplored(bool isExplored) { this->isExplored = isExplored; }
	void SetIsPath(bool isPath) { this->isPath = isPath; }
	void SetIsObjective(bool isObjective) { this->isObjective = isObjective; }
	bool GetIsObjective() { return isObjective; }
	void SetParentNode(Node* node) { connectedTo = node; }
	Node* GetParentNode() { return connectedTo; }
	void CheckObjective(std::vector<Entity*> entities, Node* node);
	void SetNodesColor();
};

