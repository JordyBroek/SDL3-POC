#pragma once

#include "Color.h"
#include "IRenderer.h"

struct SDL_Renderer;

namespace engine
{
class SDL3Renderer final : public IRenderer
{
public:
    SDL3Renderer() = default;
    ~SDL3Renderer() override;

    SDL3Renderer(const SDL3Renderer&) = delete;
    auto operator=(const SDL3Renderer&) -> SDL3Renderer& = delete;

    auto init(Window& window) -> bool override;
    auto clear() -> void override;
    auto drawRect(int x, int y, int width, int height, Color color) -> void override;
    auto present() -> void override;
    auto shutdown() -> void override;

private:
    // Eigendom: deze klasse maakt en vernietigt dit SDL-handle zelf.
    SDL_Renderer* handle = nullptr;
};
} // namespace engine
