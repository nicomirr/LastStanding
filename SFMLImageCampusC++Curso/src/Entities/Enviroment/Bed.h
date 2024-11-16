#pragma once
#include "../Entity.h"
#include "../../Collisions/CollisionHandler.h"
#include "../Time/HoursInterface.h"

class Bed : public Entity
{
private:
	sf::FloatRect GetBounds() override;	
	static HoursInterface* hoursInterface;

public:
	Bed(std::string imageFilePath, sf::Vector2i spriteSheetSize);
	static HoursInterface* GetHoursInterface() { return hoursInterface; }

	void Destroy();
};

