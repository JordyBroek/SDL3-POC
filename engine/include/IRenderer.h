#pragma once

#include "Color.h"

namespace engine
{
class Window;

// Facade/Adapter-contract: de rest van de engine mag alleen tegen deze
// interface programmeren, nooit rechtstreeks tegen SDL. Zo kan de
// concrete implementatie (SDL3, later eventueel iets anders) verwisseld
// worden zonder Engine/main.cpp aan te passen.
class IRenderer
{
public:
    virtual ~IRenderer() = default;

    virtual auto init(Window& window) -> bool = 0;
    virtual auto clear() -> void = 0;
    virtual auto drawRect(int x, int y, int width, int height, Color color) -> void = 0;
    virtual auto present() -> void = 0;
    virtual auto shutdown() -> void = 0;
};
} // namespace engine
