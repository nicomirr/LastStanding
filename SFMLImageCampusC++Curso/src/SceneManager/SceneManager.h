#pragma once
#include "../Entities/Entity.h"
#include "../Math/MathsPlus.h"
#include "../Entities/TimeClock/TimeClock.h"
#include "../DayTasksManager/DayTasksManager.h"
#include "../Entities/Time/HoursInterface.h"
#include "../Entities/Player/Player.h";
#include "../Audio/AudioManager.h";

class SceneManager
{
private:
	sf::SoundBuffer helicopterBuffer;
	sf::Sound helicopterSound;

	bool isFenceTaskTransition;
	bool isToolboxTaskTransition;
	bool isHouseTaskTransition;
	bool isScavengeTaskTransition;
	bool isSleepTaskTransition;

	static bool isEnding;

	static bool transitionToNight;

	static bool isTransitioning;

	static bool isTransitionToDay;
	static bool isTransitionToNight;
	static bool isTransitionToInside;
	static bool isTransitionToOutside;

	bool isGameOver;

	bool isTransitionDone;

	bool isTransitioningToInside;
	bool isTransitioningToOutside;

	bool isTransitionToGame;
	bool isTransitionToTitle;

	bool isTransitioningTask;

	bool canUseDoors;

	bool sceneTransitionStartFinished;

	static bool isTitleScene;
	bool isGameOverScene;
	static bool isDayTimeScene;
	bool isNightTimeScene;

	bool displayGoodEndingText;
	bool displayBadEndingText;

	static bool isInsidePlayerHouse;
	static bool isOutsidePlayerHouse;

	Entity* blackScreenTransition;

	float sceneTransitionProgress;
	float sceneTransitionEndTime;
	float sceneTransitionEndTimeToStart;
	float sceneTransitionEndTimer;

	float sceneTransitionProgressTitleToGameStart;
	float sceneTransitionProgressTitleToGameEnd;

	float sceneTransitionProgressGameToTitleStart;
	float sceneTransitionProgressGameToTitleEnd;

	float sceneTransitionProgressToGameOver;
	float gameOverTimer;

	float sceneTransitionEnding;
	float endingTimer;

	float sceneTransitionProgressOutsideInsideStart;
	float sceneTransitionProgressOutsideInsideEnd;		

	float sceneTransitionProgressInsideStart;
	float sceneTransitionProgressInsideEnd;

	float sceneTransitionTasksProgressStart;
	float sceneTransitionTasksProgressEnd;

	static bool displayEnding;

public:
	SceneManager();
	
	void Update(DayTasksManager* dayTasksManager, float deltaTime, bool sosBuilt);
	
	static bool GetIsTransitioning() { return isTransitioning; }

	static bool GetIsTransitionToDay() { return isTransitionToDay; }
	static bool GetIsTransitionToNight() { return isTransitionToNight; }
	static bool GetIsTransitionToInside() { return isTransitionToInside; }
	static bool GetIsTransitionToOutside() { return isTransitionToOutside; }

	static bool GetIsTitleScene() { return isTitleScene; }
	bool GetIsGameOverScene() { return isGameOverScene; }
	static bool GetIsDayTimeScene() { return isDayTimeScene; }
	bool GetIsNightTimeScene() { return isNightTimeScene; }
	static bool GetIsInsidePlayerHouse() { return isInsidePlayerHouse; }
	static bool GetIsOutsidePlayerHouse() { return isOutsidePlayerHouse; }

	bool GetIsGameOver() { return isGameOver; }

	bool GetCanUseDoors() { return canUseDoors; }

	static bool GetDisplayEnding() { return displayEnding; }

	Entity* GetBlackScreenTransition() { return blackScreenTransition; }

	void SetIsFenceTaskTransition(bool value) { isFenceTaskTransition = value; }
	void SetIsToolboxTaskTransition(bool value) { isToolboxTaskTransition = value; }
	void SetIsHouseTaskTransition(bool value) { isHouseTaskTransition = value; }
	void SetIsScavengeTaskTransition(bool value) { isScavengeTaskTransition = value; }
	void SetIsSleepTaskTransition(bool value) { isSleepTaskTransition = value; }

	void SetIsTransitioning(bool value) { isTransitioning = value; }

	static void SetIsTransitionToDay(bool value) { isTransitionToDay = value; }
	static void SetIsTransitionToNight(bool value) { isTransitionToNight = value; }
	static void SetIsTransitionToInside(bool value) { isTransitionToInside = value; }
	static void SetIsTransitionToOutside(bool value) { isTransitionToOutside = value; }

	static void SetTransitionToNight(bool value) { transitionToNight = value; }

	static bool GetIsEnding() { return isEnding; }
	static void SetIsEnding(bool value) { isEnding = value; }

	void SetIsTransitioningToInside(bool value) { isTransitioningToInside = value; }
	void SetIsTransitioningToOutside(bool value) { isTransitioningToOutside = value; }

	void SetIsTransitioningTask(bool value) { isTransitioningTask = value; }

	void SetIsTransitionToGame(bool value) { isTransitionToGame = value; }

	void SetTitleSceneOn();
	void SetIsGameOverSceneOn();
	void SetIsDayTimeSceneOn();
	void SetIsNightTimeSceneOn();
	void SetIsInsidePlayerHouse();
	void SetIsOutsidePlayerHouse();


	void SceneTransitionStart();
	void SceneTransitionEndNightDayCicle(float deltaTime);

	void SceneTransitionToOutside();
	void SceneTransitionToInside();

	void TasksTransition(DayTasksManager* dayTaskManager);

	void GameOverScreen(float deltaTime);

	void EndScreen(float deltaTime, bool sosBuilt);

	void TitleToGame();

	void ResetSceneManager();

	void MainMenuSceneManager();

	void UpdateSound();

	void Destroy();
};

