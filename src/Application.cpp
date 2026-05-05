#include <SDL3/SDL.h>

#include "Application.h"

namespace
{
    constexpr int PATH_PADDING = 8;
    constexpr int PATH_SHRINK = 16;

    SDL_Color get_color(NodeType type)
    {
        switch (type)
        {
        case NodeType::Empty: return {0xBB,0xBB,0xBB,0xFF};
        case NodeType::Wall:  return {0x15,0x15,0x15,0xFF};
        case NodeType::Start: return {0x00,0x88,0x00,0xFF};
        case NodeType::Goal:  return {0x88,0x00,0x00,0xFF};
        }
        return {255, 0, 255, 255};
    }

    void draw_grid_map(const int x, const int y, const Map &map, Renderer &renderer)
    {
        int tile_size = map.get_tile_size();
        int tile_offset = map.get_tile_offset();

        renderer.set_tile_size(tile_size);

        for (int i = 0; i < map.size(); ++i)
        {
            renderer.set_draw_color(get_color(map[i]));

            Coord c = map.to_coord(i);

            renderer.draw_tile(x + (tile_size + tile_offset) * c.col,
                               y + (tile_size + tile_offset) * c.row);
        }
    }

    void draw_path(const int x, const int y, const Map &map,
                   const std::vector<int> &path, Renderer &renderer)
    {
        int tile_size = map.get_tile_size() - PATH_SHRINK;
        int tile_offset = map.get_tile_offset() + PATH_SHRINK;

        renderer.set_tile_size(tile_size);

        renderer.set_draw_color(SDL_Color{0x33, 0x33, 0x33, 0xFF});

        for (int i = 1; i < path.size() - 1; ++i)
        {
            Coord c = map.to_coord(path[i]);

            renderer.draw_tile(x + (tile_size + tile_offset) * c.col + PATH_PADDING,
                               y + (tile_size + tile_offset) * c.row + PATH_PADDING);
        }
    }
}


Application::Application(std::string title, int width, int height)
    : title(std::move(title)), screen_width(width), screen_height(height),
      renderer(this->simulation.get_map().get_tile_size()),
      simulation(Map("starter_map.txt", 32, 4)),
      ui(nullptr),
      command(nullptr),
      should_exit(false)
{}

bool Application::init()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "SDL could not be initialized. Error: %s\n",
                     SDL_GetError());

        return false;
    }

    this->window = SDL_CreateWindow(this->title.c_str(),this->screen_width,
                                    this->screen_height, SDL_WINDOW_RESIZABLE);

    if (this->window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Couldn't create window: %s",
                     SDL_GetError());

        return false;
    }

    if (this->renderer.init(this->window) == false)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Couldn't create renderer: %s",
                     SDL_GetError());

        return false;
    }

    this->ui = new UI(this->window, this->renderer.get_renderer());

    return true;
}

void Application::run()
{
    SDL_Event event;

    const Map &map_ref = this->simulation.get_map();

    while (!this->should_exit)
    {
        // PROCESSING EVENTS / INPUT
        process_events(event);

        // UPDATING
        this->simulation.apply_command(this->command);
        this->simulation.update();

        // RENDERING
        this->renderer.clear_screen();
        draw_grid_map(0, 0, map_ref, this->renderer);

        if (!this->simulation.get_path().empty())
        {
            draw_path(0, 0, map_ref,
                      this->simulation.get_path(),
                      this->renderer);
        }

        this->ui->draw_and_process(this->command);

        this->renderer.render();
    }
}

void Application::cleanup()
{
    delete this->ui;

    if (this->command)
    {
        delete this->command;
    }

    SDL_DestroyWindow(this->window);

    SDL_Quit();
}

void Application::process_events(SDL_Event &e)
{
    while (SDL_PollEvent(&e))
    {
        this->ui->process_events(e);

        if (e.type == SDL_EVENT_QUIT)
        {
            this->should_exit = true;
        }

        if (this->ui->want_capture_mouse())
        {
            continue;
        }

        else if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            NodeType type;

            if (e.button.button == SDL_BUTTON_LEFT)
            {
                type = static_cast<NodeType>(this->ui->get_current_tile() + 1);
            }
            else if(e.button.button == SDL_BUTTON_RIGHT)
            {
                type = NodeType::Empty;
            }


            this->command = new SetTileCommand(e.button.x, e.button.y, type);
        }
    }
}
