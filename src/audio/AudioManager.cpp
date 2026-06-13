#include "AudioManager.hpp"
#include <cmath>
#include <vector>
#include <iostream>


// pi for sine wave calculations
static const float PI = 3.14159265f;

AudioManager::AudioManager()
{
    // generate sound for each material
    // name, frew, delay time<dt>
    generateSound("Wood", 180.f, 0.15f);
    generateSound("Iron", 120.f, 0.20f);
    generateSound("Steel", 800.f, 0.40f);
    generateSound("Plastic", 600.f, 0.10f);
    generateSound("Glass", 1200.f, 0.50f);
    generateSound("Default", 300.f, 0.12f);
}

void AudioManager::generateSound(
        const std::string& name,
        float frequency,
        float decaySeconds,
        float volume
        )
{
    // no of samples needed for the decay duration
    int sampleCount = static_cast<int>(SAMPLE_RATE * decaySeconds);

    std::vector<sf::Int16> samples(sampleCount);

    for (int i = 0; i < sampleCount; i++)
    {
        float t = static_cast<float>(i) / SAMPLE_RATE;

        // sine wave to produce frequency
        float wave = std::sin(2.f * PI * frequency * t);

        //envelope
        float envelope = 1.0f - (static_cast<float>(i) / sampleCount);

        // amplitude ....max aplitude = 32767
        samples[i] = static_cast<sf::Int16>(wave * envelope * volume * 32767.f);

        
    }
    
    // load raw samples into the buffer
    if (!m_buffers[name].loadFromSamples(samples.data(), sampleCount, 1, SAMPLE_RATE))
    {
        std::cerr << "failed to generate sound" << name << "\n";
        return;
    }

    // bind a sound to its buffer
    // sound -> pointer to the buffer
    m_sounds[name].setBuffer(m_buffers[name]);
}

void AudioManager::playBounce(const std::string& materialName)
{
    auto it = m_sounds.find(materialName);
    if (it != m_sounds.end())
    {
        // restart from beginning if already playing
        it -> second.play();
    } else {
        playDefaultBounce();
    }
}

void AudioManager::playDefaultBounce()
{
    m_sounds["Default"].play();
}
