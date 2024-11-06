#include "DayTasksManager.h"

bool DayTasksManager::scavengeResultsOpen;

DayTasksManager::DayTasksManager(std::vector<Fence*> fences, Car* car, House* house)
{
	this->fences = fences;
	this->car = car;
	this->house = house;

	std::string backgroundImageFilePath = "res\\textures\\time\\HoursInterface.png";
	sf::Vector2i backgroundSpriteSheetSize = { 168, 107 };
	background = new Entity(backgroundImageFilePath, backgroundSpriteSheetSize);

	background->Graphic().setOrigin(84, 53);
	background->Graphic().setPosition(600, 440);
	background->Graphic().setScale({ 2, 2 });

	std::string buttonCloseImageFilePath = "res\\textures\\time\\ButtonClose.png";
	sf::Vector2i buttonCloseSpriteSheetSize = { 10, 10 };
	buttonClose = new Entity(buttonCloseImageFilePath, buttonCloseSpriteSheetSize);

	buttonClose->Graphic().setOrigin(5, 5);
	buttonClose->Graphic().setPosition(730, 365);
	buttonClose->Graphic().setScale({ 2, 2 });

	buttonClose->SetTag(Tag::CloseScavengeResults);

	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Pixel.otf";
	font->loadFromFile(fontPath);

	sf::Color* color = new sf::Color(88, 83, 74, 255);

	resourcesFoundText = new sf::Text("TEST", *font, 12);
	resourcesFoundText->setPosition(530, 420);
	resourcesFoundText->setFillColor(*color);
		
	resourcesText = new sf::Text("", *font, 12);
	resourcesText->setPosition(555, 455);
	resourcesText->setFillColor(*color);

	weaponFindChance = 10;
}

void DayTasksManager::Update()
{
	if(!scavengeResultsOpen)
		buttonClose->Graphic().setPosition(1330, 365);
	else
		buttonClose->Graphic().setPosition(730, 365);

	resourcesFoundText->setString("Scrap found: " + std::to_string(resourcesFound));
	resourcesText->setString("Scrap: " + std::to_string(Player::GetResources()));
}


void DayTasksManager::RepairFences(int hours)
{
	hours *= 2;

	std::sort(fences.begin(), fences.end(), [] (auto* a, auto* b) { return a->GetHealth() < b->GetHealth(); });

	for (auto& fence : fences)
	{
		if (hours <= 0) break;

		if (fence->GetHealth() < fence->GetMaxHealth())
		{
			fence->RepairFence();
			hours--;
		}
	}	
}

void DayTasksManager::RepairCar(int hours)
{
	for (int i = 0; i < hours; i++)
	{
		if (car->GetHealth() < car->GetMaxHealth())		
			car->RepairCar();		
	}
}

void DayTasksManager::RepairHouse(int hours)
{
	for (int i = 0; i < hours; i++)
	{
		if (house->GetHealth() < house->GetMaxHealth())
			house->RepairHouse();
	}
}

void DayTasksManager::Scavenge(int hours)
{
	int minScrap = 50;
	int maxScrap = 150;

	resourcesFound = RandomNum::RandomRange(50, 150);
	resourcesFound *= hours;
	
	if (car->GetHealth() <= 0)
	{
		resourcesFound *= 0.1;
	}
	else if (car->GetHealth() <= (car->GetMaxHealth() * 0.25))
	{
		resourcesFound *= 0.25;
	}
	else if (car->GetHealth() <= (car->GetMaxHealth() * 0.5))
	{
		resourcesFound *= 0.5;
	}
	else if (car->GetHealth() <= (car->GetMaxHealth() * 0.75))
	{
		resourcesFound *= 0.75;
	}

	Player::AddResources(resourcesFound);

	int randomNum = RandomNum::RandomRange(0, 100);

	if (hours <= 2)
		weaponFindChance = 100;
	else if (hours <= 4)
		weaponFindChance = 15;
	else if (hours <= 6)
		weaponFindChance = 20;
	else if (hours <= 8)
		weaponFindChance = 25;
	else if (hours <= 10)
		weaponFindChance = 30;
	else if (hours <= 12)
		weaponFindChance = 35;
	
	if (randomNum <= weaponFindChance)
	{
		if (!Player::GetHasShotgun())
			Player::SetHasShotgun(true);
		else 
			Player::SetHasUzi(true);
	}
}

void DayTasksManager::Sleep(int hours)
{
	Player::AddHoursSlept(hours);
}


