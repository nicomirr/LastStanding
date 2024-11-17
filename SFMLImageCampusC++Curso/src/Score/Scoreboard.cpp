#include "Scoreboard.h"

Scoreboard::Scoreboard()
{		
	std::ifstream scoresFileRead(scoresFilePath);

	if (scoresFileRead.is_open())
	{
		scoresFileRead.close();
	}
	else
	{
		std::ofstream scoresFileWrite(scoresFilePath);

		if (scoresFileWrite.is_open())
		{
			scoresFileWrite << "Sami,1200,6,Rescued\nNick,1100,6,Survived\nJohn,775,5,Dead\nElia,365,3,Dead\nJudi,280,2,Dead";
			scoresFileWrite.close();
		}
	}

	for(int i = 0; i < totalScores; i++)
	{ 		
		playerScores.push_back(new ScoreData());
	}
		
	ReadHighScores();

	std::ostringstream scoreOneStream;
	std::string scoreOneString;

	std::ostringstream scoreTwoStream;
	std::string scoreTwoString;

	std::ostringstream scoreThreeStream;
	std::string scoreThreeString;

	std::ostringstream scoreFourStream;
	std::string scoreFourString;

	std::ostringstream scoreFiveStream;
	std::string scoreFiveString;
	


	scoreOneStream << std::setw(4) << std::setfill('0') << playerScores[0]->score;
	scoreOneString = scoreOneStream.str();

	highscores.push_back(playerScores[0]->name + "     " + scoreOneString + "     " + std::to_string(playerScores[0]->day) +
		"     " + playerScores[0]->status);
	

	
	scoreTwoStream << std::setw(4) << std::setfill('0') << playerScores[1]->score;
	scoreTwoString = scoreTwoStream.str();

	highscores.push_back(playerScores[1]->name + "     " + scoreTwoString + "     " + std::to_string(playerScores[1]->day) +
		"     " + playerScores[1]->status);



	scoreThreeStream << std::setw(4) << std::setfill('0') << playerScores[2]->score;
	scoreThreeString = scoreThreeStream.str();

	highscores.push_back(playerScores[2]->name + "     " + scoreThreeString + "     " + std::to_string(playerScores[2]->day) +
		"     " + playerScores[2]->status);



	scoreFourStream << std::setw(4) << std::setfill('0') << playerScores[3]->score;
	scoreFourString = scoreFourStream.str();

	highscores.push_back(playerScores[3]->name + "     " + scoreFourString + "     " + std::to_string(playerScores[3]->day) +
		"     " + playerScores[3]->status);

	

	scoreFiveStream << std::setw(4) << std::setfill('0') << playerScores[4]->score;
	scoreFiveString = scoreFiveStream.str();

	highscores.push_back(playerScores[4]->name + "     " + scoreFiveString + "     " + std::to_string(playerScores[4]->day) +
		"     " + playerScores[4]->status);


	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Pixel.otf";
	font->loadFromFile(fontPath);

	sf::Color redColor = sf::Color(200, 50, 50, 255);

	nameText = new sf::Text("Name", *font, 11);
	scoreText = new sf::Text("Score", *font, 11);
	dayText = new sf::Text("Day", *font, 11);
	statusText = new sf::Text("Status", *font, 11);

	nameText->setFillColor(redColor);
	scoreText->setFillColor(redColor);
	dayText->setFillColor(redColor);
	statusText->setFillColor(redColor);

	nameText->setPosition(460, 400);
	scoreText->setPosition(550, 400);
	dayText->setPosition(610, 400);
	statusText->setPosition(670, 400);

	scoreNames = new sf::Text(playerScores[0]->name + "\n" + playerScores[1]->name + "\n" + playerScores[2]->name + "\n" + 
		playerScores[3]->name + "\n" + playerScores[4]->name, *font, 10);
	scorePoints = new sf::Text(scoreOneString + "\n" + scoreTwoString + "\n" + scoreThreeString + "\n" + scoreFourString + "\n" + scoreFiveString,
		*font, 10);
	scoreDay = new sf::Text(std::to_string(playerScores[0]->day) + "\n" + std::to_string(playerScores[1]->day) + "\n" +
		std::to_string(playerScores[2]->day) + "\n" + std::to_string(playerScores[3]->day) + "\n" +
		std::to_string(playerScores[4]->day), *font, 10);
	scoreStatus = new sf::Text(playerScores[0]->status + "\n" + playerScores[1]->status + "\n" + playerScores[2]->status + "\n" +
		playerScores[3]->status + "\n" + playerScores[4]->status, *font, 10);

	sf::Color color = sf::Color(0, 0, 0, 255);

	scoreNames->setFillColor(color);
	scorePoints->setFillColor(color);
	scoreDay->setFillColor(color);
	scoreStatus->setFillColor(color);

	scoreNames->setPosition(460, 425);		
	scorePoints->setPosition(555, 425);
	scoreDay->setPosition(627, 425);
	scoreStatus->setPosition(665, 425);
	
	std::string newHighscorePopupImageFilePath = "res\\textures\\scoreboard\\NewScore.png";
	sf::Vector2i newHighscorePopupSpriteSize = { 168, 107 };

	newHighscorePopup = new Entity(newHighscorePopupImageFilePath, newHighscorePopupSpriteSize);

	newHighscorePopup->Graphic().setOrigin(84, 54);
	newHighscorePopup->Graphic().setPosition(630, 425);
	newHighscorePopup->Graphic().setScale(3, 3);
}

void Scoreboard::ReadHighScores()
{
	std::ifstream scoresFileRead(scoresFilePath);
	if (scoresFileRead.is_open())
	{
		std::string line;

		int i = 0;

		while (std::getline(scoresFileRead, line))
		{
			std::stringstream ss(line);

			std::getline(ss, playerScores[i]->name, ',');

			std::string scoreString;
			std::getline(ss, scoreString, ',');
			playerScores[i]->score = std::stoi(scoreString);

			std::string waveString;
			std::getline(ss, waveString, ',');
			playerScores[i]->day = std::stoi(waveString);

			std::getline(ss, playerScores[i]->status);

			if (i < playerScores.size() - 1)
				i++;
		}

	}

}

void Scoreboard::WriteHighScores()
{
	std::ofstream scoresFileWrite(scoresFilePath);

	if (scoresFileWrite.is_open())
	{
		scoresFileWrite << playerScores[0]->name + "," + std::to_string(playerScores[0]->score) + "," + std::to_string(playerScores[0]->day) + "," +
			playerScores[0]->status + "\n" + playerScores[1]->name + "," + std::to_string(playerScores[1]->score) + "," +
			std::to_string(playerScores[1]->day) + "," + playerScores[1]->status + "\n" + playerScores[2]->name + "," + std::to_string(playerScores[2]->score) +
			"," + std::to_string(playerScores[2]->day) + "," + playerScores[2]->status + "\n" + playerScores[3]->name + "," +
			std::to_string(playerScores[3]->score) + "," + std::to_string(playerScores[3]->day) + "," + playerScores[3]->status + "\n" +
			playerScores[4]->name + "," + std::to_string(playerScores[4]->score) + "," + std::to_string(playerScores[4]->day) + "," +
			playerScores[4]->status;

		scoresFileWrite.close();

		ReadHighScores();

		std::ostringstream scoreOneStream;
		std::string scoreOneString;

		std::ostringstream scoreTwoStream;
		std::string scoreTwoString;

		std::ostringstream scoreThreeStream;
		std::string scoreThreeString;

		std::ostringstream scoreFourStream;
		std::string scoreFourString;

		std::ostringstream scoreFiveStream;
		std::string scoreFiveString;

		highscores.clear();

		scoreOneStream << std::setw(4) << std::setfill('0') << playerScores[0]->score;
		scoreOneString = scoreOneStream.str();

		highscores.push_back(playerScores[0]->name + "     " + scoreOneString + "     " + std::to_string(playerScores[0]->day) +
			"     " + playerScores[0]->status);



		scoreTwoStream << std::setw(4) << std::setfill('0') << playerScores[1]->score;
		scoreTwoString = scoreTwoStream.str();

		highscores.push_back(playerScores[1]->name + "     " + scoreTwoString + "     " + std::to_string(playerScores[1]->day) +
			"     " + playerScores[1]->status);



		scoreThreeStream << std::setw(4) << std::setfill('0') << playerScores[2]->score;
		scoreThreeString = scoreThreeStream.str();

		highscores.push_back(playerScores[2]->name + "     " + scoreThreeString + "     " + std::to_string(playerScores[2]->day) +
			"     " + playerScores[2]->status);



		scoreFourStream << std::setw(4) << std::setfill('0') << playerScores[3]->score;
		scoreFourString = scoreFourStream.str();

		highscores.push_back(playerScores[3]->name + "     " + scoreFourString + "     " + std::to_string(playerScores[3]->day) +
			"     " + playerScores[3]->status);



		scoreFiveStream << std::setw(4) << std::setfill('0') << playerScores[4]->score;
		scoreFiveString = scoreFiveStream.str();

		highscores.push_back(playerScores[4]->name + "     " + scoreFiveString + "     " + std::to_string(playerScores[4]->day) +
			"     " + playerScores[4]->status);


		scoreNames->setString(playerScores[0]->name + "\n" + playerScores[1]->name + "\n" + playerScores[2]->name + "\n" +
			playerScores[3]->name + "\n" + playerScores[4]->name);

		scorePoints->setString(scoreOneString + "\n" + scoreTwoString + "\n" + scoreThreeString + "\n" + scoreFourString + "\n" + scoreFiveString);

		scoreDay->setString(std::to_string(playerScores[0]->day) + "\n" + std::to_string(playerScores[1]->day) + "\n" +
			std::to_string(playerScores[2]->day) + "\n" + std::to_string(playerScores[3]->day) + "\n" +
			std::to_string(playerScores[4]->day));

		scoreStatus->setString(playerScores[0]->status + "\n" + playerScores[1]->status + "\n" + playerScores[2]->status + "\n" +
			playerScores[3]->status + "\n" + playerScores[4]->status);

		inputNewHighscoreName = false;

	}
}

void Scoreboard::CheckForNewHighScore()
{
	std::cout << "Player score: " + std::to_string(Player::GetScore()) << std::endl;

	for (int i = 0; i < playerScores.size(); i++)
	{
		std::cout << playerScores[i]->score << std::endl;

		if (Player::GetScore() > playerScores[i]->score)
		{
			newHighscore = true;
			newHighscoreIndex = i;

			break;
		}
	}

	if (newHighscore && !newHighscoreChecked)
	{
		inputNewHighscoreName = true;
		newHighscoreChecked = true;
	}
	
}

void Scoreboard::AddNewHighScore()
{	
	playerScores[newHighscoreIndex]->name = newHighscoreName;
	playerScores[newHighscoreIndex]->score = Player::GetScore();
	playerScores[newHighscoreIndex]->day = TimeClock::GetCurrentDay();

	if (TimeClock::GetCurrentDay() < 6)
		playerScores[newHighscoreIndex]->status = "Dead";
	else
	{
		if(SOSSign::GetSignBuilt())
			playerScores[newHighscoreIndex]->status = "Rescued";
		else
			playerScores[newHighscoreIndex]->status = "Survived";

	}

	WriteHighScores();
	newHighscore = false;

}

void Scoreboard::ResetScoreBoard()
{
	newHighscore = false;
	inputNewHighscoreName = false;
	newHighscoreChecked = false;
}

void Scoreboard::Destroy()
{
	for (int i = 0; i < playerScores.size(); i++)
	{
		if (playerScores[i] != nullptr)
		{
			delete playerScores[i];
			playerScores[i] = nullptr;
		}
	}

	if (font != nullptr)
	{
		delete font;
		font = nullptr;
	}

	if (nameText != nullptr)
	{
		delete nameText;
		nameText = nullptr;
	}

	if (scoreText != nullptr)
	{
		delete scoreText;
		scoreText = nullptr;
	}

	if (dayText != nullptr)
	{
		delete dayText;
		dayText = nullptr;
	}

	if (statusText != nullptr)
	{
		delete statusText;
		statusText = nullptr;
	}

	if (scoreNames != nullptr)
	{
		delete scoreNames;
		scoreNames = nullptr;
	}

	if (scorePoints != nullptr)
	{
		delete scorePoints;
		scorePoints = nullptr;
	}

	if (scoreDay != nullptr)
	{
		delete scoreDay;
		scoreDay = nullptr;
	}

	if (scoreStatus != nullptr)
	{
		delete scoreStatus;
		scoreStatus = nullptr;
	}

	if (newHighscorePopup)
	{
		delete newHighscorePopup;
		newHighscorePopup = nullptr;
	}
}


ScoreData::ScoreData(){}
