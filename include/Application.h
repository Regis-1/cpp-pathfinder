#pragma once

#include <string>

#include "InputState.h"
#include "Renderer.h"
#include "Simulation.h"
#include "UI.h"

union SDL_Event;
class SDL_Window;

class Application
{
public:
    Application(std::string title, int width, int height);
    bool init();
    void run();
    void cleanup();

private:
    void process_events(SDL_Event &e);
    void update(Map &map);

    const std::string title;
    const int screen_width;
    const int screen_height;

    SDL_Window *window;

    Simulation simulation;
    Renderer renderer;
    UI *ui;

    InputState input_state;

};
