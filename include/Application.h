#pragma once

#include <string>

#include "Renderer.h"
#include "Simulation.h"
#include "UI.h"
#include "Command.h"

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

    SDL_Window *window;

    Renderer renderer;
    Simulation simulation;

    UI *ui;

    Command *command;

    const std::string title;
    const int screen_width;
    const int screen_height;

    bool should_exit;
};
