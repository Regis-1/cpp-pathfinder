#pragma once

#include <string>
#include <SDL3/SDL.h>

#include "Renderer.h"
#include "Simulation.h"

class Application
{
public:
    Application(const std::string &&title, const int &&width, const int &&height);
    bool init();
    void run();
    void cleanup();

private:
    void process_events(SDL_Event *e);
    void update(Map &map);

    const std::string title;
    const int screen_width;
    const int screen_height;

    SDL_Window *window;

    Simulation simulation;
    Renderer renderer;

    InputState input_state;
};
