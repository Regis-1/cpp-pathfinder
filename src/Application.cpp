#include "Application.h"

#include "Pathfinder.h"

namespace
{
    void draw_grid_map(const int x, const int y, Map &map, Renderer &renderer)
    {
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

	    Coord c = map.to_coord(i);

            renderer.draw_tile(x + (32+4) * c.col, y + (32+4) * c.row);
        }
    }
}


Application::Application(const std::string &&title, const int &&width, const int &&height)
    : title(title), screen_width(width), screen_height(height)
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

    return true;
}

void Application::run()
{
    Map map(3, 3,
	    std::vector<NodeType>{NodeType::Empty, NodeType::Wall, NodeType::Empty,
				  NodeType::Empty, NodeType::Wall, NodeType::Empty,
				  NodeType::Empty, NodeType::Empty, NodeType::Wall});

    SDL_Event event;
    bool should_quit {false};
    while (!should_quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                should_quit = true;
            }
        }

        renderer.clear_screen();
        draw_grid_map(20, 20, map, renderer);
        renderer.render();
    }
}

void Application::cleanup()
{
    SDL_DestroyWindow(this->window);

    SDL_Quit();
}
