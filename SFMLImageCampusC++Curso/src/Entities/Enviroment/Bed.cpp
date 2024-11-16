#include "Bed.h"

HoursInterface* Bed::hoursInterface;

Bed::Bed(std::string imageFilePath, sf::Vector2i spriteSheetSize) : Entity(imageFilePath, spriteSheetSize)
{
	hoursInterface = new HoursInterface();

	hoursInterface->SetInterfaceText("How much time should \n		  I sleep?");
	hoursInterface->GetInterfaceText()->setPosition(495, 390);

	CollisionHandler::AddCollision(hoursInterface->GetButtonClose());
	CollisionHandler::AddCollision(hoursInterface->GetButtonRight());
	CollisionHandler::AddCollision(hoursInterface->GetButtonLeft());
	
	hoursInterface->GetButtonOk()->SetTag(Tag::OkHoursButtonSleep);
	CollisionHandler::AddCollision(hoursInterface->GetButtonOk());
}

sf::FloatRect Bed::GetBounds()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();

	bounds.height *= 0.7;

	return bounds;
}

void Bed::Destroy()
{
	if (hoursInterface != nullptr)
	{
		delete hoursInterface;
		hoursInterface = nullptr;
	}
}
