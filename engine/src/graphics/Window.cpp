#include "Window.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <utility>

namespace engine
{
Window::Window(std::string title, int width, int height)
    : title(std::move(title))
    , width(width)
    , height(height)
{
}

Window::~Window()
{
    if (handle != nullptr)
    {
        SDL_DestroyWindow(handle);
    }
}

auto Window::init() -> bool
{
    handle = SDL_CreateWindow(title.c_str(), width, height, 0);
    if (handle == nullptr)
    {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << '\n';
        return false;
    }

    return true;
}

auto Window::getHandle() const -> SDL_Window*
{
    return handle;
}

auto Window::getWidth() const -> int
{
    return width;
}

auto Window::getHeight() const -> int
{
    return height;
}
} // namespace engine
