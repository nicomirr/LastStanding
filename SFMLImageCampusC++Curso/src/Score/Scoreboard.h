#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "SFML/Graphics.hpp"
#include "../Entities/Player/Player.h"
#include "../Entities/TimeClock/TimeClock.h"
#include "../Entities/Enviroment/SOSSign.h"

struct ScoreData
{
	std::string name;
	int score;
	int day; 
	std::string status;

	ScoreData();

};

class Scoreboard
{
private:
	const int totalScores = 5;
	const std::string scoresFilePath = "res/data/Highscores.dat";

	std::vector<ScoreData*> playerScores;

	bool newHighscore;
	int newHighscoreIndex;
	std::string newHighscoreName;

	bool inputNewHighscoreName;
	bool newHighscoreChecked;

	std::vector<std::string> highscores;

	sf::Font* font;

	sf::Text* nameText;
	sf::Text* scoreText;
	sf::Text* dayText;
	sf::Text* statusText;

	sf::Text* scoreNames;
	sf::Text* scorePoints;
	sf::Text* scoreDay;
	sf::Text* scoreStatus;
	
	Entity* newHighscorePopup;
	

	void ReadHighScores();
	void WriteHighScores();

public:
	Scoreboard();

	sf::Text* GetNameText() { return nameText; }
	sf::Text* GetScoreText() { return scoreText; }
	sf::Text* GetDayText() { return dayText; }
	sf::Text* GetStatusText() { return statusText; }

	sf::Text* GetScoreNamesText() { return scoreNames; }
	sf::Text* GetScorePointsText() { return scorePoints; }
	sf::Text* GetScoreDayText() { return scoreDay; }
	sf::Text* GetScoreStatusText() { return scoreStatus; }

	bool GetInputNewHighscoreName() { return inputNewHighscoreName; }
	void SetInputNewHighscoreName(bool value) { inputNewHighscoreName = value; }
	void SetNewHighscoreName(std::string name) { newHighscoreName = name; }

	Entity* GetNewHighScorePopup() { return newHighscorePopup; }

	void CheckForNewHighScore();
	void AddNewHighScore();

	void ResetScoreBoard();

};

