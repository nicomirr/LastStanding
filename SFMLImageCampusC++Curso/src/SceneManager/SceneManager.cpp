#include "SceneManager.h"

bool SceneManager::isTransitioning = false;
bool SceneManager::isTransitionToDay = false;
bool SceneManager::isTransitionToNight = false;
bool SceneManager::isTransitionToInside = false;
bool SceneManager::isTransitionToOutside = false;
bool SceneManager::transitionToNight = false;
bool SceneManager::isEnding = false;
bool SceneManager::isTitleScene;
bool SceneManager::isInsidePlayerHouse;
bool SceneManager::isOutsidePlayerHouse;
bool SceneManager::displayEnding;
bool SceneManager::isDayTimeScene;

SceneManager::SceneManager()
{
	std::string  helicopterFilePath = "res\\audio\\ending\\Helicopter.mp3";
	helicopterBuffer.loadFromFile(helicopterFilePath);

	helicopterSound.setBuffer(helicopterBuffer);
	helicopterSound.setVolume(100);
	helicopterSound.setLoop(false);

	std::string blackScreenFilePath = "res\\textures\\transitions\\BlackScreen.png";
	sf::Vector2i blackScreenSpriteSheetSize = { 1200, 880 };
	blackScreenTransition = new Entity(blackScreenFilePath, blackScreenSpriteSheetSize);

	sf::Color blackScreenColor(blackScreenTransition->Graphic().getColor().r, blackScreenTransition->Graphic().getColor().g,
		blackScreenTransition->Graphic().getColor().b, 255);		

	blackScreenTransition->Graphic().setColor(blackScreenColor);

	sceneTransitionEndTime = 1;
	sceneTransitionEndTimeToStart = 5;

	canUseDoors = true;

	isOutsidePlayerHouse = true;

	SetTitleSceneOn();
	//SetIsNightTimeSceneOn();
	//SetIsDayTimeSceneOn();		//Testeo
}

void SceneManager::Update(DayTasksManager* dayTasksManager, float deltaTime, bool sosBuilt)
{
	UpdateSound();

	GameOverScreen(deltaTime);
	EndScreen(deltaTime, sosBuilt);

	SceneTransitionStart();
	SceneTransitionToInside();
	SceneTransitionToOutside();
	TasksTransition(dayTasksManager);

	TitleToGame();


	if (transitionToNight)
		SceneTransitionEndNightDayCicle(deltaTime);
	
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

	SetIsInsidePlayerHouse();
}

void SceneManager::SetIsNightTimeSceneOn()
{
	isTitleScene = false;
	isGameOverScene = false;
	isDayTimeScene = false;
	isNightTimeScene = true;

	SetIsOutsidePlayerHouse();
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

//SUMAR DIA
//CAMBIAR LUZ A OSCURIDAD
//REINICIAR RELOJ HACIA LUNA
void SceneManager::SceneTransitionEndNightDayCicle(float deltaTime)
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
			transitionToNight = false;
			TimeClock::SetEndDayTextShown(false);
			TimeClock::SetEndDayTextOpened(false);
			TimeClock::AddDay();
			TimeClock::ResetClockAndLight();
		}

		sceneTransitionStartFinished = false;
		sceneTransitionEndTimer = 0;
				
		isTransitioning = true;
		
	}
}

void SceneManager::SceneTransitionToOutside()
{
	if (!isTransitioningToOutside) return;

	canUseDoors = false;

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
		canUseDoors = true;
	}
	
		
}

void SceneManager::SceneTransitionToInside()
{
	if (!isTransitioningToInside) return;

	canUseDoors = false;
		
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
		canUseDoors = true;
	}
}


//CONTINUAR ACA

void SceneManager::TasksTransition(DayTasksManager* dayTaskManager)
{
	//en collisionhandler activar istransitioning
	//un return para que no vuelva a ejecutarse?	
	if (!isTransitioningTask) return;

	if (sceneTransitionTasksProgressStart < 1.0f)
	{
		int alpha = MathsPlus::Lerp(0, 255, sceneTransitionTasksProgressStart);

		sceneTransitionTasksProgressStart += 0.01f;

		if (alpha >= 0)
		{
			sf::Color blackScreenColor(blackScreenTransition->Graphic().getColor().r, blackScreenTransition->Graphic().getColor().g,
				blackScreenTransition->Graphic().getColor().b, alpha);

			blackScreenTransition->Graphic().setColor(blackScreenColor);
		}

	}

	if (sceneTransitionTasksProgressStart < 1.0f) return;
		
	if (isFenceTaskTransition)
	{
		dayTaskManager->RepairFences(HoursInterface::GetHoursToSpend());
		TimeClock::SetHours(TimeClock::GetHours() - (HoursInterface::GetHoursToSpend()));

		isFenceTaskTransition = false;
	}
	else if (isToolboxTaskTransition)
	{
		dayTaskManager->RepairCar(HoursInterface::GetHoursToSpend());
		TimeClock::SetHours(TimeClock::GetHours() - (HoursInterface::GetHoursToSpend()));

		isToolboxTaskTransition = false;
	}
	else if (isHouseTaskTransition)
	{
		dayTaskManager->RepairHouse(HoursInterface::GetHoursToSpend());
		TimeClock::SetHours(TimeClock::GetHours() - (HoursInterface::GetHoursToSpend()));

		isHouseTaskTransition = false;
	}
	else if (isScavengeTaskTransition)
	{
		dayTaskManager->Scavenge(HoursInterface::GetHoursToSpend());
		TimeClock::SetHours(TimeClock::GetHours() - (HoursInterface::GetHoursToSpend()));

		dayTaskManager->SetScavengeResultsOpen(true);
		isScavengeTaskTransition = false;
	}
	else if (isSleepTaskTransition)
	{
		dayTaskManager->Sleep(HoursInterface::GetHoursToSpend());
		TimeClock::SetHours(TimeClock::GetHours() - (HoursInterface::GetHoursToSpend()));

		isSleepTaskTransition = false;
	}
	

	isTransitioning = false;

	HoursInterface::ResetHoursToSpend();

	if (sceneTransitionTasksProgressEnd < 1.0f)
	{
		int alpha = MathsPlus::Lerp(255, 0, sceneTransitionTasksProgressEnd);

		sceneTransitionTasksProgressEnd += 0.01f;


		if (alpha <= 255)
		{
			sf::Color blackScreenColor(blackScreenTransition->Graphic().getColor().r, blackScreenTransition->Graphic().getColor().g,
				blackScreenTransition->Graphic().getColor().b, alpha);

			blackScreenTransition->Graphic().setColor(blackScreenColor);
		}

	}
	else
	{
		sceneTransitionTasksProgressStart = 0;
		sceneTransitionTasksProgressEnd = 0;
		isTransitioningTask = false;
		isTransitionDone = false;
	}
}

void SceneManager::GameOverScreen(float deltaTime)
{
	if (House::GetHealth() <= 0)
		Player::SetIsAlive(false);

	if (!Player::GetIsAlive())
	{
		isGameOver = true;

		gameOverTimer += deltaTime;

		if (sceneTransitionProgressToGameOver < 1.0f && gameOverTimer > 2)
		{
			int alpha = MathsPlus::Lerp(0, 255, sceneTransitionProgressToGameOver);

			sceneTransitionProgressToGameOver += 0.01f;

			if (alpha >= 0)
			{
				sf::Color blackScreenColor(blackScreenTransition->Graphic().getColor().r, blackScreenTransition->Graphic().getColor().g,
					blackScreenTransition->Graphic().getColor().b, alpha);

				blackScreenTransition->Graphic().setColor(blackScreenColor);
			}
			
		}
	}

}


void SceneManager::EndScreen(float deltaTime, bool sosBuilt)
{
	if (!isEnding) return;

	if (sosBuilt)
	{
		if (helicopterSound.getStatus() == sf::SoundSource::Stopped)
			helicopterSound.play();
	}

	endingTimer += deltaTime;

	if (endingTimer < 5) return;

	if (sceneTransitionEnding < 1.0f)
	{
		int alpha = MathsPlus::Lerp(0, 255, sceneTransitionEnding);

		sceneTransitionEnding += 0.01f;

		if (alpha >= 0)
		{
			sf::Color blackScreenColor(blackScreenTransition->Graphic().getColor().r, blackScreenTransition->Graphic().getColor().g,
				blackScreenTransition->Graphic().getColor().b, alpha);

			blackScreenTransition->Graphic().setColor(blackScreenColor);
		}

	}
	else
	{
		helicopterSound.stop();
		displayEnding = true;

	}

}

void SceneManager::TitleToGame()
{
	if (!isTransitionToGame) return;

	if (sceneTransitionProgressTitleToGameStart < 1.0f)
	{
		int alpha = MathsPlus::Lerp(0, 255, sceneTransitionProgressTitleToGameStart);

		sceneTransitionProgressTitleToGameStart += 0.01f;

		if (alpha >= 0)
		{
			sf::Color blackScreenColor(blackScreenTransition->Graphic().getColor().r, blackScreenTransition->Graphic().getColor().g,
				blackScreenTransition->Graphic().getColor().b, alpha);

			blackScreenTransition->Graphic().setColor(blackScreenColor);
		}

	}


	if (sceneTransitionProgressTitleToGameStart < 1.0f) return; 

	if(isTransitioning)
		isTransitionToNight = true;

	isTransitioning = false;

	SetIsNightTimeSceneOn();


	if (sceneTransitionProgressTitleToGameEnd < 1.0f)
	{
		int alpha = MathsPlus::Lerp(255, 0, sceneTransitionProgressTitleToGameEnd);

		sceneTransitionProgressTitleToGameEnd += 0.01f;


		if (alpha <= 255)
		{
			sf::Color blackScreenColor(blackScreenTransition->Graphic().getColor().r, blackScreenTransition->Graphic().getColor().g,
				blackScreenTransition->Graphic().getColor().b, alpha);

			blackScreenTransition->Graphic().setColor(blackScreenColor);
		}

	}
	else
	{
		sceneTransitionProgressTitleToGameStart = 0;
		sceneTransitionProgressTitleToGameEnd = 0;
		isTransitionToGame = false;
	}
}

void SceneManager::ResetSceneManager()
{	
	endingTimer = 0;

	isTransitioning = false;
	isTransitionToDay = false;
	isTransitionToNight = false;
	isTransitionToInside = false;
	isTransitionToOutside = false;
	transitionToNight = false;
	isEnding = false;
	isGameOver = false;
		
	sceneTransitionProgressToGameOver = 0;
	gameOverTimer = 0;

	sceneTransitionEnding = 0;
	endingTimer = 0;

	isTransitionDone = false;
	isTransitioningToInside = false;
	isTransitioningToOutside = false;

	isTransitioningTask = false;

	sceneTransitionStartFinished = false;

	sceneTransitionProgress = 0;
	sceneTransitionEndTime = 0;
	sceneTransitionEndTimeToStart = 0;
	sceneTransitionEndTimer = 0;

	sceneTransitionProgressOutsideInsideStart = 0;
	sceneTransitionProgressOutsideInsideEnd = 0;

	sceneTransitionProgressInsideStart = 0;
	sceneTransitionProgressInsideEnd = 0;

	sceneTransitionTasksProgressStart = 0;
	sceneTransitionTasksProgressEnd = 0;

	displayGoodEndingText = false;
	displayBadEndingText = false;

	displayEnding = false;

	SetIsNightTimeSceneOn();
}

void SceneManager::MainMenuSceneManager()
{
	endingTimer = 0;

	isTransitioning = false;
	isTransitionToDay = false;
	isTransitionToNight = false;
	isTransitionToInside = false;
	isTransitionToOutside = false;
	transitionToNight = false;
	isEnding = false;
	isGameOver = false;

	sceneTransitionProgressToGameOver = 0;
	gameOverTimer = 0;

	sceneTransitionEnding = 0;
	endingTimer = 0;

	isTransitionDone = false;
	isTransitioningToInside = false;
	isTransitioningToOutside = false;

	isTransitioningTask = false;

	sceneTransitionStartFinished = false;

	sceneTransitionProgress = 0;
	sceneTransitionEndTime = 0;
	sceneTransitionEndTimeToStart = 0;
	sceneTransitionEndTimer = 0;

	sceneTransitionProgressOutsideInsideStart = 0;
	sceneTransitionProgressOutsideInsideEnd = 0;

	sceneTransitionProgressInsideStart = 0;
	sceneTransitionProgressInsideEnd = 0;

	sceneTransitionTasksProgressStart = 0;
	sceneTransitionTasksProgressEnd = 0;

	displayGoodEndingText = false;
	displayBadEndingText = false;

	displayEnding = false;

	SetIsOutsidePlayerHouse();
	SetTitleSceneOn();
}

void SceneManager::UpdateSound()
{
	helicopterSound.setVolume(100 * AudioManager::GetAudioRegulator());
}
