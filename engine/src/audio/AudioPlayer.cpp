#include "AudioPlayer.h"

#include <SDL3/SDL.h>
#include <iostream>

namespace engine
{
AudioPlayer::~AudioPlayer()
{
    shutdown();
}

auto AudioPlayer::loadSound(const std::string& filePath) -> bool
{
    SDL_AudioSpec spec;
    if (!SDL_LoadWAV(filePath.c_str(), &spec, &audioBuffer, &audioLength))
    {
        std::cerr << "SDL_LoadWAV failed: " << SDL_GetError() << '\n';
        return false;
    }

    // SDL3: een audio-stream koppelt het geladen format direct aan het
    // standaard afspeelapparaat. Dit vervangt de SDL2-aanpak met een
    // los geopend audiodevice + handmatige callback.
    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr);
    if (stream == nullptr)
    {
        std::cerr << "SDL_OpenAudioDeviceStream failed: " << SDL_GetError() << '\n';
        return false;
    }

    SDL_ResumeAudioStreamDevice(stream);
    return true;
}

auto AudioPlayer::playSound() -> void
{
    if (stream == nullptr || audioBuffer == nullptr)
    {
        return;
    }

    // Fire-and-forget: de samples opnieuw in de stream zetten speelt het
    // geluid (opnieuw) af, zonder dat de aanroeper de levenscyclus hoeft
    // te beheren (vgl. US12: geluidseffecten naast muziek).
    SDL_PutAudioStreamData(stream, audioBuffer, static_cast<int>(audioLength));
}

auto AudioPlayer::shutdown() -> void
{
    if (stream != nullptr)
    {
        SDL_DestroyAudioStream(stream);
        stream = nullptr;
    }

    if (audioBuffer != nullptr)
    {
        SDL_free(audioBuffer);
        audioBuffer = nullptr;
    }
}
} // namespace engine
