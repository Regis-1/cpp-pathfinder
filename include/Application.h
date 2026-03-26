#pragma once

#include <string>
#include <SDL3/SDL.h>

#include "Renderer.h"

class Application
{
public:
    Application(const std::string &&title, const int &&width, const int &&height);
    bool init();
    void run();
    void cleanup();

private:
    const std::string title;
    const int screen_width;
    const int screen_height;

    SDL_Window *window;

    Renderer renderer;
};
