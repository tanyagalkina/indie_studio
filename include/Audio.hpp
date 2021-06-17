//
// Created by tag43 on 6/16/21.
//

#ifndef BOMBERMAN_AUDIO_HPP
#define BOMBERMAN_AUDIO_HPP

#include <SFML/Audio.hpp>
#include <SFML/Audio.h>

class Audio {
private:
    sf::SoundBuffer exploBuffer;
    sf::Sound exploSound;
    sf::SoundBuffer backBuffer;
    sf::Sound backSound;
public:
    Audio()
    {
        exploBuffer.loadFromFile("media/sounds/explosion.ogg");
        exploSound.setBuffer(exploBuffer);
        exploSound.setVolume(20);
        backBuffer.loadFromFile("media/sounds/arabic.ogg");
        backSound.setBuffer(backBuffer);
        backSound.setLoop(true);
        backSound.setVolume(5);

    }
    void Mute()
    {
        backSound.setVolume(0);
        exploSound.setVolume(0);
    }

    void Unmute()
    {
        backSound.setVolume(20);
        exploSound.setVolume(5);
    }

    void explode()
    {
        exploSound.play();       // Play queued audio
    }
    void backMusic()
    {
        backSound.play();
    }
};


#endif //BOMBERMAN_AUDIO_HPP
