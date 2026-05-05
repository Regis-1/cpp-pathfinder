#pragma once

class SDL_Window;
class SDL_Renderer;
union SDL_Event;
class Command;
class ImGuiIO;

class UI
{
public:
    UI() = delete;

    UI(SDL_Window *window, SDL_Renderer *renderer);
    ~UI();

    void draw_and_process(Command *&command);

    void process_events(SDL_Event &e);

    int get_current_tile() const;

    bool want_capture_mouse() const;

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    ImGuiIO *io;

    bool show_demo_window;
    bool show_fps_counter;
    int item_current;
};
