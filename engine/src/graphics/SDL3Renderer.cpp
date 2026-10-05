#include "SDL3Renderer.h"
#include "Window.h"
#include <SDL3/SDL.h>
#include <iostream>

namespace engine
{
SDL3Renderer::~SDL3Renderer()
{
    shutdown();
}

auto SDL3Renderer::init(Window& window) -> bool
{
    // SDL3's SDL_CreateRenderer no longer takes a driver-index argument like SDL2 did.
    // nullptr lets SDL pick the best available backend.
    handle = SDL_CreateRenderer(window.getHandle(), nullptr);
    if (handle == nullptr)
    {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << '\n';
        return false;
    }
    return true;
}

auto SDL3Renderer::clear() -> void
{
    SDL_SetRenderDrawColor(handle, 20, 20, 20, 255);
    SDL_RenderClear(handle);
}

auto SDL3Renderer::drawRect(int x, int y, int width, int height, Color color) -> void
{
    // SDL3 uses float-based rects (SDL_FRect) instead of SDL2's int-based SDL_Rect.
    const SDL_FRect rect{
        static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height)};

    SDL_SetRenderDrawColor(handle, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(handle, &rect);
}

auto SDL3Renderer::present() -> void
{
    SDL_RenderPresent(handle);
}

auto SDL3Renderer::shutdown() -> void
{
    if (handle != nullptr)
    {
        SDL_DestroyRenderer(handle);
        handle = nullptr;
    }
}
} // namespace engine
