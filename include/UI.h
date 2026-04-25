#pragma once

class InputState;
class SDL_Window;
class SDL_Renderer;
union SDL_Event;

class UI
{
public:
    UI() = delete;

    UI(SDL_Window *window, SDL_Renderer *renderer);

    void draw_and_process(InputState &is);

    void process_events(SDL_Event *e);

    int get_current_tile();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool show_demo_window;
    bool show_fps_counter;
    int item_current;
};
