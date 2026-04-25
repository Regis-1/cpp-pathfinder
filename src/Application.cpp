#include <SDL3/SDL.h>

#include "Application.h"

namespace
{
    void draw_grid_map(const int x, const int y, const Map &map, Renderer &renderer)
    {
        int tile_size = map.get_tile_size();
        int tile_offset = map.get_tile_offset();

        renderer.set_tile_size(tile_size);

        for (int i = 0; i < map.size(); ++i)
        {
            if (map[i] == NodeType::Empty)
            {
                renderer.set_draw_color(0xBB, 0xBB, 0xBB, 0xFF);
            }
            else if (map[i] == NodeType::Wall)
            {
                renderer.set_draw_color(0x15, 0x15, 0x15, 0xFF);
            }
            else if (map[i] == NodeType::Start)
            {
                renderer.set_draw_color(0x00, 0x88, 0x00, 0xFF);
            }
            else if (map[i] == NodeType::Goal)
            {
                renderer.set_draw_color(0x88, 0x00, 0x00, 0xFF);
            }

            Coord c = map.to_coord(i);

            renderer.draw_tile(x + (tile_size + tile_offset) * c.col,
                               y + (tile_size + tile_offset) * c.row);
        }
    }

    void draw_path(const int x, const int y, const Map &map,
                   const std::vector<int> &path, Renderer &renderer)
    {
        int tile_size = map.get_tile_size() - 16;
        int tile_offset = map.get_tile_offset() + 16;

        renderer.set_tile_size(tile_size);

        renderer.set_draw_color(0x33, 0x33, 0x33, 0xFF);

        for (int i = 0; i < path.size(); ++i)
        {
            if (i == 0 || i == path.size() - 1)
            {
                continue;
            }

            Coord c = map.to_coord(path[i]);

            renderer.draw_tile(x + (tile_size + tile_offset) * c.col + 8,
                               y + (tile_size + tile_offset) * c.row + 8);
        }
    }
}


Application::Application(const std::string &&title, const int &&width, const int &&height)
    : title(title), screen_width(width), screen_height(height),
      renderer(this->simulation.get_map().get_tile_size()), ui(nullptr)
{
    this->input_state = InputState {0, 0, NodeType::Empty, false, false, false};
}

bool Application::init()
{
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

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
    while (!input_state.exit)
    {
        // PROCESSING EVENTS / INPUT
        process_events(&event);
        this->simulation.process_input(this->input_state);

        // UPDATING
        this->simulation.update();

        // RENDERING
        this->renderer.clear_screen();
        draw_grid_map(0, 0, this->simulation.get_map(), this->renderer);

        if (!this->simulation.get_path().empty())
        {
            draw_path(0, 0, this->simulation.get_map(),
                      this->simulation.get_path(),
                      this->renderer);
        }

        this->ui->draw_and_process(this->input_state);

        this->renderer.render();
    }
}

void Application::cleanup()
{
    SDL_DestroyWindow(this->window);

    SDL_Quit();
}

void Application::process_events(SDL_Event *e)
{
    while (SDL_PollEvent(e))
    {
        // EXPERIMENTAL - IMGUI
        ui->process_events(e);
        //

        if (e->type == SDL_EVENT_QUIT)
        {
            this->input_state.exit = true;
        }

        else if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            this->input_state.mouse_button_down = true;
            this->input_state.x = e->button.x;
            this->input_state.y = e->button.y;

            if (e->button.button == SDL_BUTTON_LEFT)
            {
                this->input_state.selected_tile_type = static_cast<NodeType>(this->ui->get_current_tile() + 1);
            }
            else if (e->button.button == SDL_BUTTON_RIGHT)
            {
                this->input_state.selected_tile_type = NodeType::Empty;
            }
        }
    }
}
