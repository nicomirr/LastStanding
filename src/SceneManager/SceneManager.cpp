#include "SceneManager.h"

bool SceneManager::isTransitioning = false;
bool SceneManager::isTransitionToDay = false;
bool SceneManager::isTransitionToNight = false;
bool SceneManager::isTransitionToInside = false;
bool SceneManager::isTransitionToOutside = false;

SceneManager::SceneManager()
{
	std::string blackScreenFilePath = "res\\textures\\transitions\\BlackScreen.png";
	sf::Vector2i blackScreenSpriteSheetSize = { 1200, 880 };
	blackScreenTransition = new Entity(blackScreenFilePath, blackScreenSpriteSheetSize);

	sf::Color blackScreenColor(blackScreenTransition->Graphic().getColor().r, blackScreenTransition->Graphic().getColor().g,
		blackScreenTransition->Graphic().getColor().b, 255);		

	blackScreenTransition->Graphic().setColor(blackScreenColor);

	sceneTransitionEndTime = 1;
	sceneTransitionEndTimeToStart = 5;

	SetIsNightTimeSceneOn();
	//SetIsDayTimeSceneOn();		//Testeo
}

void SceneManager::Update()
{
	SceneTransitionStart();
	SceneTransitionToInside();
	SceneTransitionToOutside();
	
	
}

void SceneManager::SetTitleSceneOn()
{
	isTitleScene = true;
	isGameOverScene = false;
	isDayTimeScene = false;
	isNightTimeScene = false;
}

void SceneManager::SetIsGameOverSceneOn()
{
	isTitleScene = false;
	isGameOverScene = true;
	isDayTimeScene = false;
	isNightTimeScene = false;
}

void SceneManager::SetIsDayTimeSceneOn()
{
	isTitleScene = false;
	isGameOverScene = false;
	isDayTimeScene = true;
	isNightTimeScene = false;
}

void SceneManager::SetIsNightTimeSceneOn()
{
	isTitleScene = false;
	isGameOverScene = false;
	isDayTimeScene = false;
	isNightTimeScene = true;
}

void SceneManager::SetIsInsidePlayerHouse()
{
	isInsidePlayerHouse = true;
	isOutsidePlayerHouse = false;
}

void SceneManager::SetIsOutsidePlayerHouse()
{
	isOutsidePlayerHouse = true;
	isInsidePlayerHouse = false;
}

void SceneManager::SceneTransitionStart()
{
	if (sceneTransitionStartFinished) return;
	
	isTransitioning = false;

	if (sceneTransitionProgress < 1.0f)
	{
		int alpha = MathsPlus::Lerp(275, 0, sceneTransitionProgress);

		sceneTransitionProgress += 0.007f;

		if (alpha <= 255)
		{
			sf::Color blackScreenColor(blackScreenTransition->Graphic().getColor().r, blackScreenTransition->Graphic().getColor().g,
				blackScreenTransition->Graphic().getColor().b, alpha);

			blackScreenTransition->Graphic().setColor(blackScreenColor);
		}

		if (alpha <= 1)
		{
			sceneTransitionProgress = 0;
			sceneTransitionStartFinished = true;
		}

	}
	
}

void SceneManager::SceneTransitionEnd(float deltaTime)
{
	sceneTransitionEndTimer += deltaTime;

	if (sceneTransitionEndTimer < sceneTransitionEndTime) return;

	if (sceneTransitionProgress < 1.0f)
	{
		int alpha = MathsPlus::Lerp(-20, 255, sceneTransitionProgress);

		sceneTransitionProgress += 0.007f;

		if (alpha >= 0)
		{
			sf::Color blackScreenColor(blackScreenTransition->Graphic().getColor().r, blackScreenTransition->Graphic().getColor().g,
				blackScreenTransition->Graphic().getColor().b, alpha);

			blackScreenTransition->Graphic().setColor(blackScreenColor);
		}
						
	}
	else if (sceneTransitionProgress >= 1)
	{		
		if (sceneTransitionEndTimer < sceneTransitionEndTimeToStart) return;

		if (isNightTimeScene)
		{
			TimeClock::SetIsNight(false);
			TimeClock::SetIsDay(true);
			SetIsDayTimeSceneOn();
			SetIsInsidePlayerHouse();
			sceneTransitionProgress = 0;
			isTransitionToDay = true;			

		}
		else if (isDayTimeScene)
		{
			TimeClock::SetIsDay(false);
			TimeClock::SetIsNight(true);
			SetIsNightTimeSceneOn();
			SetIsOutsidePlayerHouse();
			sceneTransitionProgress = 0;
			isTransitionToNight = true;

		}

		sceneTransitionStartFinished = false;
		sceneTransitionEndTimer = 0;

		isTransitioning = true;
		
	}
}

void SceneManager::SceneTransitionToOutside()
{
	if (!isTransitioningToOutside) return;

	if (sceneTransitionProgressOutsideInsideStart < 1.0f)
	{
		int alpha = MathsPlus::Lerp(0, 255, sceneTransitionProgressOutsideInsideStart);

		sceneTransitionProgressOutsideInsideStart += 0.01f;

		if (alpha >= 0)
		{
			sf::Color blackScreenColor(blackScreenTransition->Graphic().getColor().r, blackScreenTransition->Graphic().getColor().g,
				blackScreenTransition->Graphic().getColor().b, alpha);

			blackScreenTransition->Graphic().setColor(blackScreenColor);
		}

	}
		
	if (sceneTransitionProgressOutsideInsideStart < 1.0f) return;
	
	if (!isTransitionDone)
	{
		isTransitionToOutside = true;
		isTransitionDone = true;
	}

	SetIsOutsidePlayerHouse();
	isTransitioning = false;

	if (sceneTransitionProgressOutsideInsideEnd < 1.0f)
	{
		int alpha = MathsPlus::Lerp(255, 0, sceneTransitionProgressOutsideInsideEnd);

		sceneTransitionProgressOutsideInsideEnd += 0.01f;

		if (alpha < 255)
		{

			sf::Color blackScreenColor(blackScreenTransition->Graphic().getColor().r, blackScreenTransition->Graphic().getColor().g,
				blackScreenTransition->Graphic().getColor().b, alpha);

			blackScreenTransition->Graphic().setColor(blackScreenColor);
		}
	}
	else
	{
		sceneTransitionProgressOutsideInsideStart = 0;
		sceneTransitionProgressOutsideInsideEnd = 0;
		isTransitioningToOutside = false;
		isTransitionDone = false;
	}
	
		
}

void SceneManager::SceneTransitionToInside()
{
	if (!isTransitioningToInside) return;
		
	if (sceneTransitionProgressOutsideInsideStart < 1.0f)
	{
		int alpha = MathsPlus::Lerp(0, 255, sceneTransitionProgressOutsideInsideStart);

		sceneTransitionProgressOutsideInsideStart += 0.01f;

		if (alpha >= 0)
		{			
			sf::Color blackScreenColor(blackScreenTransition->Graphic().getColor().r, blackScreenTransition->Graphic().getColor().g,
				blackScreenTransition->Graphic().getColor().b, alpha);

			blackScreenTransition->Graphic().setColor(blackScreenColor);
		}

	}

	if (sceneTransitionProgressOutsideInsideStart < 1.0f) return;
		
	if (!isTransitionDone)
	{
		isTransitionToInside = true;
		isTransitionDone = true;
	}

	SetIsInsidePlayerHouse();
	isTransitioning = false;

	if (sceneTransitionProgressOutsideInsideEnd < 1.0f)
	{
		int alpha = MathsPlus::Lerp(255, 0, sceneTransitionProgressOutsideInsideEnd);

		sceneTransitionProgressOutsideInsideEnd += 0.01f;


		if (alpha <= 255)
		{
			sf::Color blackScreenColor(blackScreenTransition->Graphic().getColor().r, blackScreenTransition->Graphic().getColor().g,
				blackScreenTransition->Graphic().getColor().b, alpha);

			blackScreenTransition->Graphic().setColor(blackScreenColor);
		}

	}
	else
	{
		sceneTransitionProgressOutsideInsideStart = 0;
		sceneTransitionProgressOutsideInsideEnd = 0;
		isTransitioningToInside = false;
		isTransitionDone = false;
	}
}
