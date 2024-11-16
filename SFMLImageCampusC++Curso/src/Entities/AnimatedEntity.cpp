#include "AnimatedEntity.h"

AnimatedEntity::AnimatedEntity(){}

AnimatedEntity::AnimatedEntity(sf::Vector2i animationFrameSize, std::string imageFilePath,
	sf::Vector2i spriteSheetSize) : Entity(imageFilePath, spriteSheetSize)
{
	this->frameSize = animationFrameSize;

	int left = 0;
	int top = 0;
	int width = animationFrameSize.x;
	int height = animationFrameSize.y;

	sf::IntRect textureRectInitialPos(left, top, width, height); 
	sprite.setTextureRect(textureRectInitialPos);
}

void AnimatedEntity::Update(float deltaTime)
{
	if (currentAnimationName.empty()) return;
		
	animationTimer += deltaTime;

	if (animationTimer >= currentFrameTime)
	{
		animationTimer -= currentFrameTime;

		if (imagePosition.x < animations[currentAnimationName].columnsCount - 1)
			imagePosition.x++;

		else if (animations[currentAnimationName].loops)
			imagePosition.x = 0;

		int left = imagePosition.x * frameSize.x;
		int top = imagePosition.y * frameSize.y;
		int width = frameSize.x;
		int height = frameSize.y;

		sf::IntRect textureRectNewPos(left, top, width, height);
		sprite.setTextureRect(textureRectNewPos);
	}
}

void AnimatedEntity::AddAnimation(std::string animationName, AnimationData animationData)
{
	if (animations.count(animationName))
	{
		std::cout << "Error. Ya existe una animacion con ese nombre.";
		return;
	}

	animations.insert({ animationName, animationData });
}

void AnimatedEntity::RemoveAnimation(std::string animationName)
{
	if (!animations.count(animationName))
	{
		std::cout << "Error. No existe una animacion con ese nombre.";
		return;
	}

	animations.erase(animationName);
}

void AnimatedEntity::SetCurrentAnimation(std::string animationName)
{
	if (!animations.count(animationName))
	{
		std::cout << "Error. No existe una animacion con ese nombre.";
		return;
	}

	if (currentAnimationName != animationName)
	{
		currentAnimationName = animationName;
		currentFrameTime = 1.0 / animations[currentAnimationName].frameRate;	//a mayor framerate, menos dura cada frame de animación
		imagePosition = sf::Vector2i(0, animations[currentAnimationName].rowIndex);

		animationTimer = 0;

		int left = imagePosition.x * frameSize.x;
		int top = imagePosition.y * frameSize.y;
		int width = frameSize.x;
		int height = frameSize.y;

		sf::IntRect textureRectNewPos(left, top, width, height);
		sprite.setTextureRect(textureRectNewPos);
	}
}

void AnimatedEntity::SetAnimationFrameSize(sf::Vector2i animationFrameSize)
{
	this->frameSize = animationFrameSize;
}

