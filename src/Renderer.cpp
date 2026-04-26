#include "Renderer.h"

Renderer::Renderer(const int tile_size)
    : renderer(nullptr), tile_size(tile_size)
{}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(this->renderer);
    this->renderer = nullptr;
}

bool Renderer::init(SDL_Window *window)
{
    if (this->renderer)
    {
        SDL_DestroyRenderer(this->renderer);
    }

    this->renderer = SDL_CreateRenderer(window, nullptr);

    if (this->renderer == nullptr)
    {
        return false;
    }

    SDL_SetRenderVSync(this->renderer, 1);
    return true;
}

void Renderer::clear_screen() const
{
    SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
}

void Renderer::render() const
{
    SDL_RenderPresent(renderer);
}

void Renderer::draw_tile(const int x, const int y) const
{
    SDL_FRect rect {static_cast<float>(x), static_cast<float>(y),
                    static_cast<float>(this->tile_size),
                    static_cast<float>(this->tile_size)};

    SDL_RenderFillRect(this->renderer, &rect);
}

void Renderer::set_draw_color(SDL_Color color)
{
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}

void Renderer::set_tile_size(const int new_size)
{
    this->tile_size = new_size;
}

SDL_Renderer* Renderer::get_renderer() const
{
    return this->renderer;
}
