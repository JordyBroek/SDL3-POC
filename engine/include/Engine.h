#pragma once

#include "AudioPlayer.h"
#include "IRenderer.h"
#include "Window.h"

#include <memory>

namespace engine
{
class Engine
{
public:
    Engine() = default;
    ~Engine() = default;

    auto init() -> bool;
    [[nodiscard]] auto isRunning() const -> bool;
    auto update() -> void;
    auto shutdown() -> void;

private:
    auto handleEvents() -> void;
    auto render() -> void;

    std::unique_ptr<Window> window;
    std::unique_ptr<IRenderer> renderer;
    std::unique_ptr<AudioPlayer> audioPlayer;

    // Naam bewust "running" (niet "isRunning") om botsing met de
    // publieke methode isRunning() te vermijden.
    bool running = false;
};
} // namespace engine
