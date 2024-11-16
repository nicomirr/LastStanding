#pragma once
#include <SFML/Audio.hpp>

class HitSoundPool
{
public:
    HitSoundPool(size_t poolSize, const sf::SoundBuffer& buffer);
	
    void play();

private:
    std::vector<sf::Sound> sounds;
    size_t currentIndex = 0;

};

