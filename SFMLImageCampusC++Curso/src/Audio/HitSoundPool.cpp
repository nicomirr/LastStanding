#include "HitSoundPool.h"

HitSoundPool::HitSoundPool(size_t poolSize, const sf::SoundBuffer& buffer)
{
    {
        for (size_t i = 0; i < poolSize; ++i)
        {
            sf::Sound sound;
            sound.setBuffer(buffer);
            sound.setVolume(100);
            sound.setLoop(false);
            sounds.push_back(sound);
        }
    }
}

void HitSoundPool::play()
{
    for (auto& sound : sounds) 
    {
        if (sound.getStatus() != sf::Sound::Playing) 
        {
            sound.play();
            return;
        }
    }

    sounds[currentIndex].stop();
    sounds[currentIndex].play();
    currentIndex = (currentIndex + 1) % sounds.size();  
    
}
