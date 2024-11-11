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

	CreateToolbox();

	CreatePlanks();

	CreateBricks();

	CreateInteriorFloor();

	CreateInteriorWall();

	CreateInteriorLimits();

	CreateBed();

	CreateRadio();

	CreateChairs();

	CreateTable();

	CreateBook();

	CreateCalendar();

	CreateBoard();

	CreateDoorColliderInside();

	CreateBedCollider();

	CreateRadioCollider();

	CreateDoorColliderOutside();

	CreateSOSSign();

	CreateTitle();

	CreateCarCollider();

	CreateToolboxCollider();

	CreatePlanksCollider();

	CreateBricksCollider();

	CreateBookCollider();

	CreateCalendarCollider();

	CreateBoardCollider();

	CreateCarHoursInterface();

	CreateToolboxHoursInterface();

	CreatePlanksHoursInterface();

	CreateBricksHoursInterface();

	CreateDaysTasksManager();

	CreateCarWindow();

	CreateBookWindow();

	CreateCalendarWindow();

	CreateBoardWindow();

	CreateBedWindow();

	CreateRadioWindow();

	CreateFont();

	CreateGameOverOptions();

	CreateEndingTexts();

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

	sceneManager->Update(dayTasksManager, deltaTime);

	Fence::GetHealthPercentage(fences);
	car->GetHealthPercentage();
	house->GetHealthPercentage();


	if (sceneManager->GetIsNightTimeScene())
	{
		NightTimeUpdate(deltaTime);
	}
	else if (sceneManager->GetIsDayTimeScene())
	{
		DayTimeUpdate(deltaTime);
	}
	else if (sceneManager->GetIsTitleScene())
	{
		for (int i = 0; i < fences.size(); i++)
		{
			fences[i]->Update(deltaTime);
		}

		house->Update(deltaTime);

		car->Update(deltaTime);

		player->Update(deltaTime);
	}
	/*for (auto node = nodesGrid->GetNodesGrid().begin(); node != nodesGrid->GetNodesGrid().end(); ++node)
	{
		node->second->Update(CollisionHandler::GetEntities(), node->second);				
	}*/
		
	Ending(deltaTime);

	if (sceneManager->GetIsGameOver())
		UpdateGameOver();

	CollisionHandler::SolveCollisions(deltaTime, sceneManager, window, carHoursInterface, toolboxHoursInterface, planksHoursInterface, bricksHoursInterface,
		bed->GetHoursInterface(), sosSign->GetHoursInterface(), dayTasksManager, carWindow, bookWindow, calendarWindow, boardWindow, bedWindow, radioWindow);	

}

void Program::Draw()
{
	window->clear();
	
	float nodePosX = player->Graphic().getPosition().x + 15;
	float nodePosY = player->Graphic().getPosition().y + 25;
		
	if (sceneManager->GetIsNightTimeScene())
	{
		DrawNightTime();
		DrawHoursInterfaces();
		window->draw(timeClock->GetButtonClose()->Graphic());

	}
	else if (sceneManager->GetIsDayTimeScene())
	{
		DrawDayTime();
		DrawHoursInterfaces();
		window->draw(timeClock->GetButtonClose()->Graphic());
	}
	else if (sceneManager->GetIsTitleScene())
	{
		if (sceneManager->GetIsOutsidePlayerHouse())
		{
			DrawOutsideFloor();

			DrawTitle();

			//dibujar fences
			if (player->Graphic().getPosition().y <= 350)
			{
				DrawFences();
			}

			//dibujar player 
			if (player->Graphic().getPosition().y <= 280)
			{
				DrawPlayer();
			}

			DrawHouse();

			DrawCar();

			//dibujar player 
			if (player->Graphic().getPosition().y > 280)
			{
				DrawPlayer();
			}

			if (player->Graphic().getPosition().y > 350)
			{
				DrawFences();
			}

		}
		else if (sceneManager->GetIsInsidePlayerHouse())
		{
			DrawInsideHouse();
		}			
			
		DrawEButton();
				
		DrawCarWindow();

		DrawBookWindow();

		DrawCalendarWindow();

		DrawBoardWindow();

		DrawBedWindow();

		DrawRadioWindow();
		
		DrawTransitionScreen();
				

	}
	
	DrawEndingText();

	//window->draw(baseAreaCollider->Graphic());

	DrawGameOverText(deltaTime);

	window->display();
}



void Program::CreateWindow()
{
	windowWidth = 1200;				//1280 X 720
	windowHeight = 880;

	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Last Standing", sf::Style::Close);

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
	std::string bulletFilePath = "res\\textures\\weapons\\Bullet.png";
	sf::Vector2i bulletSpriteSheetSize = { 3, 3 };
	float bulletMaxPosX = windowWidth;
	float bulletMaxPosY = windowHeight;


	float gunFireRate = 0.2f;
	float gunReloadTime = 1.0f;
	float gunCapacity = 7;

	float gunOriginX = 4;
	float gunOriginY = 4;

	sf::Vector2i gunAnimationFrameSize = { 8, 8 };
	std::string gunFilePath = "res\\textures\\weapons\\Gun.png";
	sf::Vector2i gunSpriteSheetSize = { 8, 32 };

	float gunBulletMinDamage = 3;
	float gunMaxBulletDamage = 6;
	float bulletSpeed = 2000.0f;
	

	gun = new Weapon(gunFireRate, gunReloadTime, gunCapacity, gunOriginX, gunOriginY, gunAnimationFrameSize, gunFilePath, gunSpriteSheetSize,
		gunBulletMinDamage, gunMaxBulletDamage, bulletSpeed, bulletFilePath, bulletSpriteSheetSize, bulletMaxPosX,
		bulletMaxPosY);

	gun->SetTag(Tag::Gun);
	CollisionHandler::AddCollision(gun);



	float shotgunFireRate = 0.6f;
	float shotgunReloadTime = 1.8f;
	float shotgunCapacity = 4;

	float shotgunOriginX = 0;
	float shotgunOriginY = 2.5f;

	sf::Vector2i shotgunAnimationFrameSize = { 16, 5 };
	std::string shotgunFilePath = "res\\textures\\weapons\\Shotgun.png";
	sf::Vector2i shotgunSpriteSheetSize = { 16, 10 };

	float shotgunBulletMinDamage = 12;
	float shotgunMaxBulletDamage = 20;
	float shotgunBulletSpeed = 2000.0f;


	shotgun = new Weapon(shotgunFireRate, shotgunReloadTime, shotgunCapacity, shotgunOriginX, shotgunOriginY, shotgunAnimationFrameSize, shotgunFilePath, 
		shotgunSpriteSheetSize,	shotgunBulletMinDamage, shotgunMaxBulletDamage, shotgunBulletSpeed, bulletFilePath, bulletSpriteSheetSize, bulletMaxPosX,
		bulletMaxPosY);

	shotgun->SetTag(Tag::Shotgun);
	CollisionHandler::AddCollision(shotgun);


	float uziFireRate = 0.1f;
	float uziReloadTime = 1.0f;
	float uziCapacity = 20;

	float uziOriginX = 5;
	float uziOriginY = 3;

	sf::Vector2i uziAnimationFrameSize = { 10, 6 };
	std::string uziFilePath = "res\\textures\\weapons\\Uzi.png";
	sf::Vector2i uziSpriteSheetSize = { 10, 12 };

	float uziBulletMinDamage = 1;
	float uziMaxBulletDamage = 3;
	float uziBulletSpeed = 2000.0f;


	uzi = new Weapon(uziFireRate, uziReloadTime, uziCapacity, uziOriginX, uziOriginY, uziAnimationFrameSize, uziFilePath,
		uziSpriteSheetSize, uziBulletMinDamage, uziMaxBulletDamage, uziBulletSpeed, bulletFilePath, bulletSpriteSheetSize, bulletMaxPosX,
		bulletMaxPosY);

	uzi->SetTag(Tag::Uzi);
	CollisionHandler::AddCollision(uzi);




}

void Program::CreatePlayer()
{
	float playerSpeed = 100;
	sf::Vector2i playerAnimationFrameSize = { 15, 15 };
	std::string playerFilePath = "res\\textures\\player\\Player.png";
	sf::Vector2i playerSpriteSheetSize = { 44, 90 };

	player = new Player(playerSpeed, gun, shotgun, uzi, windowWidth, windowHeight, playerAnimationFrameSize, playerFilePath,
		playerSpriteSheetSize);

	player->SetTag(Tag::Player);
	CollisionHandler::AddCollision(player);
}

void Program::CreateHUD()
{
	sf::Vector2i hudAnimationFrameSize = { 1200, 92 };
	std::string hudFilePath = "res\\textures\\HUD\\HUDbar.png";
	sf::Vector2i hudSpriteSheetSize = { 1200, 273 };

	hud = new HUD(hudAnimationFrameSize, hudFilePath, hudSpriteSheetSize);
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

	CollisionHandler::AddCollision(timeClock->GetButtonClose());
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

	std::cout << std::to_string(fences.size());
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

void Program::CreateToolbox()
{
	std::string toolboxFilePath = "res\\textures\\enviroment\\Toolbox.png";
	sf::Vector2i toolboxSpriteSheetSize = { 24, 22 };

	toolbox = new Entity(toolboxFilePath, toolboxSpriteSheetSize);

	toolbox->Graphic().setPosition(400, 500);
	toolbox->Graphic().setOrigin(12, 11);
	toolbox->Graphic().scale(sf::Vector2f(1.3f, 1.3f));


	toolbox->SetTag(Tag::Toolbox);

	sf::FloatRect toolboxBounds = toolbox->Graphic().getGlobalBounds();

	toolboxBounds.height *= 0.15;

	toolbox->SetBounds(toolboxBounds);

	CollisionHandler::AddCollision(toolbox);
}

void Program::CreatePlanks()
{
	std::string planksFilePath = "res\\textures\\enviroment\\Planks.png";
	sf::Vector2i planksSpriteSheetSize = { 45, 93 };

	planks = new Entity(planksFilePath, planksSpriteSheetSize);

	planks->Graphic().setPosition(880, 370);
	planks->Graphic().setOrigin(21, 44);
	planks->Graphic().scale(sf::Vector2f(1.0f, 1.0f));


	planks->SetTag(Tag::Planks);

	sf::FloatRect planksBounds = planks->Graphic().getGlobalBounds();

	planks->SetBounds(planksBounds);

	CollisionHandler::AddCollision(planks);
}

void Program::CreateBricks()
{
	std::string bricksFilePath = "res\\textures\\enviroment\\Bricks.png";
	sf::Vector2i bricksSpriteSheetSize = { 40, 21 };

	bricks = new Entity(bricksFilePath, bricksSpriteSheetSize);

	bricks->Graphic().setPosition(650, 440);
	bricks->Graphic().setOrigin(20, 10);
	bricks->Graphic().scale(sf::Vector2f(1.4f, 1.4f));


	bricks->SetTag(Tag::Bricks);

	sf::FloatRect brickBounds = bricks->Graphic().getGlobalBounds();

	brickBounds.height *= 0.15;

	bricks->SetBounds(brickBounds);

	CollisionHandler::AddCollision(bricks);
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

void Program::CreateSOSSign()
{
	sf::Vector2f sosSignPos = { 570,345 };

	sf::Vector2i sosSignAnimationFrameSize = { 97, 36 };
	std::string sosSignFilePath = "res\\textures\\enviroment\\SOSSign.png";
	sf::Vector2i sosSignSpriteSheetSize = { 97, 72 };


	sosSign = new SOSSign(sosSignAnimationFrameSize, sosSignFilePath, sosSignSpriteSheetSize);
	sosSign->SetTag(Tag::SOSSign);

	sosSign->Graphic().setPosition(sosSignPos);

	sosSign->Graphic().setOrigin(sosSignAnimationFrameSize.x, sosSignAnimationFrameSize.y);

	sosSign->Graphic().setScale({ 2.3, 1.8 });

	sosSign->GetHoursInterface()->GetInterfaceText()->setPosition(495, 370);

	sosSign->GetHoursInterface()->GetResourcesText()->setPosition(485, 450);

	sosSign->GetHoursInterface()->GetScrapCostText()->setPosition(604, 450);

	sosSign->GetHoursInterface()->GetHoursLeftText()->setPosition(537, 477);

	sosSign->GetScrapNeededText()->setPosition(507, 420);

	CollisionHandler::AddCollision(sosSign);
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

	bed->GetHoursInterface()->GetInterfaceText()->setPosition(495, 360);
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

void Program::CreateBook()
{
	std::string bookFilePath = "res\\textures\\enviroment\\interior\\Book.png";
	sf::Vector2i bookSpriteSheetSize = { 27, 17 };

	book = new Entity(bookFilePath, bookSpriteSheetSize);

	book->Graphic().setPosition(618, 430);
	book->Graphic().setOrigin(14, 8);
	book->Graphic().scale(sf::Vector2f(1.2f, 1.2f));

}

void Program::CreateCalendar()
{
	std::string calendarFilePath = "res\\textures\\enviroment\\interior\\Calendar.png";
	sf::Vector2i calendarSpriteSheetSize = { 42, 27 };

	calendar = new Entity(calendarFilePath, calendarSpriteSheetSize);

	calendar->Graphic().setPosition(496, 320);
	calendar->Graphic().setOrigin(21, 13);
	calendar->Graphic().scale(sf::Vector2f(1.0f, 1.0f));

}

void Program::CreateBoard()
{
	std::string boardFilePath = "res\\textures\\enviroment\\interior\\Board.png";
	sf::Vector2i boardSpriteSheetSize = { 76, 37 };

	board = new Entity(boardFilePath, boardSpriteSheetSize);

	board->Graphic().setPosition(575, 315);
	board->Graphic().setOrigin(38, 18);
	board->Graphic().scale(sf::Vector2f(1.0f, 1.0f));
}

void Program::CreateCarWindow()
{	
	carWindow = new PopUpWindow();
	CollisionHandler::AddCollision(carWindow->GetButtonClose());

	carWindow->GetText()->setString("Do you want to exit?");
	carWindow->GetText()->setPosition(517, 390);

	carWindow->GetOkButton()->SetTag(Tag::OkPopUpWindowCar);

	CollisionHandler::AddCollision(carWindow->GetOkButton());
	CollisionHandler::AddCollision(carWindow->GetCancelButton());
}

void Program::CreateBookWindow()
{
	bookWindow = new PopUpWindow();
	CollisionHandler::AddCollision(bookWindow->GetButtonClose());	

	bookWindow->GetText()->setString("TUTORIAL");
	bookWindow->GetText()->setPosition(555, 360);
}

void Program::CreateCalendarWindow()
{
	calendarWindow = new PopUpWindow();
	CollisionHandler::AddCollision(calendarWindow->GetButtonClose());

	calendarWindow->GetText()->setString("SCORE");
	calendarWindow->GetText()->setPosition(568, 360);
}

void Program::CreateBoardWindow()
{
	boardWindow = new PopUpWindow();
	CollisionHandler::AddCollision(boardWindow->GetButtonClose());

	boardWindow->GetText()->setString("CREDITS");
	boardWindow->GetText()->setPosition(559, 360);
}

void Program::CreateBedWindow()
{
	bedWindow = new PopUpWindow();
	CollisionHandler::AddCollision(bedWindow->GetButtonClose());

	bedWindow->GetText()->setString("Do you want to play?");
	bedWindow->GetText()->setPosition(517, 390);

	bedWindow->GetOkButton()->SetTag(Tag::OkPopUpWindowBed);

	CollisionHandler::AddCollision(bedWindow->GetOkButton());
	CollisionHandler::AddCollision(bedWindow->GetCancelButton());
}

void Program::CreateRadioWindow()
{
	radioWindow = new PopUpWindow();
	CollisionHandler::AddCollision(radioWindow->GetButtonClose());

	radioWindow->GetText()->setString("SOUND");
	radioWindow->GetText()->setPosition(568, 360);
}

void Program::CreateTitle()
{
	std::string titleFilePath = "res\\textures\\title\\Title.png";
	sf::Vector2i titleSpriteSheetSize = { 503, 47 };

	title = new Entity(titleFilePath, titleSpriteSheetSize);

	title->Graphic().setPosition(620, 100);
	title->Graphic().setOrigin(253, 23);
	title->Graphic().scale(sf::Vector2f(1.0f, 1.0f));
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

	radioCollider->SetTag(Tag::RadioCollider);

	sf::FloatRect radioColliderBounds = radioCollider->Graphic().getGlobalBounds();

	radioCollider->SetBounds(radioColliderBounds);

	CollisionHandler::AddCollision(radioCollider);
}

void Program::CreateCarCollider()
{
	std::string carColliderFilePath = "res\\textures\\enviroment\\interior\\Collider.png";
	sf::Vector2i carColliderSpriteSheetSize = { 32, 32 };

	carCollider = new Entity(carColliderFilePath, carColliderSpriteSheetSize);

	carCollider->Graphic().setPosition(503, 485);
	carCollider->Graphic().setOrigin(41, 25);
	carCollider->Graphic().scale(sf::Vector2f(0.5f, 1.0f));

	carCollider->SetTag(Tag::CarCollider);

	sf::FloatRect carColliderBounds = carCollider->Graphic().getGlobalBounds();

	carCollider->SetBounds(carColliderBounds);

	CollisionHandler::AddCollision(carCollider);
}

void Program::CreateToolboxCollider()
{
	std::string toolboxColliderFilePath = "res\\textures\\enviroment\\interior\\Collider.png";
	sf::Vector2i toolboxColliderSpriteSheetSize = { 32, 32 };

	toolboxCollider = new Entity(toolboxColliderFilePath, toolboxColliderSpriteSheetSize);

	toolboxCollider->Graphic().setPosition(395, 500);
	toolboxCollider->Graphic().setOrigin(16, 16);
	toolboxCollider->Graphic().scale(sf::Vector2f(1.1f, 1.0f));

	toolboxCollider->SetTag(Tag::ToolboxCollider);

	sf::FloatRect toolboxColliderBounds = toolboxCollider->Graphic().getGlobalBounds();

	toolboxCollider->SetBounds(toolboxColliderBounds);

	CollisionHandler::AddCollision(toolboxCollider);
}

void Program::CreatePlanksCollider()
{
	std::string planksColliderFilePath = "res\\textures\\enviroment\\interior\\Collider.png";
	sf::Vector2i planksColliderSpriteSheetSize = { 32, 32 };

	planksCollider = new Entity(planksColliderFilePath, planksColliderSpriteSheetSize);

	planksCollider->Graphic().setPosition(880, 370);
	planksCollider->Graphic().setOrigin(16, 16);
	planksCollider->Graphic().scale(sf::Vector2f(1.7f, 3.4f));

	planksCollider->SetTag(Tag::PlanksCollider);

	sf::FloatRect planksColliderBounds = planksCollider->Graphic().getGlobalBounds();

	planksCollider->SetBounds(planksColliderBounds);

	CollisionHandler::AddCollision(planksCollider);

}

void Program::CreateBricksCollider()
{
	std::string bricksColliderFilePath = "res\\textures\\enviroment\\interior\\Collider.png";
	sf::Vector2i bricksColliderSpriteSheetSize = { 32, 32 };

	bricksCollider = new Entity(bricksColliderFilePath, bricksColliderSpriteSheetSize);

	bricksCollider->Graphic().setPosition(650, 440);
	bricksCollider->Graphic().setOrigin(16, 16);
	bricksCollider->Graphic().scale(sf::Vector2f(1.9f, 1.0f));

	bricksCollider->SetTag(Tag::BricksCollider);

	sf::FloatRect bricksColliderBounds = bricksCollider->Graphic().getGlobalBounds();

	bricksCollider->SetBounds(bricksColliderBounds);

	CollisionHandler::AddCollision(bricksCollider);
}

void Program::CreateBookCollider()
{
	std::string bookColliderFilePath = "res\\textures\\enviroment\\interior\\Collider.png";
	sf::Vector2i bookColliderSpriteSheetSize = { 32, 32 };

	bookCollider = new Entity(bookColliderFilePath, bookColliderSpriteSheetSize);

	bookCollider->Graphic().setPosition(618, 450);
	bookCollider->Graphic().setOrigin(16, 16);
	bookCollider->Graphic().scale(sf::Vector2f(1.9f, 1.0f));

	bookCollider->SetTag(Tag::BookCollider);

	sf::FloatRect bookColliderBounds = bookCollider->Graphic().getGlobalBounds();

	bookCollider->SetBounds(bookColliderBounds);

	CollisionHandler::AddCollision(bookCollider);
}

void Program::CreateCalendarCollider()
{
	std::string calendarColliderFilePath = "res\\textures\\enviroment\\interior\\Collider.png";
	sf::Vector2i calendarColliderSpriteSheetSize = { 32, 32 };

	calendarCollider = new Entity(calendarColliderFilePath, calendarColliderSpriteSheetSize);

	calendarCollider->Graphic().setPosition(496, 340);
	calendarCollider->Graphic().setOrigin(16, 16);
	calendarCollider->Graphic().scale(sf::Vector2f(0.2f, 1.0f));

	calendarCollider->SetTag(Tag::CalendarCollider);

	sf::FloatRect calendarColliderBounds = calendarCollider->Graphic().getGlobalBounds();

	calendarCollider->SetBounds(calendarColliderBounds);

	CollisionHandler::AddCollision(calendarCollider);
}

void Program::CreateBoardCollider()
{
	std::string boardColliderFilePath = "res\\textures\\enviroment\\interior\\Collider.png";
	sf::Vector2i boardColliderSpriteSheetSize = { 32, 32 };

	boardCollider = new Entity(boardColliderFilePath, boardColliderSpriteSheetSize);

	boardCollider->Graphic().setPosition(575, 335);
	boardCollider->Graphic().setOrigin(16, 16);
	boardCollider->Graphic().scale(sf::Vector2f(1.0f, 1.0f));

	boardCollider->SetTag(Tag::BoardCollider);

	sf::FloatRect boardColliderBounds = boardCollider->Graphic().getGlobalBounds();

	boardCollider->SetBounds(boardColliderBounds);

	CollisionHandler::AddCollision(boardCollider);
}

void Program::CreateCarHoursInterface()
{
	carHoursInterface = new HoursInterface();

	carHoursInterface->SetInterfaceText("How much time should \n		I scavenge?");
	carHoursInterface->GetInterfaceText()->setPosition(495, 390);

	carHoursInterface->GetButtonOk()->SetTag(Tag::OkHoursButtonScavenge);
	CollisionHandler::AddCollision(carHoursInterface->GetButtonOk());
}

void Program::CreateToolboxHoursInterface()
{
	toolboxHoursInterface = new HoursInterface();

	toolboxHoursInterface->SetInterfaceText("How much time should \n	   I repair car?");
	toolboxHoursInterface->GetInterfaceText()->setPosition(495, 360);

	toolboxHoursInterface->GetButtonOk()->SetTag(Tag::OkHoursButtonToolbox);
	CollisionHandler::AddCollision(toolboxHoursInterface->GetButtonOk());
}

void Program::CreatePlanksHoursInterface()
{
	planksHoursInterface = new HoursInterface();

	planksHoursInterface->SetInterfaceText("How much time should \n	 I repair fences?");
	planksHoursInterface->GetInterfaceText()->setPosition(495, 360);

	planksHoursInterface->GetButtonOk()->SetTag(Tag::OkHoursButtonPlanks);
	CollisionHandler::AddCollision(planksHoursInterface->GetButtonOk());

}

void Program::CreateBricksHoursInterface()
{
	bricksHoursInterface = new HoursInterface();

	bricksHoursInterface->SetInterfaceText("How much time should \n	 I repair house?");
	bricksHoursInterface->GetInterfaceText()->setPosition(495, 360);

	bricksHoursInterface->GetButtonOk()->SetTag(Tag::OkHoursButtonBricks);
	CollisionHandler::AddCollision(bricksHoursInterface->GetButtonOk());
}

void Program::CreateDaysTasksManager()
{
	dayTasksManager = new DayTasksManager(fences, car, house);

	CollisionHandler::AddCollision(dayTasksManager->GetButtonClose());
}

void Program::CreateFont()
{
	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Roboto.ttf";
	font->loadFromFile(fontPath);
}

void Program::CreateGameOverOptions()
{
	sf::Color color = sf::Color(88, 83, 74, 255);

	restartText = new sf::Text("Restart", *font, 12);
	restartText->setPosition(610, 603);
	restartText->setFillColor(color);

	mainMenuText = new sf::Text("Main Menu", *font, 12);
	mainMenuText->setPosition(600, 660);
	mainMenuText->setFillColor(color);

	exitText = new sf::Text("Exit", *font, 12);
	exitText->setPosition(625, 720);
	exitText->setFillColor(color);
}

void Program::CreateEndingTexts()
{
	sf::Color color = sf::Color(88, 83, 74, 255);

	goodEndingText = new sf::Text("									YOU WERE RESCUED\n\n  After building an SOS signal," 
		" you were found by a rescue team.\n While on the chopper you learned form one of the survivors that\n"
		"    the infection is wider than you thought. Things seems to be\n getting out  of control everywhere. For now you are safe, but who\n"
		"								knows what comes next.\n\n									    Press 'E' to continue", *font, 35);
	goodEndingText->setPosition(100, 290);
	goodEndingText->setFillColor(color);

	badEndingText = new sf::Text("									      YOU SURVIVED\n\n  It's been a while since the infection"
		" started. You survived this long \n  on your own, but who knows how much more of this you can take. \n   Maybe the rescue team" 
		"   that you missed for your last chance of\n							      survival. Just time will tell."
		"\n\n									    Press 'E' to continue", *font, 35);
	badEndingText->setPosition(67, 290);
	badEndingText->setFillColor(color);

}


void Program::NightTimeUpdate(float deltaTime)
{
	player->Update(deltaTime);

	hud->Update(player->GetResources(), player->GetCurrentWeapon().GetCurrentAmmo(), deltaTime, player->GetCurrentWeapon());
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

	hud->Update(player->GetResources(), player->GetCurrentWeapon().GetCurrentAmmo(), deltaTime, player->GetCurrentWeapon());
	timeClock->Update(deltaTime);

	radio->Update(player->Graphic().getPosition(), deltaTime, sceneManager);

	UpdateHourInterfaces(deltaTime);

	dayTasksManager->Update();

	sosSign->Update();

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

void Program::UpdateHourInterfaces(float deltaTime)
{
	bed->GetHoursInterface()->Update(player->GetResources(), deltaTime);
	carHoursInterface->Update(player->GetResources(), deltaTime);
	toolboxHoursInterface->Update(player->GetResources(), deltaTime);
	planksHoursInterface->Update(player->GetResources(), deltaTime);
	bricksHoursInterface->Update(player->GetResources(), deltaTime);
	sosSign->GetHoursInterface()->Update(player->GetResources(), deltaTime);
}

void Program::UpdateGameOver()
{
	sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{		
		if (restartText->getGlobalBounds().contains(mousePos)) 
		{
			RestartGame();			
		}
		else if (mainMenuText->getGlobalBounds().contains(mousePos))
		{		
			GoMainMenu();
		}
		else if (exitText->getGlobalBounds().contains(mousePos))
		{
			exit(0);
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


void Program::DrawHoursInterfaces()
{

	DrawBedHoursInterface();

	DrawCarHoursInterface();

	DrawToolboxHoursInterface();

	DrawPlanksHoursInterface();

	DrawBricksHoursInterface();

	DrawSOSSignHoursInterface();

}


void Program::DrawBedHoursInterface()
{
	if (Bed::GetHoursInterface()->GetIsActive())
	{
		window->draw(Bed::GetHoursInterface()->GetBackground()->Graphic());
		window->draw(Bed::GetHoursInterface()->GetButtonRight()->Graphic());
		window->draw(Bed::GetHoursInterface()->GetButtonLeft()->Graphic());
		window->draw(Bed::GetHoursInterface()->GetButtonClose()->Graphic());
		window->draw(Bed::GetHoursInterface()->GetButtonOk()->Graphic());

		window->draw(*Bed::GetHoursInterface()->GetInterfaceText());
		window->draw(*Bed::GetHoursInterface()->GetHoursSleptText());
		window->draw(*Bed::GetHoursInterface()->GetHoursLeftText());
		window->draw(*Bed::GetHoursInterface()->GetHoursToSpendText());
	}
}

void Program::DrawCarHoursInterface()
{
	if (carHoursInterface->GetIsActive())
	{
		window->draw(carHoursInterface->GetBackground()->Graphic());
		window->draw(carHoursInterface->GetButtonClose()->Graphic());
		window->draw(carHoursInterface->GetButtonLeft()->Graphic());
		window->draw(carHoursInterface->GetButtonRight()->Graphic());
		window->draw(carHoursInterface->GetButtonOk()->Graphic());

		window->draw(*carHoursInterface->GetInterfaceText());
		window->draw(*carHoursInterface->GetHoursLeftText());
		window->draw(*carHoursInterface->GetHoursToSpendText());
	}	
}

void Program::DrawToolboxHoursInterface()
{
	if (toolboxHoursInterface->GetIsActive())
	{
		window->draw(toolboxHoursInterface->GetBackground()->Graphic());
		window->draw(toolboxHoursInterface->GetButtonClose()->Graphic());
		window->draw(toolboxHoursInterface->GetButtonLeft()->Graphic());
		window->draw(toolboxHoursInterface->GetButtonRight()->Graphic());
		window->draw(toolboxHoursInterface->GetButtonOk()->Graphic());

		window->draw(*toolboxHoursInterface->GetInterfaceText());
		window->draw(*bricksHoursInterface->GetResourcesText());
		window->draw(*bricksHoursInterface->GetScrapCostText());
		window->draw(*toolboxHoursInterface->GetHoursLeftText());
		window->draw(*toolboxHoursInterface->GetHoursToSpendText());

		DrawNotEnoughScrapText();
		DrawCarHealthPercentageText();
	}
}

void Program::DrawPlanksHoursInterface()
{
	if (planksHoursInterface->GetIsActive())
	{
		window->draw(planksHoursInterface->GetBackground()->Graphic());
		window->draw(planksHoursInterface->GetButtonClose()->Graphic());
		window->draw(planksHoursInterface->GetButtonLeft()->Graphic());
		window->draw(planksHoursInterface->GetButtonRight()->Graphic());
		window->draw(planksHoursInterface->GetButtonOk()->Graphic());

		window->draw(*planksHoursInterface->GetInterfaceText());
		window->draw(*bricksHoursInterface->GetResourcesText());
		window->draw(*bricksHoursInterface->GetScrapCostText());
		window->draw(*planksHoursInterface->GetHoursLeftText());
		window->draw(*planksHoursInterface->GetHoursToSpendText());

		DrawNotEnoughScrapText();
		DrawFencesHealthPercentageText();
	}
}

void Program::DrawBricksHoursInterface()
{
	if (bricksHoursInterface->GetIsActive())
	{
		window->draw(bricksHoursInterface->GetBackground()->Graphic());
		window->draw(bricksHoursInterface->GetButtonClose()->Graphic());
		window->draw(bricksHoursInterface->GetButtonLeft()->Graphic());
		window->draw(bricksHoursInterface->GetButtonRight()->Graphic());
		window->draw(bricksHoursInterface->GetButtonOk()->Graphic());

		window->draw(*bricksHoursInterface->GetInterfaceText());
		window->draw(*bricksHoursInterface->GetResourcesText());
		window->draw(*bricksHoursInterface->GetScrapCostText());
		window->draw(*bricksHoursInterface->GetHoursLeftText());
		window->draw(*bricksHoursInterface->GetHoursToSpendText());

		DrawNotEnoughScrapText();
		DrawHouseHealthPercentageText();
	}
}

void Program::DrawSOSSignHoursInterface()
{
	if (SOSSign::GetHoursInterface()->GetIsActive())
	{
		window->draw(SOSSign::GetHoursInterface()->GetBackground()->Graphic());
		window->draw(SOSSign::GetHoursInterface()->GetButtonRight()->Graphic());
		window->draw(SOSSign::GetHoursInterface()->GetButtonLeft()->Graphic());
		window->draw(SOSSign::GetHoursInterface()->GetButtonClose()->Graphic());
		window->draw(SOSSign::GetHoursInterface()->GetButtonOk()->Graphic());

		window->draw(*SOSSign::GetHoursInterface()->GetInterfaceText());
		window->draw(*SOSSign::GetHoursInterface()->GetHoursLeftText());
		window->draw(*SOSSign::GetHoursInterface()->GetHoursToSpendText());

		window->draw(*sosSign->GetScrapNeededText());

		window->draw(*sosSign->GetHoursInterface()->GetResourcesText());

		window->draw(*sosSign->GetHoursInterface()->GetScrapCostText());

		DrawNotEnoughScrapText();

	}
}



void Program::DrawScavengeResults()
{
	if (dayTasksManager->GetScavengeResultsOpen())
	{
		window->draw(dayTasksManager->GetBackground()->Graphic());
		window->draw(dayTasksManager->GetButtonClose()->Graphic());
		window->draw(*dayTasksManager->GetResourcesFoundText());
		window->draw(*dayTasksManager->GetResourcesText());
		
		DrawShotgunHasBeenFoundText();
		DrawUziHasBeenFoundText();
	}
}

void Program::DrawNotEnoughScrapText()
{
	if (HoursInterface::GetScrapNotEnoughShowText())
		window->draw(*HoursInterface::GetNotEnoughScrapText());
}

void Program::DrawRadioCheckText()
{
	if (radio->GetShowCheckText())
		window->draw(*radio->GetCheckRadioText());
}

void Program::DrawRadioDialogueText()
{
	if (radio->GetShowRadioDialogueText())
	{
		window->draw(*radio->GetRadioDialogueText());
	}
}

void Program::DrawListeningRadioText()
{
	if (radio->GetShowRadioText())
	{
		window->draw(*radio->GetRadioText());
	}
}

void Program::DrawRadioMessageText()
{
	if (radio->GetShowRadioMessageText())
	{
		window->draw(*radio->GetRadioMessageText());
	}
}

void Program::DrawRadioMessageDialogueText()
{
	if (radio->GetShowRadioMessageDialogueText())
	{
		window->draw(*radio->GetRadioMessageDialogueText());
	}
}

void Program::DrawShotgunHasBeenFoundText()
{
	if (dayTasksManager->GetShowShotgunHasBeenFoundText())
	{		
		window->draw(*dayTasksManager->GetShotgunFoundText());
	}
}

void Program::DrawUziHasBeenFoundText()
{
	if (dayTasksManager->GetShowUziHasBeenFoundText())
	{
		window->draw(*dayTasksManager->GetUziFoundText());
	}
}



void Program::DrawNightTime()
{
	DrawOutsideFloor();

	if (timeClock->GetCurrentDay() >= 5)
		DrawSOSSign();

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
	for (int i = 0; i < Weapon::totalBullets; i++)
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

void Program::DrawToolbox()
{
	window->draw(toolbox->Graphic());
}

void Program::DrawPlanks()
{
	window->draw(planks->Graphic());
}

void Program::DrawBricks()
{
	window->draw(bricks->Graphic());
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


void Program::DrawFencesHealthPercentageText()
{
	window->draw(*Fence::GetPercentageText());
}

void Program::DrawCarHealthPercentageText()
{
	window->draw(*car->GetPercentageText());
}

void Program::DrawHouseHealthPercentageText()
{
	window->draw(*house->GetPercentageText());
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
	if(player->GetCurrentWeapon().GetTag() == Tag::Gun)
		window->draw(hud->GetGunAmmoHolder()->Graphic());
	else if (player->GetCurrentWeapon().GetTag() == Tag::Shotgun)
		window->draw(hud->GetShotgunAmmoHolder()->Graphic());
	else if (player->GetCurrentWeapon().GetTag() == Tag::Uzi)
		window->draw(hud->GetUziAmmoHolder()->Graphic());

}

void Program::DrawDate()
{
	window->draw(*timeClock->GetDateText());
}



void Program::DrawTransitionScreen()
{
	window->draw(sceneManager->GetBlackScreenTransition()->Graphic());
}


void Program::DrawEndDayText()
{
	if (TimeClock::GetEndDayTextOpened())
	{
		sceneManager->SetIsTransitioning(true);

		window->draw(timeClock->GetBackground()->Graphic());
		window->draw(timeClock->GetButtonClose()->Graphic());
		window->draw(*timeClock->GetEndDayText());

		radio->SetWasUsed(false);
	}
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

	DrawRadioCheckText();

	DrawListeningRadioText();

	DrawRadioDialogueText();

	DrawRadioMessageText();

	DrawRadioMessageDialogueText();

	DrawScavengeResults();

	DrawEndDayText();
	
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

	if (timeClock->GetCurrentDay() >= 4)
		DrawSOSSign();

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

	DrawToolbox();

	DrawPlanks();

	DrawBricks();

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

	DrawCarHoursInterface();

	/*DrawCarCollider();

	DrawToolboxCollider();

	DrawPlanksCollider();

	DrawBricksCollider();*/
	
}

void Program::DrawPlayerInHouse()
{
	DrawInteriorFloor();

	DrawInteriorWalls();

	DrawCalendar();

	DrawBoard();

	DrawLimits();

	DrawBed();

	DrawRadio();

	DrawChairs();

	DrawTable();
	
	if(sceneManager->GetIsTitleScene())
		DrawBook();

	DrawPlayer();

	/*DrawDoorCollider();

	DrawBedCollider();

	DrawRadioCollider();*/

	/*DrawBookCollider();

	DrawCalendarCollider();

	DrawBoardCollider();*/
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

void Program::DrawBook()
{
	window->draw(book->Graphic());
}

void Program::DrawCalendar()
{
	window->draw(calendar->Graphic());
}

void Program::DrawBoard()
{
	window->draw(board->Graphic());
}

void Program::DrawTitle()
{
	window->draw(title->Graphic());
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

void Program::DrawCarCollider()
{
	window->draw(carCollider->Graphic());
}

void Program::DrawToolboxCollider()
{
	window->draw(toolboxCollider->Graphic());
}

void Program::DrawPlanksCollider()
{
	window->draw(planksCollider->Graphic());
}

void Program::DrawBricksCollider()
{
	window->draw(bricksCollider->Graphic());
}

void Program::DrawBookCollider()
{
	window->draw(bookCollider->Graphic());
}

void Program::DrawCalendarCollider()
{
	window->draw(calendarCollider->Graphic());
}

void Program::DrawBoardCollider()
{
	window->draw(boardCollider->Graphic());
}

void Program::DrawCarWindow()
{
	if (carWindow->GetIsActive())
	{
		window->draw(carWindow->GetBackground()->Graphic());
		window->draw(carWindow->GetButtonClose()->Graphic());

		window->draw(*carWindow->GetText());

		window->draw(carWindow->GetOkButton()->Graphic());
		window->draw(carWindow->GetCancelButton()->Graphic());
	}
}

void Program::DrawBookWindow()
{
	if (bookWindow->GetIsActive())
	{
		window->draw(bookWindow->GetBackground()->Graphic());
		window->draw(bookWindow->GetButtonClose()->Graphic());

		window->draw(*bookWindow->GetText());
	}
}

void Program::DrawCalendarWindow()
{
	if (calendarWindow->GetIsActive())
	{
		window->draw(calendarWindow->GetBackground()->Graphic());
		window->draw(calendarWindow->GetButtonClose()->Graphic());

		window->draw(*calendarWindow->GetText());
	}
}

void Program::DrawBoardWindow()
{
	if (boardWindow->GetIsActive())
	{
		window->draw(boardWindow->GetBackground()->Graphic());
		window->draw(boardWindow->GetButtonClose()->Graphic());

		window->draw(*boardWindow->GetText());
	}
}

void Program::DrawBedWindow()
{
	if (bedWindow->GetIsActive())
	{
		window->draw(bedWindow->GetBackground()->Graphic());
		window->draw(bedWindow->GetButtonClose()->Graphic());

		window->draw(*bedWindow->GetText());

		window->draw(bedWindow->GetOkButton()->Graphic());
		window->draw(bedWindow->GetCancelButton()->Graphic());
	}
}

void Program::DrawRadioWindow()
{
	if (radioWindow->GetIsActive())
	{
		window->draw(radioWindow->GetBackground()->Graphic());
		window->draw(radioWindow->GetButtonClose()->Graphic());

		window->draw(*radioWindow->GetText());
	}
}

void Program::DrawSOSSign()
{	
	window->draw(sosSign->Graphic());
}

void Program::DrawGameOverText(float delaTime)
{	
	if (sceneManager->GetIsGameOver())
	{		
		if(gameOverTimer < 5)
		{ 
			gameOverTimer += deltaTime;
			restartText->setPosition(1400, 603);
			mainMenuText->setPosition(1400, 660);
			exitText->setPosition(1400, 720);
		}

		if (gameOverTimer >= 5)
		{
			restartText->setPosition(612, 603);
			mainMenuText->setPosition(600, 660);
			exitText->setPosition(625, 720);

			window->draw(*restartText);
			window->draw(*mainMenuText);
			window->draw(*exitText);
		}	
	}
}

void Program::DrawEndingText()
{
	if (!eEndingPressed)
	{
		if (isGoodEnding)
			window->draw(*goodEndingText);
		else if (isBadEnding)
			window->draw(*badEndingText);
	}

}

void Program::DrawHours()
{	
	window->draw(*timeClock->GetTimeText());
}

void Program::Ending(float deltaTime)
{
	if (sceneManager->GetDisplayEnding())
	{
		endingTimer += deltaTime;

		if (endingTimer >= 2)
		{
			if (SOSSign::GetSignBuilt())
			{
				isGoodEnding = true;
			}
			else
			{
				isBadEnding = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				eEndingPressed = true;
			}
		}
		
	}	

	if (eEndingPressed)
	{
		toMainMenuTimer += deltaTime;

		if (toMainMenuTimer >= 3)
		{
			GoMainMenu();
		}
	}
}

void Program::RestartGame()
{	
	player->ResetPlayer();

	timeClock->ResetTimeClock();
	sceneManager->ResetSceneManager();

	enemySpawner->ResetEnemySpawner();

	for (int i = 0; i < fences.size(); i++)
		fences[i]->ResetFence();

	house->ResetHouse();

	car->ResetCar();

	radio->ResetRadio();

	sosSign->ResetSOSSign();

	gameOverTimer = 0;		
	endingTimer = 0;

	isGoodEnding = false;
	isBadEnding = false;

	eEndingPressed = false;

	toMainMenuTimer = 0;
}

void Program::GoMainMenu()
{	
	carWindow->SetIsActive(false);
	bookWindow->SetIsActive(false);
	calendarWindow->SetIsActive(false);
	boardWindow->SetIsActive(false);
	bedWindow->SetIsActive(false);
	radioWindow->SetIsActive(false);

	player->ResetPlayer();

	timeClock->ResetTimeClock();
	sceneManager->MainMenuSceneManager();

	enemySpawner->ResetEnemySpawner();

	for (int i = 0; i < fences.size(); i++)
		fences[i]->ResetFence();

	house->ResetHouse();

	car->ResetCar();

	radio->ResetRadio();

	sosSign->ResetSOSSign();

	gameOverTimer = 0;
	endingTimer = 0;

	isGoodEnding = false;
	isBadEnding = false;

	eEndingPressed = false;

	toMainMenuTimer = 0;
}
