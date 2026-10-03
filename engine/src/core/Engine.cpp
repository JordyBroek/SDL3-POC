#include "Engine.h"

#include "SDL3Renderer.h"

#include <SDL3/SDL.h>

#include <iostream>
#include <memory>

namespace engine
{
    auto Engine::init() -> bool
    {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
        {
            std::cerr << "SDL_Init failed: " << SDL_GetError() << '\n';
            return false;
        }

        window = std::make_unique<Window>("Engine Prototype", 800, 600);
        if (!window->init())
        {
            // SDL_Init is al gelukt op dit punt; shutdown() ruimt dat weer
            // netjes op zodat we geen SDL-subsysteem laten "hangen" bij een
            // mislukte init.
            shutdown();
            return false;
        }

        // De rest van de Engine praat alleen tegen IRenderer; dat hier een
        // SDL3Renderer gekozen wordt is de enige plek waar dat vastligt.
        renderer = std::make_unique<SDL3Renderer>();
        if (!renderer->init(*window))
        {
            shutdown();
            return false;
        }

        audioPlayer = std::make_unique<AudioPlayer>();
        if (!audioPlayer->loadSound("assets/sounds/blip.wav"))
        {
            // Niet fataal voor dit prototype: rendering blijft werken ook
            // zonder geluidsbestand, maar we loggen het wel duidelijk.
            std::cerr << "Kon geluid niet laden, ga door zonder audio.\n";
        }

        running = true;
        return true;
    }

    auto Engine::isRunning() const -> bool
    {
        return running;
    }

    auto Engine::update() -> void
    {
        handleEvents();
        render();
    }

    auto Engine::handleEvents() -> void
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_SPACE)
            {
                audioPlayer->playSound();
            }
        }
    }

    auto Engine::render() -> void
    {
        renderer->clear();

        // Object 1: rood vierkant, linkerkant van het scherm.
        renderer->drawRect(100, 200, 150, 150, Color{255, 0, 0, 255});

        // Object 2: blauw vierkant, rechterkant van het scherm.
        renderer->drawRect(550, 200, 150, 150, Color{0, 0, 255, 255});

        renderer->present();
    }

    auto Engine::shutdown() -> void
    {
        audioPlayer.reset();
        renderer.reset();
        window.reset();
        SDL_Quit();
        running = false;
    }
} // namespace engine
