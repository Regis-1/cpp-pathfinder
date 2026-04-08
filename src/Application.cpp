#include "Application.h"

namespace
{
    void draw_grid_map(const int x, const int y, const Map &map, Renderer &renderer)
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
	    else if (map[i] == NodeType::Start)
	    {
                renderer.set_draw_color(0x00, 0x88, 0x00, 0xFF);
	    }
	    else if (map[i] == NodeType::Goal)
	    {
                renderer.set_draw_color(0x88, 0x00, 0x00, 0xFF);
	    }

	    Coord c = map.to_coord(i);

            renderer.draw_tile(x + (map.get_tile_size() + map.get_tile_offset())
			       * c.col,
			       y + (map.get_tile_size() + map.get_tile_offset())
			       * c.row);
        }
    }
}


Application::Application(const std::string &&title, const int &&width, const int &&height)
    : title(title), screen_width(width), screen_height(height)
{
    this->input_state = InputState {0, 0, NodeType::Empty, false, false};
}

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
    SDL_Event event;
    while (!input_state.exit)
    {
	process_events(&event);

	this->simulation.process_input(this->input_state);
	this->simulation.update();

        this->renderer.clear_screen();
        draw_grid_map(0, 0, this->simulation.get_map(), this->renderer);
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
	if (e->type == SDL_EVENT_QUIT)
	{
	    this->input_state.exit = true;
	}

	else if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
	{
	    this->input_state.mouse_button_down = true;
	    this->input_state.x = e->button.x;
	    this->input_state.y = e->button.y;
	}

	else if (e->type == SDL_EVENT_KEY_DOWN)
	{
	    if (e->key.key == SDLK_W)
	    {
		this->input_state.selected_tile_type = NodeType::Wall;
	    }
	    else if (e->key.key == SDLK_E)
	    {
		this->input_state.selected_tile_type = NodeType::Empty;
	    }
	    else if (e->key.key == SDLK_S)
	    {
		this->input_state.selected_tile_type = NodeType::Start;
	    }
	    else if (e->key.key == SDLK_G)
	    {
		this->input_state.selected_tile_type = NodeType::Goal;
	    }
	}
    }
}
