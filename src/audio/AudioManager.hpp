#pragma once 
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class AudioManager
{
    public:
        AudioManager();
         // bounce sound for a given material
         void playBounce(const std::string& materialName);

         // generic sound for blocks
         void playDefaultBounce();
    private:
         // generate sine waves
         void generateSound(
                 const std::string& name, 
                 float frequency, 
                 float decaySeconds,
                 float volume = 10.f
                 );
         // each material has its own buffer
         std::map<std::string, sf::SoundBuffer> m_buffers;
         std::map<std::string, sf::Sound> m_sounds;

         static const int SAMPLE_RATE = 44100; // smaples per second
};
