#include "GridManager.h"

GridManager::GridManager()
{
	float nodeXPos = 336;	
	float nodeYPos = 248;
	sf::Vector2f coordinates(nodeXPos, nodeYPos);
	int nodeIndex = 0;


	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 8; j++)
		{			
			nodesGrid.insert({ sf::Vector2f{nodeXPos, nodeYPos}, new Node() });
			
			auto node = nodesGrid.find(coordinates);
			if (node != nodesGrid.end() && node->second != nullptr)
			{
				node->second->Graphic().setPosition(coordinates);
				node->second->SetCoordinates(coordinates);
			}

			nodeIndex++;
			nodeYPos += 48;

			coordinates = { nodeXPos, nodeYPos };

		}

		nodeXPos += 48;
		nodeYPos = 248;

		coordinates = { nodeXPos, nodeYPos };
	}


	
}

Node* GridManager::GetNode(sf::Vector2f coordinates)
{
	auto node = nodesGrid.find(coordinates);

	if (node != nodesGrid.end())
	{
		return node->second;
	}

	
}

void GridManager::ResetNodes()
{
	for (auto node = nodesGrid.begin(); node != nodesGrid.end(); ++node)
	{
		node->second->SetParentNode(nullptr);
		node->second->SetIsExplored(false);
		node->second->SetIsPath(false);
		node->second->SetIsObjective(false);

	}
}


