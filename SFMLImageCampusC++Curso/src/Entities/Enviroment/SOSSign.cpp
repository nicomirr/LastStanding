#include "SOSSign.h"

HoursInterface* SOSSign::hoursInterface;
int SOSSign::scrap;
bool SOSSign::signBuilt;

SOSSign::SOSSign(sf::Vector2i animationFrameSize, std::string imageFilePath, sf::Vector2i spriteSheetSize) :
	AnimatedEntity(animationFrameSize, imageFilePath, spriteSheetSize)
{
	AnimationData sosSign = { 0, 0, 1, false };
	AnimationData sosSignFilled = { 0, 1, 1, false };

	AddAnimation("sosSign", sosSign);
	AddAnimation("sosSignFilled", sosSignFilled);

	SetCurrentAnimation("sosSign");

	hoursInterface = new HoursInterface();

	hoursInterface->SetInterfaceText("How much time should \n	   I build sign?");
	hoursInterface->GetInterfaceText()->setPosition(495, 390);

	CollisionHandler::AddCollision(hoursInterface->GetButtonClose());
	CollisionHandler::AddCollision(hoursInterface->GetButtonRight());
	CollisionHandler::AddCollision(hoursInterface->GetButtonLeft());

	hoursInterface->GetButtonOk()->SetTag(Tag::OkHoursButtonSOSSign);
	CollisionHandler::AddCollision(hoursInterface->GetButtonOk());

	font = new sf::Font();
	std::string fontPath = "res\\fonts\\Roboto.ttf";

	font->loadFromFile(fontPath);

	buildPercentageText = new sf::Text("Build percentage: 0%", *font, 17);
	buildPercentageText->setFillColor(sf::Color(88, 83, 74, 255));

	neededScrap = 500;
	
}

void SOSSign::Update()
{
	CheckSignBuiltStatus();
	SignAppearance();

	std::ostringstream scrapStream;
	std::string scrapString;

	scrapStream << std::setw(3) << std::setfill('0') << scrap;
	scrapString = scrapStream.str();

	buildPercentageText->setString("Scrap needed: " + scrapString + "/" + std::to_string(neededScrap));
}

void SOSSign::CheckSignBuiltStatus()
{
	if (scrap >= neededScrap)
		signBuilt = true;
}

void SOSSign::SignAppearance()
{
	if (signBuilt)
	{
		if(!SceneManager::GetIsTransitioning())
			SetCurrentAnimation("sosSignFilled");
	}
}

void SOSSign::BuildSOSSign()
{
	int scrapFound = 50 * HoursInterface::GetHoursToSpend();
	scrap += scrapFound;

	TimeClock::SetHours(TimeClock::GetHours() - (HoursInterface::GetHoursToSpend()));	
	
}

void SOSSign::ResetSOSSign()
{
	scrap = 0;
	signBuilt = false;
}

sf::FloatRect SOSSign::GetBounds()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();

	return bounds;
}

