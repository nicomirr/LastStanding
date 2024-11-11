#pragma once

#include<iostream>
#include <SFML/Graphics.hpp>
#include "../Entities/Player/Player.h"
#include "../Entities/Enemy/EnemySpawner.h"
#include "../Entities/Enviroment/Fence.h"
#include "../Entities/Entity.h"
#include "../Entities/Enviroment/House.h"
#include "../Entities/Enviroment/Car.h"
#include "../Collisions/CollisionHandler.h"
#include "../Collisions/BaseAreaCollider.h"
#include "../BreadthFirstSearch/Node.h"
#include "../BreadthFirstSearch/GridManager.h"
#include "../BreadthFirstSearch/Pathfinder.h"
#include "../Entities/HUD/HUD.h"
#include "../Entities/TimeClock/TimeClock.h"
#include "../Entities/Enviroment/Wall.h"
#include "../Entities/Enviroment/Bed.h"
#include "../Entities/Enviroment/Radio.h"
#include "../SceneManager/SceneManager.h"
#include "../DayTasksManager/DayTasksManager.h"
#include "../Entities/Enviroment/SOSSign.h"
#include "../Entities/HUD/PopUpWindow.h"


class Program
{
public: 
	Program();
	void Run();
	static sf::Vector2i const GetMousePosition(){ return mousePosition; }

private:
	int windowWidth;
	int windowHeight;

	sf::Cursor cursor;
	sf::Image cursorImage;
	std::string cursorImageFilePath;

	static sf::Vector2i mousePosition;
	
	//std::vector<Node*> nodeGrid;
	GridManager* nodesGrid;
	PathFinder* pathfinder;

	SceneManager* sceneManager;

	HUD* hud;
	TimeClock* timeClock;	

	Entity* skyNight;
	std::vector<AnimatedEntity*> floor;

	BaseAreaCollider* baseAreaCollider;

	Weapon* gun;
	Weapon* shotgun;
	Weapon* uzi;

	Player* player;
	EnemySpawner* enemySpawner;
	
	std::vector<Fence*> fences;
	House* house;
	Car* car;
	
	Entity* interiorFloor;
	Wall* interiorUpWall;
	Entity* limitLeft;
	Entity* limitRight;
	Entity* limitDown;
	Bed* bed;
	Radio* radio;
	Entity* chairLeft;
	Entity* chairRight;
	Entity* table;
	Entity* wardrobe;

	Entity* doorColliderOutside;
	Entity* doorColliderInside;
	Entity* bedCollider;
	Entity* radioCollider;
	Entity* carCollider;
	Entity* toolboxCollider;
	Entity* planksCollider;
	Entity* bricksCollider;

	Entity* bookCollider;
	Entity* calendarCollider;
	Entity* boardCollider;

	Entity* toolbox;
	Entity* planks;
	Entity* bricks;

	Entity* book;
	Entity* calendar;
	Entity* board;

	PopUpWindow* carWindow;
	PopUpWindow* bookWindow;
	PopUpWindow* calendarWindow;
	PopUpWindow* boardWindow;
	PopUpWindow* bedWindow;
	PopUpWindow* radioWindow;


	Entity* title;

	Entity* mainMenuButton;
	Entity* exitButton;


	HoursInterface* carHoursInterface;
	HoursInterface* toolboxHoursInterface;
	HoursInterface* planksHoursInterface;
	HoursInterface* bricksHoursInterface;
	
	SOSSign* sosSign;

	bool isProgramRunning;
	float deltaTime;
	sf::Clock clock;

	sf::RenderWindow* window;

	DayTasksManager* dayTasksManager;

	sf::Font* font;

	sf::Text* restartText;
	sf::Text* mainMenuText;
	sf::Text* exitText;

	sf::Text* goodEndingText;
	sf::Text* badEndingText;

	bool isGoodEnding;
	bool isBadEnding;

	float gameOverTimer;
	float endingTimer;

	bool eEndingPressed;
	
	float toMainMenuTimer;

	void Initialize();
	void DeInitialize();
	void ProgramLoop();

	void Input();
	void Update();
	void Draw();

	void CreateWindow();
	void CreateSceneManager();
	void SetCursorAppearance();
	void CreateWeapons();
	void CreatePlayer();
	void CreateHUD();
	void CreateNightSky();
	void CreateClock();
	void CreatePlayerBaseCollider();
	void CreateOutsideFloor();
	void CreateFences();
	void CreateHouse();
	void CreateCar();
	void CreateToolbox();
	void CreatePlanks();
	void CreateBricks();
	void CreateDoorColliderOutside();
	void CreateSOSSign();

	void CreateInteriorFloor();
	void CreateInteriorWall();
	void CreateInteriorLimits();
	void CreateBed();
	void CreateRadio();
	void CreateChairs();
	void CreateTable();

	void CreateBook();
	void CreateCalendar();
	void CreateBoard();

	void CreateCarWindow();
	void CreateBookWindow();
	void CreateCalendarWindow();
	void CreateBoardWindow();
	void CreateBedWindow();
	void CreateRadioWindow();

	void CreateTitle();

	void CreateDoorColliderInside();
	void CreateBedCollider();
	void CreateRadioCollider();
	void CreateCarCollider();
	void CreateToolboxCollider();
	void CreatePlanksCollider();
	void CreateBricksCollider();

	void CreateBookCollider();
	void CreateCalendarCollider();
	void CreateBoardCollider();
	
	void CreateCarHoursInterface();
	void CreateToolboxHoursInterface();
	void CreatePlanksHoursInterface();
	void CreateBricksHoursInterface();

	void CreateDaysTasksManager();

	void CreateFont();
	void CreateGameOverOptions();

	void CreateEndingTexts();

	void NightTimeUpdate(float deltaTime);	
	void DayTimeUpdate(float deltaTime);

	void UpdateHourInterfaces(float deltaTime);

	void UpdateGameOver();

	void DrawPlayer();
	void DrawEButton();	

	void DrawHoursInterfaces();

	void DrawBedHoursInterface();
	void DrawCarHoursInterface();
	void DrawToolboxHoursInterface();
	void DrawPlanksHoursInterface();
	void DrawBricksHoursInterface();
	void DrawSOSSignHoursInterface();

	void DrawScavengeResults();	

	void DrawNotEnoughScrapText();

	void DrawRadioCheckText();
	void DrawRadioDialogueText();
	void DrawListeningRadioText();

	void DrawRadioMessageText();
	void DrawRadioMessageDialogueText();

	void DrawShotgunHasBeenFoundText();
	void DrawUziHasBeenFoundText();

	void DrawNightTime();
	void DrawOutsideFloor();
	void DrawFences();
	void DrawBullets();
	void DrawWeapon();
	void DrawHouse();
	void DrawCar();
	void DrawToolbox();
	void DrawPlanks();
	void DrawBricks();
	void DrawSky();
	void DrawEnemiesHealthBars();
	void DrawHouseHealthBar();
	void DrawCarHealthBar();
	
	void DrawFencesHealthPercentageText();
	void DrawCarHealthPercentageText();
	void DrawHouseHealthPercentageText();


	void DrawDayTime();
	 
	void DrawInsideHouse();
	void DrawOutsideHouse();
	
	void DrawPlayerInHouse();
	void DrawInteriorFloor();
	void DrawInteriorWalls();
	void DrawLimits();
	void DrawBed();
	void DrawRadio();
	void DrawChairs();
	void DrawTable();

	void DrawBook();
	void DrawCalendar();
	void DrawBoard();

	void DrawTitle();
		
	void DrawDoorColliderInside();
	void DrawBedCollider();
	void DrawRadioCollider();		
	void DrawDoorColliderOutside();
	void DrawCarCollider();
	void DrawToolboxCollider();
	void DrawPlanksCollider();
	void DrawBricksCollider();

	void DrawBookCollider();
	void DrawCalendarCollider();
	void DrawBoardCollider();

	void DrawCarWindow();
	void DrawBookWindow();
	void DrawCalendarWindow();
	void DrawBoardWindow();
	void DrawBedWindow();
	void DrawRadioWindow();

	void DrawSOSSign();

	void DrawGameOverText(float delaTime);

	void DrawEndingText();

	void DrawTimeClock();
	void DrawHUD();
	void DrawHours();
	void DrawAmmoText();
	void DrawHUDBullets();
	void DrawDate();
	
	void DrawTransitionScreen();

	void DrawEndDayText();
		
	void Ending(float deltaTime);

	void RestartGame();

	void GoMainMenu();

};

/*
x = 912
y = 420

*/

/*
#include CAMBIOS:
Si queremos acceder desde aca a una subcarpeta que se encuentre en la carpeta "src", deberemos
ir hacia atr�s, hasta llegar a la carpeta "src". Una vez en esta carpeta, all� si podemos crear
el camino hacia el archivo que se encuentra en la subcarpeta de "src". Para volver hacia atr�s
se utiliza siempre "../". Para acceder, por ejemplo, a nuestro archivo "Player.h" desde "Program.h"
podemos hacer lo siguiente: "#include ../Entities/Player/Player.h". Vamos hacia atr�s y luego
accedemos a todas las carpetas que haga falta hasta llegar a "Player.h".

*/