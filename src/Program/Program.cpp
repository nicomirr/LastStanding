#include "Program.h"

sf::Vector2i Program::mousePosition;

Program::Program()
{
	isProgramRunning = true;
}

void Program::Run()
{
	Initialize();
	ProgramLoop();
	DeInitialize();
}

void Program::Initialize()
{
	srand(time(NULL));

	CreateWindow();
	
	CreateSceneManager();
	
	SetCursorAppearance();

	CreateWeapons();

	CreatePlayer();

	CreateHUD();
	
	CreateNightSky();

	CreateClock();

	nodesGrid = new GridManager();
	pathfinder = new PathFinder(nodesGrid);
	//ARREGLAR DEPENDENCIA DE NODOS ANTES DE ENCAPSULAR
	enemySpawner = new EnemySpawner(nodesGrid, pathfinder, sceneManager);
			
	CreatePlayerBaseCollider();
		
	CreateOutsideFloor();

	CreateFences();

	CreateHouse();

	CreateCar();

	CreateInteriorFloor();

	CreateInteriorWall();

	CreateInteriorLimits();

	CreateBed();

	CreateRadio();

	CreateChairs();

	CreateTable();

	CreateDoorColliderInside();

	CreateBedCollider();

	CreateRadioCollider();

	CreateDoorColliderOutside();


	for (auto node = nodesGrid->GetNodesGrid().begin(); node != nodesGrid->GetNodesGrid().end(); ++node)
	{
		node->second->SetNodeState(CollisionHandler::GetEntities(), node->second);
	}

	for (auto node = nodesGrid->GetNodesGrid().begin(); node != nodesGrid->GetNodesGrid().end(); ++node)
	{
		node->second->Update(CollisionHandler::GetEntities(), node->second);
	}


	//pathfinder->GetNewPath();

}

void Program::DeInitialize()
{
	if (window != nullptr)
	{
		delete window;
		window = nullptr;
	}

	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
}



void Program::ProgramLoop()
{
	while (window->isOpen())
	{
		Input();
		Update();
		Draw();
	}
}



void Program::Input()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		window->setMouseCursor(cursor);

		player->Input(event);

		sf::Mouse mouse;
	}
}

void Program::Update()
{	
	mousePosition = sf::Mouse::getPosition(*window);
	deltaTime = clock.restart().asSeconds();

	sceneManager->Update();

	if (sceneManager->GetIsNightTimeScene())
	{
		NightTimeUpdate(deltaTime);
	}
	else if (sceneManager->GetIsDayTimeScene())
	{
		DayTimeUpdate(deltaTime);
	}

	/*for (auto node = nodesGrid->GetNodesGrid().begin(); node != nodesGrid->GetNodesGrid().end(); ++node)
	{
		node->second->Update(CollisionHandler::GetEntities(), node->second);				
	}*/
		
	CollisionHandler::SolveCollisions(deltaTime, sceneManager);	

}

void Program::Draw()
{
	window->clear();
	
	float nodePosX = player->Graphic().getPosition().x + 15;
	float nodePosY = player->Graphic().getPosition().y + 25;
		
	if (sceneManager->GetIsNightTimeScene())
	{
		DrawNightTime();
	}
	else if (sceneManager->GetIsDayTimeScene())
	{
		DrawDayTime();
	}

	DrawBedHoursInterface();


	//DrawHours();

	//window->draw(baseAreaCollider->Graphic());

	//for (auto node = nodesGrid->GetNodesGrid().begin(); node != nodesGrid->GetNodesGrid().end(); ++node)
	//{
	//	window->draw(node->second->Graphic());
	//}
	

	window->display();
}



void Program::CreateWindow()
{
	windowWidth = 1200;
	windowHeight = 880;

	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Last Stand", sf::Style::Close);

	window->setFramerateLimit(60);
}

void Program::CreateSceneManager()
{
	sceneManager = new SceneManager();
}

void Program::SetCursorAppearance()
{
	cursorImageFilePath = "res\\textures\\cursor\\Cursor.png";
	cursorImage.loadFromFile(cursorImageFilePath);
	sf::Vector2u cursorHotspot({ 16,16 });

	cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), cursorHotspot);

}

void Program::CreateWeapons()
{
	float gunFireRate = 0.2f;
	float gunReloadTime = 1.0f;
	float gunCapacity = 7;
	sf::Vector2i gunAnimationFrameSize = { 8, 8 };
	std::string gunFilePath = "res\\textures\\weapons\\Gun.png";
	sf::Vector2i gunSpriteSheetSize = { 8, 32 };

	float gunBulletMinDamage = 3;
	float gunMaxBulletDamage = 6;
	float bulletSpeed = 2000.0f;
	std::string bulletFilePath = "res\\textures\\weapons\\Bullet.png";
	sf::Vector2i bulletSpriteSheetSize = { 3, 3 };
	float bulletMaxPosX = windowWidth;
	float bulletMaxPosY = windowHeight;

	gun = new Weapon(gunFireRate, gunReloadTime, gunCapacity, gunAnimationFrameSize, gunFilePath, gunSpriteSheetSize,
		gunBulletMinDamage, gunMaxBulletDamage, bulletSpeed, bulletFilePath, bulletSpriteSheetSize, bulletMaxPosX,
		bulletMaxPosY);

	gun->SetTag(Tag::Weapon);
	CollisionHandler::AddCollision(gun);
}

void Program::CreatePlayer()
{

	float playerSpeed = 100;
	sf::Vector2i playerAnimationFrameSize = { 15, 15 };
	std::string playerFilePath = "res\\textures\\player\\Player.png";
	sf::Vector2i playerSpriteSheetSize = { 44, 90 };

	player = new Player(playerSpeed, gun, windowWidth, windowHeight, playerAnimationFrameSize, playerFilePath,
		playerSpriteSheetSize);

	player->SetTag(Tag::Player);
	CollisionHandler::AddCollision(player);
}

void Program::CreateHUD()
{
	std::string hudFilePath = "res\\textures\\HUD\\HUDbarWithGun.png";
	sf::Vector2i hudSpriteSheetSize = { 1200, 191 };

	hud = new HUD(hudFilePath, hudSpriteSheetSize);
}

void Program::CreateNightSky()
{
	std::string skyNightImageFilePath = "res\\textures\\enviroment\\SkyNight.png";
	sf::Vector2i skyNightFrameSize = { 1200, 880 };
	skyNight = new Entity(skyNightImageFilePath, skyNightFrameSize);
}

void Program::CreateClock()
{
	std::string clockFilePath = "res\\textures\\HUD\\Clock.png";
	sf::Vector2i clockSpriteSheetSize = { 142, 124 };

	timeClock = new TimeClock(skyNight, clockFilePath, clockSpriteSheetSize);
}

void Program::CreatePlayerBaseCollider()
{
	std::string playerBaseColliderFilePath = "res\\textures\\playerBaseCollider\\PlayerBaseCollider.png";
	sf::Vector2i playerBaseColliderSpriteSheetSize = { 580, 350 };

	baseAreaCollider = new BaseAreaCollider(playerBaseColliderFilePath, playerBaseColliderSpriteSheetSize);
	baseAreaCollider->Graphic().setPosition({ 330, 240 });
	baseAreaCollider->SetTag(Tag::BaseArea);
	CollisionHandler::AddCollision(baseAreaCollider);
}

void Program::CreateOutsideFloor()
{
	sf::Vector2i floorFrameSize = { 48, 48 };
	std::string floorFilePath = "res\\textures\\tiles\\floors\\Floor1.png";
	sf::Vector2i floorSpriteSheetSize = { 48, 144 };
	int totalTiles = (windowWidth / 48) * ((windowHeight + 32) / 48);

	AnimationData normalFloor = { 0, 0, 1, 0 };
	AnimationData grassFloorOne = { 0, 1, 1, 0 };
	AnimationData grassFloorTwo = { 0, 2, 1, 0 };

	for (int i = 0; i < totalTiles; i++)
	{
		floor.push_back(new AnimatedEntity(floorFrameSize, floorFilePath, floorSpriteSheetSize));
	}

	int randomNum;

	for (int i = 0; i < totalTiles; i++)
	{
		floor[i]->AddAnimation("normalFloor", normalFloor);
		floor[i]->AddAnimation("grassFloorOne", grassFloorOne);
		floor[i]->AddAnimation("grassFloorTwo", grassFloorTwo);

		randomNum = rand() % 10;

		switch (randomNum)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			floor[i]->SetCurrentAnimation("normalFloor");
			break;
		case 8:
			floor[i]->SetCurrentAnimation("grassFloorOne");
			break;
		case 9:
			floor[i]->SetCurrentAnimation("grassFloorTwo");
			break;
		}

	}

	int floorXPos = 0;
	int floorYPos = 0;
	int floorIndex = 0;

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			floor[floorIndex]->Graphic().setPosition(floorXPos, floorYPos);
			floorIndex++;
			floorYPos += 48;
		}

		floorXPos += 48;
		floorYPos = 0;
	}
}

void Program::CreateFences()
{
	float fenceHealth = 100;
	sf::Vector2i fenceFrameSize = { 48, 60 };
	sf::Vector2i sideFenceFrameSize = { 12, 60 };
	sf::Vector2i doorFrameSize = { 92, 60 };
	std::string fenceFilePath = "res\\textures\\enviroment\\Fence.png";
	sf::Vector2i fenceSpriteSheetSize = { 92, 2288 };
	int fenceXPos = 300;
	int fenceYPos = 160;

	fences.push_back(new Fence(fenceHealth, "topLeftCorner", sf::Vector2f(fenceXPos + 5, fenceYPos),
		fenceFrameSize, fenceFilePath, fenceSpriteSheetSize));
	fenceXPos += 48;

	fences.push_back(new Fence(fenceHealth, "topSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos += 48;

	fences.push_back(new Fence(fenceHealth, "topSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos += 48;

	fences.push_back(new Fence(fenceHealth, "topSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos += 48;

	fences.push_back(new Fence(fenceHealth, "topSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos += 48;

	fences.push_back(new Fence(fenceHealth, "topSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos += 48;

	fences.push_back(new Fence(fenceHealth, "topSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos += 48;

	fences.push_back(new Fence(fenceHealth, "topSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos += 48;

	fences.push_back(new Fence(fenceHealth, "topSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos += 48;

	fences.push_back(new Fence(fenceHealth, "topSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos += 48;

	fences.push_back(new Fence(fenceHealth, "topSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos += 48;

	fences.push_back(new Fence(fenceHealth, "topSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos += 48;

	fences.push_back(new Fence(fenceHealth, "topSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos += 48;

	fences.push_back(new Fence(fenceHealth, "rightSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceYPos += 60;

	fences.push_back(new Fence(fenceHealth, "rightSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceYPos += 60;

	fences.push_back(new Fence(fenceHealth, "rightSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceYPos += 60;

	fences.push_back(new Fence(fenceHealth, "rightSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceYPos += 60;

	fences.push_back(new Fence(fenceHealth, "rightSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceYPos += 60;

	fences.push_back(new Fence(fenceHealth, "rightSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceYPos += 60;

	fences.push_back(new Fence(fenceHealth, "rightSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));

	fences.push_back(new Fence(fenceHealth, "rightSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceYPos += 60;

	fences.push_back(new Fence(fenceHealth, "rightSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos -= 48;

	fences.push_back(new Fence(fenceHealth, "bottomRightCorner", sf::Vector2f(fenceXPos, fenceYPos),
		fenceFrameSize, fenceFilePath, fenceSpriteSheetSize));
	fenceXPos -= 48;

	fences.push_back(new Fence(fenceHealth, "bottomSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos -= 48;

	fences.push_back(new Fence(fenceHealth, "bottomSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos -= 48;

	fences.push_back(new Fence(fenceHealth, "bottomSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos -= 48;

	fences.push_back(new Fence(fenceHealth, "bottomSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos -= 48;

	fences.push_back(new Fence(fenceHealth, "bottomSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos -= 48;

	fences.push_back(new Fence(fenceHealth, "bottomSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos -= 48;

	fences.push_back(new Fence(fenceHealth, "bottomSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos -= 48;

	fences.push_back(new Fence(fenceHealth, "bottomSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos -= 48;

	fences.push_back(new Fence(fenceHealth, "door", sf::Vector2f(fenceXPos - 42, fenceYPos + 10), doorFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos -= 92;

	fences.push_back(new Fence(fenceHealth, "bottomSide", sf::Vector2f(fenceXPos, fenceYPos), fenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceXPos -= 48;

	fences.push_back(new Fence(fenceHealth, "bottomLeftCorner", sf::Vector2f(fenceXPos, fenceYPos),
		fenceFrameSize, fenceFilePath, fenceSpriteSheetSize));
	fenceYPos -= 60;

	fences.push_back(new Fence(fenceHealth, "leftSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceYPos -= 60;

	fences.push_back(new Fence(fenceHealth, "leftSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceYPos -= 60;

	fences.push_back(new Fence(fenceHealth, "leftSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceYPos -= 60;

	fences.push_back(new Fence(fenceHealth, "leftSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceYPos -= 60;

	fences.push_back(new Fence(fenceHealth, "leftSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));
	fenceYPos -= 60;

	fences.push_back(new Fence(fenceHealth, "leftSide", sf::Vector2f(fenceXPos, fenceYPos), sideFenceFrameSize,
		fenceFilePath, fenceSpriteSheetSize));

	for (int i = 0; i < fences.size(); i++)
	{
		fences[i]->SetTag(Tag::Fence);
		CollisionHandler::AddCollision(fences[i]);
	}
}

void Program::CreateHouse()
{
	sf::Vector2f housePos = { 600,280 };
	sf::Vector2i houseAnimationFrameSize = { 227, 139 };
	std::string houseFilePath = "res\\textures\\enviroment\\House.png";
	sf::Vector2i houseSpriteSheetSize = { 227,417 };

	house = new House(housePos, houseAnimationFrameSize, houseFilePath, houseSpriteSheetSize);
	house->SetTag(Tag::House);
	CollisionHandler::AddCollision(house);
}

void Program::CreateCar()
{
	sf::Vector2f carPos = { 418, 425 };
	sf::Vector2i carAnimationFrameSize = { 70, 122 };
	std::string carFilePath = "res\\textures\\enviroment\\Car.png";
	sf::Vector2i carSpriteSheetSize = { 70, 366 };


	car = new Car(carPos, carAnimationFrameSize, carFilePath, carSpriteSheetSize);
	car->SetTag(Tag::Car);
	CollisionHandler::AddCollision(car);
}

void Program::CreateDoorColliderOutside()
{
	std::string doorColliderFilePath = "res\\textures\\enviroment\\interior\\Collider.png";
	sf::Vector2i doorColliderSpriteSheetSize = { 32, 32 };

	doorColliderOutside = new Entity(doorColliderFilePath, doorColliderSpriteSheetSize);

	doorColliderOutside->Graphic().setPosition(771, 395);
	doorColliderOutside->Graphic().setOrigin(41, 25);
	doorColliderOutside->Graphic().scale(sf::Vector2f(1.2f, 1.0f));

	doorColliderOutside->SetTag(Tag::DoorColliderOutside);

	sf::FloatRect doorColliderBounds = doorColliderOutside->Graphic().getGlobalBounds();

	doorColliderOutside->SetBounds(doorColliderBounds);

	CollisionHandler::AddCollision(doorColliderOutside);
}

void Program::CreateInteriorFloor()
{
	std::string interiorFloorFilePath = "res\\textures\\enviroment\\interior\\WoodenFloor.png";
	sf::Vector2i interiorFloorSpriteSheetSize = { 342, 251 };

	interiorFloor = new Entity(interiorFloorFilePath, interiorFloorSpriteSheetSize);

	interiorFloor->Graphic().setOrigin(171, 125);
	interiorFloor->Graphic().setPosition(sf::Vector2f(600, 440));
	interiorFloor->Graphic().scale(sf::Vector2f(1.3f, 1.0f));
}

void Program::CreateInteriorWall()
{
	std::string interiorUpWallFilePath = "res\\textures\\enviroment\\interior\\WallUp.png";
	sf::Vector2i interiorUpWallSpriteSheetSize = { 345, 80 };

	interiorUpWall = new Wall(interiorUpWallFilePath, interiorUpWallSpriteSheetSize);

	interiorUpWall->Graphic().setPosition(sf::Vector2f(600, 310));
	interiorUpWall->Graphic().setOrigin(172, 40);
	interiorUpWall->Graphic().scale(sf::Vector2f(1.3f, 1.0f));

	interiorUpWall->SetTag(Tag::Wall);
	CollisionHandler::AddCollision(interiorUpWall);
}

void Program::CreateInteriorLimits()
{
	std::string leftRightLimitFilePath = "res\\textures\\enviroment\\interior\\LimitLeftRight.png";
	sf::Vector2i leftRightLimitSpriteSheetSize = { 3, 251 };

	limitLeft = new Entity(leftRightLimitFilePath, leftRightLimitSpriteSheetSize);
	limitRight = new Entity(leftRightLimitFilePath, leftRightLimitSpriteSheetSize);

	limitLeft->Graphic().setPosition(378, 420);
	limitLeft->Graphic().setOrigin(1, 125);
	limitLeft->Graphic().scale(sf::Vector2f(1.0f, 1.2f));

	limitRight->Graphic().setPosition(820, 420);
	limitRight->Graphic().setOrigin(1, 125);
	limitRight->Graphic().scale(sf::Vector2f(1.0f, 1.2f));

	limitLeft->SetBounds(limitLeft->Graphic().getGlobalBounds());
	limitRight->SetBounds(limitRight->Graphic().getGlobalBounds());

	limitLeft->SetTag(Tag::Limit);
	CollisionHandler::AddCollision(limitLeft);

	limitRight->SetTag(Tag::Limit);
	CollisionHandler::AddCollision(limitRight);


	std::string downLimitFilePath = "res\\textures\\enviroment\\interior\\LimitDown.png";
	sf::Vector2i downLimitSpriteSheetSize = { 345, 4 };

	limitDown = new Entity(downLimitFilePath, downLimitSpriteSheetSize);

	limitDown->Graphic().setPosition(595, 562);
	limitDown->Graphic().setOrigin(172, 2);
	limitDown->Graphic().scale(sf::Vector2f(1.3f, 2.0f));

	limitDown->SetBounds(limitDown->Graphic().getGlobalBounds());

	limitDown->SetTag(Tag::Limit);
	CollisionHandler::AddCollision(limitDown);
}

void Program::CreateBed()
{
	std::string bedFilePath = "res\\textures\\enviroment\\interior\\Bed.png";
	sf::Vector2i bedSpriteSheetSize = { 57, 95 };

	bed = new Bed(bedFilePath, bedSpriteSheetSize);

	bed->Graphic().setPosition(416, 370);
	bed->Graphic().setOrigin(28, 47);
	bed->Graphic().scale(sf::Vector2f(1.1f, 1.0f));
	

	bed->SetTag(Tag::Bed);
	CollisionHandler::AddCollision(bed);
}

void Program::CreateRadio()
{
	std::string radioFilePath = "res\\textures\\enviroment\\interior\\Radio.png";
	sf::Vector2i radioSpriteSheetSize = { 42, 58 };

	radio = new Radio(radioFilePath, radioSpriteSheetSize);

	radio->Graphic().setPosition(770, 345);
	radio->Graphic().setOrigin(21, 28);
	radio->Graphic().scale(sf::Vector2f(1.0f, 1.0f));


	radio->SetTag(Tag::Radio);
	CollisionHandler::AddCollision(radio);
	
}

void Program::CreateChairs()
{
	std::string chairFilePath = "res\\textures\\enviroment\\interior\\Chair.png";
	sf::Vector2i chairSpriteSheetSize = { 26, 26 };

	chairLeft = new Entity (chairFilePath, chairSpriteSheetSize);
	chairRight = new Entity (chairFilePath, chairSpriteSheetSize);

	chairLeft->Graphic().setPosition(770, 345);
	chairLeft->Graphic().setOrigin(21, 28);
	chairLeft->Graphic().scale(sf::Vector2f(1.0f, 1.0f));

	chairRight->Graphic().setPosition(770, 345);
	chairRight->Graphic().setOrigin(21, 28);
	chairRight->Graphic().scale(sf::Vector2f(1.0f, 1.0f));

	chairLeft->Graphic().setScale(sf::Vector2f(1.2, 1.2));
	chairRight->Graphic().setScale(sf::Vector2f(1.2, 1.2));


	chairLeft->SetTag(Tag::Chair);
	chairRight->SetTag(Tag::Chair);

	chairLeft->Graphic().setPosition(550, 460);
	chairRight->Graphic().setPosition(700, 460);


	sf::FloatRect chairBoundsLeft = chairLeft->Graphic().getGlobalBounds();
	sf::FloatRect chairBoundsRight = chairRight->Graphic().getGlobalBounds();
	
	chairBoundsLeft.height *= 0.3;
	chairBoundsRight.height *= 0.3;


	chairLeft->SetBounds(chairBoundsLeft);
	chairRight->SetBounds(chairBoundsRight);

	CollisionHandler::AddCollision(chairLeft);
	CollisionHandler::AddCollision(chairRight);
}

void Program::CreateTable()
{
	std::string tableFilePath = "res\\textures\\enviroment\\interior\\Table.png";
	sf::Vector2i tableSpriteSheetSize = { 82, 51 };

	table = new Entity(tableFilePath, tableSpriteSheetSize);

	table->Graphic().setPosition(618, 440);
	table->Graphic().setOrigin(41, 25);
	table->Graphic().scale(sf::Vector2f(1.2f, 1.1f));

	table->SetTag(Tag::Table);

	sf::FloatRect tableBounds = table->Graphic().getGlobalBounds();

	tableBounds.height *= 0.5;

	table->SetBounds(tableBounds);

	CollisionHandler::AddCollision(table);

}

void Program::CreateDoorColliderInside()
{
	std::string doorColliderFilePath = "res\\textures\\enviroment\\interior\\Collider.png";
	sf::Vector2i doorColliderSpriteSheetSize = { 32, 32 };

	doorColliderInside = new Entity(doorColliderFilePath, doorColliderSpriteSheetSize);

	doorColliderInside->Graphic().setPosition(738, 575);
	doorColliderInside->Graphic().setOrigin(41, 25);
	doorColliderInside->Graphic().scale(sf::Vector2f(2.2f, 1.0f));

	doorColliderInside->SetTag(Tag::DoorColliderInside);

	sf::FloatRect doorColliderBounds = doorColliderInside->Graphic().getGlobalBounds();
		
	doorColliderInside->SetBounds(doorColliderBounds);

	CollisionHandler::AddCollision(doorColliderInside);
}

void Program::CreateBedCollider()
{
	std::string bedColliderFilePath = "res\\textures\\enviroment\\interior\\Collider.png";
	sf::Vector2i bedColliderSpriteSheetSize = { 32, 32 };

	bedCollider = new Entity(bedColliderFilePath, bedColliderSpriteSheetSize);

	bedCollider->Graphic().setPosition(470, 350);
	bedCollider->Graphic().setOrigin(41, 25);
	bedCollider->Graphic().scale(sf::Vector2f(1.0f, 2.5f));

	bedCollider->SetTag(Tag::BedCollider);

	sf::FloatRect bedColliderBounds = bedCollider->Graphic().getGlobalBounds();

	bedCollider->SetBounds(bedColliderBounds);

	CollisionHandler::AddCollision(bedCollider);
}

void Program::CreateRadioCollider()
{
	std::string radioColliderFilePath = "res\\textures\\enviroment\\interior\\Collider.png";
	sf::Vector2i radioColliderSpriteSheetSize = { 32, 32 };

	radioCollider = new Entity(radioColliderFilePath, radioColliderSpriteSheetSize);

	radioCollider->Graphic().setPosition(775, 385);
	radioCollider->Graphic().setOrigin(41, 25);
	radioCollider->Graphic().scale(sf::Vector2f(0.2f, 1.0f));

	radioCollider->SetTag(Tag::BedCollider);

	sf::FloatRect radioColliderBounds = radioCollider->Graphic().getGlobalBounds();

	radioCollider->SetBounds(radioColliderBounds);

	CollisionHandler::AddCollision(radioCollider);
}



void Program::NightTimeUpdate(float deltaTime)
{
	player->Update(deltaTime);

	hud->Update(player->GetCurrentWeapon().GetCurrentAmmo(), deltaTime);
	timeClock->Update(deltaTime);

	house->Update(deltaTime);

	car->Update(deltaTime);

	for (int i = 0; i < fences.size(); i++)
	{
		fences[i]->Update(deltaTime);
	}

	enemySpawner->Update(deltaTime, player->Graphic().getPosition());
	
}

void Program::DayTimeUpdate(float deltaTime)
{	
	player->Update(deltaTime);

	hud->Update(player->GetCurrentWeapon().GetCurrentAmmo(), deltaTime);
	timeClock->Update(deltaTime);

	if (sceneManager->GetIsOutsidePlayerHouse())
	{
		house->Update(deltaTime);

		car->Update(deltaTime);

		for (int i = 0; i < fences.size(); i++)
		{
			fences[i]->Update(deltaTime);
		}
	}

}


void Program::DrawPlayer()
{
	window->draw(player->Graphic());
}

void Program::DrawEButton()
{
	window->draw(player->GetEButton()->Graphic());
}


void Program::DrawBedHoursInterface()
{
	if (Bed::GetHoursInterface()->GetIsActive())
	{
		window->draw(Bed::GetHoursInterface()->GetBackground()->Graphic());
		//falta drawear flechas y demas.
	}
}


void Program::DrawNightTime()
{
	DrawOutsideFloor();

	//dibujar fences
	if (player->Graphic().getPosition().y <= 350)
	{
		DrawFences();
	}

	DrawBullets();

	//dibujar player y weapon
	if (player->Graphic().getPosition().y <= 280)
	{
		DrawPlayer();

		if (player->GetIsAlive())
			DrawWeapon();
	}

	//dibujar enemigos
	for (int i = 0; i < enemySpawner->GetEnemies().size(); i++)
	{
		if (enemySpawner->GetEnemies()[i]->Graphic().getPosition().y > 240 &&
			enemySpawner->GetEnemies()[i]->Graphic().getPosition().y <= 280)
		{
			if (enemySpawner->GetEnemies()[i]->GetIsActive())
			{
				window->draw(enemySpawner->GetEnemies()[i]->Graphic());
			}
		}

	}

	DrawHouse();

	DrawCar();

	//dibujar player y weapon
	if (player->Graphic().getPosition().y > 280)
	{
		DrawPlayer();

		if (player->GetIsAlive())
			DrawWeapon();
	}

	//dibujar enemigos
	for (int i = 0; i < enemySpawner->GetEnemies().size(); i++)
	{
		if (enemySpawner->GetEnemies()[i]->Graphic().getPosition().y > 280)
		{
			if (enemySpawner->GetEnemies()[i]->GetIsActive())
			{
				window->draw(enemySpawner->GetEnemies()[i]->Graphic());
			}
		}

	}

	if (player->Graphic().getPosition().y > 350)
	{
		DrawFences();
	}

	//dibujar enemigos
	for (int i = 0; i < enemySpawner->GetEnemies().size(); i++)
	{
		if (enemySpawner->GetEnemies()[i]->Graphic().getPosition().y > 350 ||
			enemySpawner->GetEnemies()[i]->Graphic().getPosition().y <= 240)
		{
			if (enemySpawner->GetEnemies()[i]->GetIsActive())
			{
				window->draw(enemySpawner->GetEnemies()[i]->Graphic());
			}
		}

	}

	DrawSky();

	DrawEnemiesHealthBars();

	DrawHouseHealthBar();

	DrawCarHealthBar();

	DrawTimeClock();

	DrawHUD();

	DrawAmmoText();

	DrawHUDBullets();

	DrawDate();

	//DrawDoorColliderOutside();

	DrawTransitionScreen();
}

void Program::DrawOutsideFloor()
{
	for (int i = 0; i < floor.size(); i++)
	{
		window->draw(floor[i]->Graphic());
	}
}

void Program::DrawFences()
{
	for (int i = 0; i < fences.size(); i++)
	{
		window->draw(fences[i]->Graphic());
	}
}

void Program::DrawBullets()
{
	for (int i = 0; i < 20; i++)
	{
		if (player->GetCurrentWeapon().GetBullets()[i]->GetIsActive())
		{
			window->draw(player->GetCurrentWeapon().GetBullets()[i]->Graphic());
		}
	}
}

void Program::DrawWeapon()
{
	window->draw(player->GetCurrentWeapon().Graphic());
}

void Program::DrawHouse()
{
	window->draw(house->Graphic());
}

void Program::DrawCar()
{
	window->draw(car->Graphic());
}

void Program::DrawSky()
{
	window->draw(skyNight->Graphic());
}

void Program::DrawEnemiesHealthBars()
{
	for (int i = 0; i < enemySpawner->GetEnemies().size(); i++)
	{
		if (enemySpawner->GetEnemies()[i]->GetIsActive())
		{
			window->draw(enemySpawner->GetEnemies()[i]->GetHealthBar()->Graphic());
		}
	}
}

void Program::DrawHouseHealthBar()
{
	window->draw(house->GetHealthBar()->Graphic());
}

void Program::DrawCarHealthBar()
{
	window->draw(car->GetHealthBar()->Graphic());
}

void Program::DrawTimeClock()
{
	window->draw(timeClock->Graphic());
}

void Program::DrawHUD()
{
	window->draw(hud->Graphic());
}

void Program::DrawAmmoText()
{
	window->draw(*hud->GetAmmoText());
}

void Program::DrawHUDBullets()
{
	window->draw(hud->GetAmmoHolder()->Graphic());
}

void Program::DrawDate()
{
	window->draw(*timeClock->GetDateText());
}

void Program::DrawTransitionScreen()
{
	window->draw(sceneManager->GetBlackScreenTransition()->Graphic());
}



void Program::DrawDayTime()
{
	if (sceneManager->GetIsInsidePlayerHouse())	
	{
		DrawInsideHouse();
	}	
	else if (sceneManager->GetIsOutsidePlayerHouse())
	{
		DrawOutsideHouse();		
	}

	DrawTimeClock();

	DrawHUD();

	DrawDate();

	DrawHours();

	DrawEButton();

	DrawTransitionScreen();


	//ACTIVAR PARA TESTEO

	/*DrawPlayerInHouse();

	DrawTimeClock();

	DrawHUD();

	DrawDate();

	DrawEButton();

	DrawTransitionScreen();*/
	
}

void Program::DrawInsideHouse()
{
	DrawPlayerInHouse();		
}

void Program::DrawOutsideHouse()
{
	DrawOutsideFloor();

	//dibujar fences
	if (player->Graphic().getPosition().y <= 350)
	{
		DrawFences();
	}

	//dibujar player y weapon
	if (player->Graphic().getPosition().y <= 280)
	{
		DrawPlayer();
	}

	DrawHouse();

	DrawCar();

	//dibujar player y weapon
	if (player->Graphic().getPosition().y > 280)
	{
		DrawPlayer();
	}

	if (player->Graphic().getPosition().y > 350)
	{
		DrawFences();
	}

	DrawHouseHealthBar();

	DrawCarHealthBar();

	
}

void Program::DrawPlayerInHouse()
{
	DrawInteriorFloor();

	DrawInteriorWalls();

	DrawLimits();

	DrawBed();

	DrawRadio();

	DrawChairs();

	DrawTable();

	DrawPlayer();

	/*DrawDoorCollider();

	DrawBedCollider();

	DrawRadioCollider();*/
}

void Program::DrawInteriorFloor()
{
	window->draw(interiorFloor->Graphic());
}

void Program::DrawInteriorWalls()
{
	window->draw(interiorUpWall->Graphic());
}

void Program::DrawLimits()
{
	window->draw(limitLeft->Graphic());
	window->draw(limitRight->Graphic());
	window->draw(limitDown->Graphic());
}

void Program::DrawBed()
{
	window->draw(bed->Graphic());
}

void Program::DrawRadio()
{	
	window->draw(radio->Graphic());		
	window->draw(*radio->GetRadioText());
}

void Program::DrawChairs()
{
	window->draw(chairLeft->Graphic());
	window->draw(chairRight->Graphic());
}

void Program::DrawTable()
{
	window->draw(table->Graphic());
}

void Program::DrawDoorColliderInside()
{
	window->draw(doorColliderInside->Graphic());
}

void Program::DrawBedCollider()
{
	window->draw(bedCollider->Graphic());
}

void Program::DrawRadioCollider()
{
	window->draw(radioCollider->Graphic());
}

void Program::DrawDoorColliderOutside()
{
	window->draw(doorColliderOutside->Graphic());
}

void Program::DrawHours()
{	
	window->draw(*timeClock->GetTimeText());
}