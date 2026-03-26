#pragma once

#include <SDL3/SDL.h>

class Renderer
{
public:
    Renderer(const unsigned int tile_size = 32);
    ~Renderer(); 

    bool init(SDL_Window *window);

    void clear_screen();
    void render();

    void draw_tile(const int x, const int y);

    void set_draw_color(const short r, const short g, const short b, const short a);
    void set_tile_size(const unsigned int new_size);

private:
    SDL_Renderer *renderer;
    unsigned int tile_size;
};
