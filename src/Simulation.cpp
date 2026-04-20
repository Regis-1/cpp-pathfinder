#include "Simulation.h"

#include <cassert>

namespace
{
    float manhattan_hfn(const Coord& node, const Coord& goal)
    {
        return 0.0f;
    }
}

Simulation::Simulation()
    : map("starter_map.txt", 32, 4), running(false), path_computed(false),
      pf(nullptr)
{
    this->pf = new Pathfinder(this->map, manhattan_hfn);
}

Simulation::~Simulation()
{
    delete pf;
}

void Simulation::process_input(InputState &is)
{
    if (is.mouse_button_down)
    {
        if ((is.selected_tile_type == NodeType::Start && this->map.is_start_set()) ||
            (is.selected_tile_type == NodeType::Goal && this->map.is_goal_set()))
        {
            is.mouse_button_down = false;
            return;
        }

        int x = static_cast<int>(is.x);
        int y = static_cast<int>(is.y);

        int segment_size = this->map.get_tile_size() + this->map.get_tile_offset();
        int local_x = x % segment_size;
        int local_y = y % segment_size;

        if (in_boundries(x, y) &&
            (local_x < this->map.get_tile_size() || local_y < this->map.get_tile_size()))
        {
            int idx = this->map.to_index(Coord{y / segment_size,
                                               x / segment_size});

            NodeType prev_type = this->map[idx];

            this->map[idx] = is.selected_tile_type;

            if (prev_type == NodeType::Start)
            {
                this->map.set_start(false);
            }
            else if (prev_type == NodeType::Goal)
            {
                this->map.set_goal(false);
            }

            if (is.selected_tile_type == NodeType::Start)
            {
                this->map.set_start(true);
            }
            else if (is.selected_tile_type == NodeType::Goal)
            {
                this->map.set_goal(true);
            }

        }

        if (!this->path.empty())
        {
            this->path.clear();
        }

        is.mouse_button_down = false;
    }

    if (is.simulation_run)
    {
        is.simulation_run = false;

        if (!this->map.is_start_set() || !this->map.is_goal_set())
        {
            return;
        }

        Endpoints ep = this->find_start_and_goal();

        this->pf->set_points(ep.start, ep.goal);

        this->running = true;
    }
}

void Simulation::update()
{
    if (this->running)// && !this->path_computed)
    {
        this->path = this->pf->a_star();
        this->pf->reset();

        //this->path_computed = true;
        this->running = false;
    }
}

const Map& Simulation::get_map() const
{
    return this->map;
}

const std::vector<int>& Simulation::get_path() const
{
    return this->path;
}

const bool Simulation::in_boundries(const int x, const int y) const
{
    int tile_size = this->map.get_tile_size();
    int tile_offset = this->map.get_tile_offset();

    int max_x = (tile_size + tile_offset) * this->map.get_width() - tile_offset;
    int max_y = (tile_size + tile_offset) * this->map.get_height() - tile_offset;

    if (x >= max_x || y >= max_y)
    {
        return false;
    }

    return true;
}

Endpoints Simulation::find_start_and_goal()
{
    Endpoints endpoints;
    bool found[2] = {false, false};

    for (int i = 0; i < map.size(); ++i)
    {
        if (map[i] == NodeType::Start)
        {
            found[0] = true;
            endpoints.start = this->map.to_coord(i);
        }
        else if(map[i] == NodeType::Goal)
        {
            found[1] = true;
            endpoints.goal = this->map.to_coord(i);
        }
    }

    return endpoints;
}
