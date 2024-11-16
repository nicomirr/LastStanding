#pragma once

#include<SFML/System.hpp>
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include "Tag.h"
#include "../Utilities/RandomNum.h"

class Entity
{
private:
	Tag tag;

protected:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::FloatRect bounds;

public:

	bool isValid = false;	//Permite encender y apagar un entity
	virtual void Update(float deltaTime);

	sf::Sprite& Graphic() { return sprite; }  //Simbolo & es pasaje por referencia

	Entity();
	Entity(std::string imageFilePath, sf::Vector2i spriteSheetSize);
	void SetTag(Tag tag) { this->tag = tag; }
	Tag GetTag() { return tag; }
	virtual sf::FloatRect GetBounds(); 
	void SetBounds(sf::FloatRect bounds);
	bool onCollission(Entity& self, Entity& other);
};

