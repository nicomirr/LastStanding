#include "CollisionHandler.h"


std::vector<Entity*> CollisionHandler::entities;
float CollisionHandler::addSubstractHoursTimer;
float CollisionHandler::okButtonTimer;

void CollisionHandler::AddCollision(Entity* entity)
{
	entities.push_back(entity);
}

void CollisionHandler::SolveCollisions(float deltaTime, SceneManager* sceneManager, sf::RenderWindow* window, HoursInterface* carHoursInterface,
	HoursInterface* toolboxHoursInterface, HoursInterface* planksHoursInterface, HoursInterface* bricksHoursInterface,
	HoursInterface* bedHoursInterface, DayTasksManager* dayTasksManager)
{
	addSubstractHoursTimer += deltaTime;
	okButtonTimer += deltaTime;

	if (sceneManager->GetIsNightTimeScene())
	{
		sf::Vector2f relativePosition;

		for (int i = 0; i < entities.size(); i++)
		{
			for (int j = 0; j < entities.size(); j++)
			{
				relativePosition = entities[i]->Graphic().getPosition() - entities[j]->Graphic().getPosition();

				if (entities[i]->GetTag() == Tag::Player && (entities[j]->GetTag() == Tag::Fence ||
					entities[j]->GetTag() == Tag::Car || entities[j]->GetTag() == Tag::House))
				{
					if (entities[i]->onCollission(*entities[i], *entities[j]))
					{
						static_cast<Player*>(entities[i])->RigidObjectCollision(deltaTime);
					}
				}

				if (entities[i]->GetTag() == Tag::Bullet && (entities[j]->GetTag() == Tag::Car ||
					entities[j]->GetTag() == Tag::House))
				{
					if (static_cast<Bullet*>(entities[i])->GetIsActive())
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
							static_cast<Bullet*>(entities[i])->SetIsActive(false);
					}
				}



				if (entities[i]->GetTag() == Tag::Bullet && entities[j]->GetTag() == Tag::Enemy)
				{
					if (static_cast<Bullet*>(entities[i])->GetIsActive())
					{
						if (static_cast<Enemy*>(entities[j])->GetIsActive())
						{
							if (entities[i]->onCollission(*entities[i], *entities[j]))
							{
								if (static_cast<Enemy*>(entities[j])->GetIsAlive())
								{
									static_cast<Enemy*>(entities[j])->
										TakeDamage(static_cast<Bullet*>(entities[i])->GetDamage());
									static_cast<Bullet*>(entities[i])->SetIsActive(false);
								}
							}
						}
					}
				}

				if (entities[i]->GetTag() == Tag::Enemy && entities[j]->GetTag() == Tag::Fence)
				{
					if (static_cast<Enemy*>(entities[i])->GetIsActive())
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							if (static_cast<Enemy*>(entities[i])->GetIsAlive() &&
								!static_cast<Enemy*>(entities[i])->GetIsAttackingPlayer() &&
								!static_cast<Fence*>(entities[j])->GetIsFenceBroken())
							{
								static_cast<Enemy*>(entities[i])->SetIsAttackingFence(true);
								static_cast<Enemy*>(entities[i])->Attack(static_cast<Fence*>(entities[j]), deltaTime);
							}
						}
					}
				}

				if (entities[i]->GetTag() == Tag::Enemy && entities[j]->GetTag() == Tag::Fence)
				{
					if (static_cast<Enemy*>(entities[i])->GetIsActive())
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							if (static_cast<Enemy*>(entities[i])->GetIsAlive() &&
								!static_cast<Enemy*>(entities[i])->GetIsAttackingPlayer() &&
								!static_cast<Fence*>(entities[j])->GetIsFenceBroken())
							{
								static_cast<Enemy*>(entities[i])->SetIsAttackingFence(true);
								static_cast<Enemy*>(entities[i])->Attack(static_cast<Fence*>(entities[j]), deltaTime);
							}
						}
					}
				}


				if (entities[i]->GetTag() == Tag::Enemy && entities[j]->GetTag() == Tag::House)
				{
					if (static_cast<Enemy*>(entities[i])->GetIsActive())
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							if (static_cast<Enemy*>(entities[i])->GetIsAlive())
							{
								static_cast<Enemy*>(entities[i])->SetIsAttackingHouse(true);
								static_cast<Enemy*>(entities[i])->SetIsAttackingPlayer(false);
								static_cast<Enemy*>(entities[i])->Attack(static_cast<House*>(entities[j]), deltaTime);
							}
						}
					}
				}

				if (entities[i]->GetTag() == Tag::Enemy && entities[j]->GetTag() == Tag::Car)
				{
					if (static_cast<Enemy*>(entities[i])->GetIsActive() && !static_cast<Car*>(entities[j])->GetIsDestroyed())
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							if (static_cast<Enemy*>(entities[i])->GetIsAlive())
							{
								static_cast<Enemy*>(entities[i])->SetIsAttackingCar(true);
								static_cast<Enemy*>(entities[i])->SetIsAttackingPlayer(false);
								static_cast<Enemy*>(entities[i])->Attack(static_cast<Car*>(entities[j]), deltaTime);
							}
						}
					}
					else if (static_cast<Enemy*>(entities[i])->GetIsActive() && static_cast<Car*>(entities[j])->GetIsDestroyed())
					{
						float distance = std::sqrt(std::pow(static_cast<Enemy*>
							(entities[i])->GetNewPosition().x - (entities[j])->Graphic().getPosition().x, 2) +
							std::pow(static_cast<Enemy*> (entities[i])->GetNewPosition().y
								- (entities[j])->Graphic().getPosition().y, 2));

						float minDistance = static_cast<Enemy*>(entities[i])->GetCollissionRadius() +
							static_cast<Car*>(entities[j])->GetCollissionRadius();

						if (distance < minDistance)
						{
							float overlap = minDistance - distance;
							sf::Vector2f direction = VectorUtility::Normalize(static_cast<Enemy*>(entities[i])->GetNewPosition()
								- (entities[j])->Graphic().getPosition());

							static_cast<Enemy*>(entities[i])->
								Graphic().setPosition(static_cast<Enemy*>(entities[i])->GetNewPosition()
									+ direction * (overlap * 0.5f));
							/*(entities[j])->
								Graphic().setPosition((entities[j])->Graphic().getPosition()
								- direction * (overlap * 0.5f));*/
						}
					}
				}

				if (entities[i]->GetTag() == Tag::Enemy && entities[j]->GetTag() == Tag::BaseArea)
				{
					if (static_cast<Enemy*>(entities[i])->GetIsActive() &&
						!static_cast<Enemy*>(entities[i])->GetIsAttackingCar() &&
						!static_cast<Enemy*>(entities[i])->GetIsAttackingHouse())
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							if (static_cast<Enemy*>(entities[i])->GetIsAlive())
							{
								static_cast<Enemy*>(entities[i])->SetIsAttackingPlayer(true);
							}

						}
					}
				}

				if (entities[i]->GetTag() == Tag::Enemy && entities[j]->GetTag() == Tag::Player)
				{
					if (static_cast<Enemy*>(entities[i])->GetIsActive())
					{
						if (static_cast<Player*>(entities[j])->GetIsAlive())
						{
							if (entities[i]->onCollission(*entities[i], *entities[j]))
							{
								if (static_cast<Enemy*>(entities[i])->GetIsAlive())
								{
									static_cast<Player*>(entities[j])->Die();

								}

							}
						}


					}
				}

				if (entities[i]->GetTag() == Tag::Enemy && entities[j]->GetTag() == Tag::Enemy)
				{
					if (i != j)
					{
						if (static_cast<Enemy*>(entities[i])->GetIsActive() &&
							static_cast<Enemy*>(entities[j])->GetIsActive())
						{
							if (static_cast<Enemy*>(entities[i])->GetIsAlive() &&
								static_cast<Enemy*>(entities[j])->GetIsAlive())
							{
								float distance = std::sqrt(std::pow(static_cast<Enemy*>
									(entities[i])->GetNewPosition().x - static_cast<Enemy*>
									(entities[j])->Graphic().getPosition().x, 2) + std::pow(static_cast<Enemy*>
										(entities[i])->GetNewPosition().y - static_cast<Enemy*>
										(entities[j])->Graphic().getPosition().y, 2));

								float minDistance = static_cast<Enemy*>(entities[i])->GetCollissionRadius() +
									static_cast<Enemy*>(entities[j])->GetCollissionRadius();

								if (distance < minDistance)
								{
									float overlap = minDistance - distance;
									sf::Vector2f direction = VectorUtility::Normalize(static_cast<Enemy*>(entities[i])->GetNewPosition()
										- static_cast<Enemy*>(entities[j])->GetNewPosition());

									static_cast<Enemy*>(entities[i])->
										Graphic().setPosition(static_cast<Enemy*>(entities[i])->GetNewPosition()
											+ direction * (overlap * 0.5f));
									static_cast<Enemy*>(entities[j])->
										Graphic().setPosition(static_cast<Enemy*>(entities[j])->GetNewPosition()
											- direction * (overlap * 0.5f));
								}
							}



						}
					}

				}

			}

		}
	}
	else if (sceneManager->GetIsDayTimeScene())
	{
		sf::Vector2f relativePosition;


		for (int i = 0; i < entities.size(); i++)
		{
			if (addSubstractHoursTimer >= 200)
				addSubstractHoursTimer = 0;

			if (okButtonTimer >= 200)
				okButtonTimer = 0;

			float waitTime = 0.2f;

			for (int j = 0; j < entities.size(); j++)
			{
				if (entities[i]->GetTag() == Tag::CloseHoursInterfaceButton)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

						if (entities[i]->Graphic().getGlobalBounds().contains(mousePos))
						{
							HoursInterface::SetIsOpen(false);
						}
					}						
					
				}
				else if (entities[j]->GetTag() == Tag::CloseHoursInterfaceButton)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

						if (entities[j]->Graphic().getGlobalBounds().contains(mousePos))
						{
							HoursInterface::SetIsOpen(false);
						}
					}
				}
								
				if (entities[i]->GetTag() == Tag::AddHoursButton)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

						if (entities[i]->Graphic().getGlobalBounds().contains(mousePos))
						{
							if (addSubstractHoursTimer >= waitTime)
							{
								HoursInterface::AddHoursToSpend();
								addSubstractHoursTimer = 0;
							}

						}
					}

				}
				else if (entities[j]->GetTag() == Tag::AddHoursButton)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

						if (entities[j]->Graphic().getGlobalBounds().contains(mousePos))
						{
							if (addSubstractHoursTimer >= waitTime)
							{
								HoursInterface::AddHoursToSpend();
								addSubstractHoursTimer = 0;
							}
						}
					}
				}

				if (entities[i]->GetTag() == Tag::SubstractHoursButton)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

						if (entities[i]->Graphic().getGlobalBounds().contains(mousePos))
						{
							if (addSubstractHoursTimer >= waitTime)
							{
								HoursInterface::SubstractHoursToSpend();
								addSubstractHoursTimer = 0;
							}
						}
					}

				}
				
				if (entities[i]->GetTag() == Tag::OkHoursButtonPlanks)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

						if (entities[i]->Graphic().getGlobalBounds().contains(mousePos))
						{
							if (okButtonTimer >= waitTime)
							{	
								int repairCost = 50 * HoursInterface::GetHoursToSpend();

								if (Player::GetResources() - repairCost >= 0)
								{
									sceneManager->SetIsTransitioning(true);
									sceneManager->SetIsFenceTaskTransition(true);
									sceneManager->SetIsTransitioningTask(true);

									Player::SpendResources(50 * HoursInterface::GetHoursToSpend());

									planksHoursInterface->SetIsActive(false);
									HoursInterface::SetIsOpen(false);
								}	
								else
								{
									HoursInterface::SetScrapNotEnoughShowText(true);
								}

								okButtonTimer = 0;
							}													

						}
					}
				}		
				else if (entities[i]->GetTag() == Tag::OkHoursButtonToolbox)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

						if (entities[i]->Graphic().getGlobalBounds().contains(mousePos))
						{
							if (okButtonTimer >= waitTime)
							{	
								int repairCost = 50 * HoursInterface::GetHoursToSpend();

								if (Player::GetResources() - repairCost >= 0)
								{
									sceneManager->SetIsTransitioning(true);
									sceneManager->SetIsToolboxTaskTransition(true);
									sceneManager->SetIsTransitioningTask(true);

									Player::SpendResources(repairCost);

									toolboxHoursInterface->SetIsActive(false);
									HoursInterface::SetIsOpen(false);
								}	
								else
								{
									HoursInterface::SetScrapNotEnoughShowText(true);
								}

								okButtonTimer = 0;
							}

						}
					}
				}
				else if (entities[i]->GetTag() == Tag::OkHoursButtonBricks)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

						if (entities[i]->Graphic().getGlobalBounds().contains(mousePos))
						{
							if (okButtonTimer >= waitTime)
							{      
								int repairCost = 50 * HoursInterface::GetHoursToSpend();

								if (Player::GetResources() - repairCost >= 0)
								{
									sceneManager->SetIsTransitioning(true);
									sceneManager->SetIsHouseTaskTransition(true);
									sceneManager->SetIsTransitioningTask(true);

									Player::SpendResources(50 * HoursInterface::GetHoursToSpend());

									bricksHoursInterface->SetIsActive(false);
									HoursInterface::SetIsOpen(false);
								}								

								okButtonTimer = 0;
							}
							else
							{
								HoursInterface::SetScrapNotEnoughShowText(true);
							}
						}
					}
				}
				else if (entities[i]->GetTag() == Tag::OkHoursButtonScavenge)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

						if (entities[i]->Graphic().getGlobalBounds().contains(mousePos))
						{
							if (okButtonTimer >= waitTime)
							{																
								sceneManager->SetIsTransitioning(true);
								sceneManager->SetIsScavengeTaskTransition(true);
								sceneManager->SetIsTransitioningTask(true);
																
								carHoursInterface->SetIsActive(false);
								HoursInterface::SetIsOpen(false);
								
								okButtonTimer = 0;
																
							}

						}
					}
				}
				else if (entities[i]->GetTag() == Tag::OkHoursButtonSleep)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

						if (entities[i]->Graphic().getGlobalBounds().contains(mousePos))
						{
							if (okButtonTimer >= waitTime)
							{
								sceneManager->SetIsTransitioning(true);
								sceneManager->SetIsSleepTaskTransition(true);
								sceneManager->SetIsTransitioningTask(true);

								bedHoursInterface->SetIsActive(false);
								HoursInterface::SetIsOpen(false);

								okButtonTimer = 0;
							}

						}
					}
				}


				if (entities[i]->GetTag() == Tag::CloseScavengeResults)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

						if (entities[i]->Graphic().getGlobalBounds().contains(mousePos))
						{
							dayTasksManager->SetScavengeResultsOpen(false);
							dayTasksManager->SetShowShotgunHasBeenFoundText(false);
							dayTasksManager->SetShowUziHasBeenFoundText(false);

						}
					}

				}


				if (entities[i]->GetTag() == Tag::CloseEndDay)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

						if (entities[i]->Graphic().getGlobalBounds().contains(mousePos))
						{
							TimeClock::SetEndDayTextOpened(false);
							sceneManager->SetTransitionToNight(true);
							entities[i]->Graphic().setPosition(2000, 2000);

						}
					}

				}

				
			}

		}

		if (sceneManager->GetIsInsidePlayerHouse())
		{
			for (int i = 0; i < entities.size(); i++)
			{
				for (int j = 0; j < entities.size(); j++)
				{
					relativePosition = entities[i]->Graphic().getPosition() - entities[j]->Graphic().getPosition();

					if (entities[i]->GetTag() == Tag::Player && ((entities[j]->GetTag() == Tag::Wall) || (entities[j]->GetTag() == Tag::Limit) ||
						(entities[j]->GetTag() == Tag::Bed) || (entities[j]->GetTag() == Tag::Radio) || (entities[j]->GetTag() == Tag::Chair) ||
						(entities[j]->GetTag() == Tag::Table)))
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							static_cast<Player*>(entities[i])->RigidObjectCollision(deltaTime);
						}
					}

					if (entities[i]->GetTag() == Tag::Player && ((entities[j]->GetTag() == Tag::BedCollider) || 
						(entities[j]->GetTag() == Tag::DoorColliderInside) || (entities[j]->GetTag() == Tag::RadioCollider)))
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							if(!Radio::GetIsListeningRadio())
								static_cast<Player*>(entities[i])->EButtonOn();
						}
					}

					if (entities[i]->GetTag() == Tag::Player && (entities[j]->GetTag() == Tag::DoorColliderInside))
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
							{
								if (TimeClock::GetHours() > 0)
								{
									if (TimeClock::GetCurrentDay() <= 3)
									{
										if (Radio::GetWasUsed())
										{
											sceneManager->SetIsTransitioning(true);

											if (sceneManager->GetCanUseDoors())
												sceneManager->SetIsTransitioningToOutside(true);
										}
										else
										{
											Radio::SetShowCheckText(true);
										}
									}
									else
									{
										sceneManager->SetIsTransitioning(true);

										if (sceneManager->GetCanUseDoors())
											sceneManager->SetIsTransitioningToOutside(true);
									}

									
								}						

							}
						}
					}

					if (entities[i]->GetTag() == Tag::Player && (entities[j]->GetTag() == Tag::BedCollider))
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
							{
								if (TimeClock::GetHours() > 0)
								{
									if (TimeClock::GetCurrentDay() <= 3)
									{
										if (Radio::GetWasUsed())
										{
											Bed::GetHoursInterface()->SetIsActive(true);
											HoursInterface::SetIsOpen(true);
										}
										else
										{
											Radio::SetShowCheckText(true);
										}
									}
									else
									{
										Bed::GetHoursInterface()->SetIsActive(true);
										HoursInterface::SetIsOpen(true);
									}
									
								}													
								
							}
						}
					}

					if (entities[i]->GetTag() == Tag::Player && (entities[j]->GetTag() == Tag::RadioCollider))
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
							{
								if (!sceneManager->GetIsTransitioning())
								{
									if (TimeClock::GetCurrentDay() <= 2)
									{
										if (TimeClock::GetHours() > 0)
										{
											if (!Radio::GetWasUsed())
											{
												sceneManager->SetIsTransitioning(true);
												Radio::SetIsListeningRadio(true);
												Radio::SetShowRadioText(true);
											}
											else
											{
												Radio::SetIsListeningRadio(true);
											}
										}
										
									}			
									else if (TimeClock::GetCurrentDay() <= 3)
									{
										if (TimeClock::GetHours() > 0)
										{
											if (!Radio::GetWasUsed())
											{
												sceneManager->SetIsTransitioning(true);
												Radio::SetIsListeningRadio(true);
												Radio::SetShowRadioMessageText(true);
											}
											else
											{
												Radio::SetIsListeningRadio(true);
											}
										}
									}
									else
									{
										Radio::SetIsListeningRadio(true);
									}
								}

								
							}
						}
					}

				}

			}
		}
		else if (sceneManager->GetIsOutsidePlayerHouse())
		{
			for (int i = 0; i < entities.size(); i++)
			{
				for (int j = 0; j < entities.size(); j++)
				{
					relativePosition = entities[i]->Graphic().getPosition() - entities[j]->Graphic().getPosition();

					if (entities[i]->GetTag() == Tag::Player && (entities[j]->GetTag() == Tag::Fence ||
						entities[j]->GetTag() == Tag::Car || entities[j]->GetTag() == Tag::House || entities[j]->GetTag() == Tag::Toolbox ||
						entities[j]->GetTag() == Tag::Planks || entities[j]->GetTag() == Tag::Bricks))
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							static_cast<Player*>(entities[i])->RigidObjectCollision(deltaTime);
						}
					}

					if (entities[i]->GetTag() == Tag::Player && (entities[j]->GetTag() == Tag::DoorColliderOutside || entities[j]->GetTag() == Tag::CarCollider ||
						entities[j]->GetTag() == Tag::ToolboxCollider || entities[j]->GetTag() == Tag::PlanksCollider || entities[j]->GetTag() == Tag::BricksCollider))
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							static_cast<Player*>(entities[i])->EButtonOn();
						}
					}

					if (entities[i]->GetTag() == Tag::Player && (entities[j]->GetTag() == Tag::DoorColliderOutside))
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
							{
								if (TimeClock::GetHours() > 0)
								{
									sceneManager->SetIsTransitioning(true);

									if (sceneManager->GetCanUseDoors())
										sceneManager->SetIsTransitioningToInside(true);
								}
																
							}
						}
					}

					if (entities[i]->GetTag() == Tag::Player && (entities[j]->GetTag() == Tag::CarCollider))
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
							{
								if (TimeClock::GetHours() > 0)
								{
									carHoursInterface->SetIsActive(true);
									HoursInterface::SetIsOpen(true);
								}								
							}
						}
					}

					if (entities[i]->GetTag() == Tag::Player && (entities[j]->GetTag() == Tag::ToolboxCollider))
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
							{
								if (TimeClock::GetHours() > 0)
								{
									toolboxHoursInterface->SetIsActive(true);
									HoursInterface::SetIsOpen(true);
								}
								
							}
						}
					}

					if (entities[i]->GetTag() == Tag::Player && (entities[j]->GetTag() == Tag::PlanksCollider))
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
							{
								if (TimeClock::GetHours() > 0)
								{
									planksHoursInterface->SetIsActive(true);
									HoursInterface::SetIsOpen(true);
								}								
							}
						}
					}

					if (entities[i]->GetTag() == Tag::Player && (entities[j]->GetTag() == Tag::BricksCollider))
					{
						if (entities[i]->onCollission(*entities[i], *entities[j]))
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
							{
								if (TimeClock::GetHours() > 0)
								{
									bricksHoursInterface->SetIsActive(true);
									HoursInterface::SetIsOpen(true);
								}
							
							}
						}
					}
									
				}

			}
		}
		
	}

	
}




//COMPROBAR TAMBIEN LA DISTANCIA ENTRE OBJETOS PARA HACER O NO COMPROBACION DE COLISIONES.
