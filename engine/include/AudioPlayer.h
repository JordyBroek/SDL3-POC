#pragma once

#include <cstdint>
#include <string>

struct SDL_AudioStream;

namespace engine
{
// Fire-and-forget geluidseffect-afspeler, gebouwd op SDL3's eigen
// audio-stream-API (dus niet de losse SDL3_mixer-library).
class AudioPlayer
{
public:
    AudioPlayer() = default;
    ~AudioPlayer();

    AudioPlayer(const AudioPlayer&) = delete;
    auto operator=(const AudioPlayer&) -> AudioPlayer& = delete;

    auto loadSound(const std::string& filePath) -> bool;
    auto playSound() -> void;
    auto shutdown() -> void;

private:
    // Eigendom: deze klasse maakt/laadt en vernietigt/bevrijdt deze
    // SDL-resources zelf (zie shutdown()).
    SDL_AudioStream* stream = nullptr;
    std::uint8_t* audioBuffer = nullptr;
    std::uint32_t audioLength = 0;
};
} // namespace engine
