#pragma once

#include <string>

struct SDL_Window;

namespace engine
{
    class Window
    {
    public:
        Window(std::string title, int width, int height);
        ~Window();

        Window(const Window&) = delete;
        auto operator=(const Window&) -> Window& = delete;

        auto init() -> bool;

        [[nodiscard]] auto getHandle() const -> SDL_Window*;
        [[nodiscard]] auto getWidth() const -> int;
        [[nodiscard]] auto getHeight() const -> int;

    private:
        std::string title;
        int width;
        int height;

        // Eigendom: deze klasse maakt en vernietigt dit SDL-handle zelf.
        SDL_Window* handle = nullptr;
    };
} // namespace engine
