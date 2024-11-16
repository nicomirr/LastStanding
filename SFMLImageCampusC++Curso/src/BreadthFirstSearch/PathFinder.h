#pragma once

#include <queue>
#include "Node.h"
#include "GridManager.h"

class PathFinder
{
private:
	GridManager* nodesGrid;
	std::vector<sf::Vector2f> directions;
	
	sf::Vector2f startCoordinates;
	sf::Vector2f destinationCoordinates;
	sf::Vector2f newDestinationCoordinates;
	
	Node* startNode;
	Node* destinationNode;
	Node* currentSearchNode;

	std::queue<Node*> frontier;
	std::unordered_map<sf::Vector2f, Node*, Vector2fHash, Vector2fEqual> reached;
	

public:
	PathFinder();
	PathFinder(GridManager* nodesGrid);
	void Update();
	void SetCurrentSearchNode(Node* node) { currentSearchNode = node; }
	void SetStartingNode(sf::Vector2f coordinates);
	void ExploreNeighbors();
	void BreadthFirstSearch();
	std::vector<Node*> BuildPath();
	std::vector<Node*> GetNewPath();
};

