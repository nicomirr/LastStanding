#pragma once
#include "../Entities/Entity.h"
#include "../Math/MathsPlus.h"
#include "../Entities/TimeClock/TimeClock.h"
#include "../DayTasksManager/DayTasksManager.h"
#include "../Entities/Time/HoursInterface.h"

class SceneManager
{
private:
	bool isFenceTaskTransition;
	bool isToolboxTaskTransition;
	bool isHouseTaskTransition;
	bool isScavengeTaskTransition;
	bool isSleepTaskTransition;

	static bool transitionToNight;

	static bool isTransitioning;

	static bool isTransitionToDay;
	static bool isTransitionToNight;
	static bool isTransitionToInside;
	static bool isTransitionToOutside;

	bool isTransitionDone;

	bool isTransitioningToInside;
	bool isTransitioningToOutside;

	bool isTransitioningTask;

	bool canUseDoors;

	bool sceneTransitionStartFinished;
	bool isTitleScene;
	bool isGameOverScene;
	bool isDayTimeScene;
	bool isNightTimeScene;
	bool isInsidePlayerHouse;
	bool isOutsidePlayerHouse;
	Entity* blackScreenTransition;

	float sceneTransitionProgress;
	float sceneTransitionEndTime;
	float sceneTransitionEndTimeToStart;
	float sceneTransitionEndTimer;

	float sceneTransitionProgressOutsideInsideStart;
	float sceneTransitionProgressOutsideInsideEnd;		

	float sceneTransitionProgressInsideStart;
	float sceneTransitionProgressInsideEnd;

	float sceneTransitionTasksProgressStart;
	float sceneTransitionTasksProgressEnd;

public:
	SceneManager();
	
	void Update(DayTasksManager* dayTasksManager, float deltaTime);
	
	static bool GetIsTransitioning() { return isTransitioning; }

	static bool GetIsTransitionToDay() { return isTransitionToDay; }
	static bool GetIsTransitionToNight() { return isTransitionToNight; }
	static bool GetIsTransitionToInside() { return isTransitionToInside; }
	static bool GetIsTransitionToOutside() { return isTransitionToOutside; }

	bool GetIsTitleScene() { return isTitleScene; }
	bool GetIsGameOverScene() { return isGameOverScene; }
	bool GetIsDayTimeScene() { return isDayTimeScene; }
	bool GetIsNightTimeScene() { return isNightTimeScene; }
	bool GetIsInsidePlayerHouse() { return isInsidePlayerHouse; }
	bool GetIsOutsidePlayerHouse() { return isOutsidePlayerHouse; }

	bool GetCanUseDoors() { return canUseDoors; }

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

	void SetIsTransitioningToInside(bool value) { isTransitioningToInside = value; }
	void SetIsTransitioningToOutside(bool value) { isTransitioningToOutside = value; }

	void SetIsTransitioningTask(bool value) { isTransitioningTask = value; }

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
};

