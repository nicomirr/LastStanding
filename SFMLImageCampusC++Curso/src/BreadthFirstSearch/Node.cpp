#include "Node.h"

Node::Node()
{
	sf::Vector2i spriteSheetSize = { 48, 48 };
	std::string imageFilePath = "res\\textures\\node\\Node.png";

	sf::IntRect area(0, 0, spriteSheetSize.x, spriteSheetSize.y);

	texture.loadFromFile(imageFilePath, area);
	sprite.setTexture(texture, false);

	isWalkable = true;
	isObstacle = false;
	isExplored = false;
	isPath = false;
	isObjective = false;

	walkableColor = { 255, 255, 255, 255 };
	blockedColor = { 255, 0, 0, 255 };
	pathColor = { 0, 0, 255, 255 };
	exploredColor = { 0, 255, 255, 255 };
	objectiveColor = { 0, 255, 0, 255 };
}

void Node::SetNodeState(std::vector<Entity*> entities, Node* node)
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->GetTag() == Tag::Car || entities[i]->GetTag() == Tag::House)
		{
			if (entities[i]->GetBounds().intersects(node->Graphic().getGlobalBounds()))
			{
				node->SetIsWalkable(false);
				node->SetIsObstacle(true);
			}
		}
	}
}

void Node::Update(std::vector<Entity*> entities, Node* node)
{	
	isObjective = false;
	if (isObstacle)
		isWalkable = false;

	CheckObjective(entities, node);

	SetNodesColor();
}

void Node::CheckObjective(std::vector<Entity*> entities, Node* node)
{
	for (int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->GetTag() == Tag::Player)
		{
			if (entities[i]->GetBounds().intersects(node->Graphic().getGlobalBounds()))
			{
				node->SetIsWalkable(true);
				isObjective = true;		
				break;
			}
		}
	}
}

void Node::SetNodesColor()
{
	if (isObjective)
		sprite.setColor(objectiveColor);
	else if (isPath)
		sprite.setColor(pathColor);
	else if (isExplored)
		sprite.setColor(exploredColor);
	else if (isWalkable)
		sprite.setColor(walkableColor);
	else
		sprite.setColor(blockedColor);
	
}