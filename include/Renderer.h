#pragma once

#include <SDL3/SDL.h>

class Renderer
{
public:
    Renderer(const int tile_size = 32);
    ~Renderer(); 

    bool init(SDL_Window *window);

    void clear_screen() const;
    void render() const;

    void draw_tile(const int x, const int y) const;

    void set_draw_color(SDL_Color color);
    void set_tile_size(const int new_size);

    SDL_Renderer* get_renderer() const;

private:
    SDL_Renderer *renderer;
    unsigned int tile_size;
};
