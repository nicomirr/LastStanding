#include "PathFinder.h"

PathFinder::PathFinder()
{
}

PathFinder::PathFinder(GridManager* nodesGrid)
{
	sf::Vector2f right = { 48,0 };
	sf::Vector2f left = { -48,0 };
	sf::Vector2f up = { 0,-48 };
	sf::Vector2f down = { 0, 48 };

	this->nodesGrid = nodesGrid;

	directions = { right, left, up, down };

	destinationCoordinates = { 0, 0 };


	startCoordinates = { 336, 248 };
	destinationCoordinates = { 480, 344 };

	startNode = nodesGrid->GetNode(startCoordinates);
	destinationNode = nodesGrid->GetNode(destinationCoordinates);
	
	newDestinationCoordinates = destinationCoordinates;
		
}

void PathFinder::Update()
{	

	for (auto node = nodesGrid->GetNodesGrid().begin(); node != nodesGrid->GetNodesGrid().end(); ++node)
	{
		if (node->second->GetIsObjective())
		{						
			newDestinationCoordinates = node->second->GetCoordinates();	
			break;
		}
	}

	if (destinationCoordinates != newDestinationCoordinates)
	{	
						
		GetNewPath();
		return;
	}

}

void PathFinder::SetStartingNode(sf::Vector2f coordinates)
{
	startCoordinates = coordinates;
	startNode = nodesGrid->GetNode(coordinates);
}

void PathFinder::ExploreNeighbors()
{
	std::vector<Node*> neighbors;

	for (int i = 0; i < directions.size(); i++)
	{
		sf::Vector2f neighborCoords = currentSearchNode->GetCoordinates() + directions[i];


		auto node = nodesGrid->GetNodesGrid().find(neighborCoords);

		if (node != nodesGrid->GetNodesGrid().end())
		{
			neighbors.push_back(node->second);		
		}

	}

	for (int i = 0; i < neighbors.size(); i++)
	{	
		auto node = reached.find(neighbors[i]->GetCoordinates());

		if (node == reached.end() && neighbors[i]->GetIsWalkable())
		{
			neighbors[i]->SetParentNode(currentSearchNode);
			reached.insert({ neighbors[i]->GetCoordinates(), neighbors[i]});
			frontier.push(neighbors[i]);
		}
	}
}

std::vector<Node*> PathFinder::GetNewPath()
{
	nodesGrid->ResetNodes();
	BreadthFirstSearch();
	return BuildPath();
}

void PathFinder::BreadthFirstSearch()
{
	while(!frontier.empty())
	{
		frontier.pop();
	}

	reached.clear();

	bool isRunning = true;

	frontier.push(startNode);
	reached.insert({ startCoordinates, startNode });

	while (frontier.size() > 0 && isRunning)
	{
		currentSearchNode = frontier.front();
		frontier.pop();
		currentSearchNode->SetIsExplored(true);

		ExploreNeighbors();

		if (currentSearchNode->GetCoordinates() == destinationCoordinates)
		{			
			isRunning = false;
		}
	}
	

}

std::vector<Node*> PathFinder::BuildPath()
{
	destinationCoordinates = newDestinationCoordinates;
	destinationNode = nodesGrid->GetNode(destinationCoordinates);

	std::vector<Node*> path;
	Node* currentNode = destinationNode;

	path.push_back(currentNode);
			
	currentNode->SetIsPath(true);

	while (currentNode->GetParentNode() != nullptr)
	{
		currentNode = currentNode->GetParentNode();
		path.push_back(currentNode);
		currentNode->SetIsPath(true);
	}

	std::reverse(path.begin(), path.end());

	return path;
}


