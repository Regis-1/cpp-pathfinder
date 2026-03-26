#include "Renderer.h"

Renderer::Renderer(const unsigned int tile_size)
    : renderer(nullptr), tile_size(tile_size)
{}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(this->renderer);
}

bool Renderer::init(SDL_Window *window)
{
    this->renderer = SDL_CreateRenderer(window, nullptr);
    if (this->renderer == nullptr)
    {
        return false;
    }

    return true;
}

void Renderer::clear_screen()
{
    SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
}

void Renderer::render()
{
    SDL_RenderPresent(renderer);
}

void Renderer::draw_tile(const int x, const int y)
{
    SDL_FRect rect {static_cast<float>(x), static_cast<float>(y),
                    static_cast<float>(this->tile_size),
                    static_cast<float>(this->tile_size)};

    SDL_RenderFillRect(this->renderer, &rect);
}

void Renderer::set_draw_color(const short r, const short g, const short b, const short a)
{
    SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
}

void Renderer::set_tile_size(const unsigned int new_size)
{
    this->tile_size = new_size;
}
