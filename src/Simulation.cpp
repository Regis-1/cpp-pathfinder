#include "Simulation.h"
#include "Command.h"

#include <cassert>
#include <cmath>

namespace
{
    float manhattan_hfn(const Coord& node, const Coord& goal)
    {
        return std::abs(node.row - goal.row) + std::abs(node.col - goal.col);
    }
}

Simulation::Simulation(Map &&map)
    : map(std::move(map)), running(false), pf(nullptr)
{
    this->pf = new Pathfinder(this->map, manhattan_hfn);
}

Simulation::~Simulation()
{
    delete pf;
}

void Simulation::apply_command(Command *&command)
{
    if (command)
    {
        command->execute(*this);

        delete command;
        command = nullptr;
    }
}

void Simulation::update()
{
    if (this->running)
    {
        this->path = this->pf->a_star();
        this->pf->reset();

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

void Simulation::set_tile_pixels(float x, float y, NodeType type)
{
    int xi = static_cast<int>(std::floor(x));
    int yi = static_cast<int>(std::floor(y));

    if (!in_boundries(xi, yi))
    {
        return;
    }

    const int tile_size = this->map.get_tile_size();
    const int offset = this->map.get_tile_offset();
    const int segment = tile_size + offset;

    int local_x = xi % segment;
    int local_y = yi % segment;

    if (local_x >= tile_size || local_y >= tile_size)
    {
        return;
    }

    int col = xi / segment;
    int row = yi / segment;

    set_tile_coord(Coord{row, col}, type);
}

void Simulation::set_tile_coord(Coord pos, NodeType type)
{
    int idx = this->map.to_index(pos);
    NodeType prev = this->map[idx];

    if ((type == NodeType::Start && this->map.is_start_set()) ||
        (type == NodeType::Goal && this->map.is_goal_set()))
    {
        return;
    }

    if (prev == type)
    {
        return;
    }

    this->map[idx] = type;

    if (prev == NodeType::Start)
    {
        this->map.set_start(false);
    }

    if (prev == NodeType::Goal)
    {
        this->map.set_goal(false);
    }

    if (type == NodeType::Start)
    {
        this->map.set_start(true);
    }

    if (type == NodeType::Goal)
    {
        this->map.set_goal(true);
    }

    this->path.clear();
}

void Simulation::start_simulation()
{
    if (!this->map.is_start_set() || !this->map.is_goal_set())
    {
        return;
    }

    Endpoints ep = this->find_start_and_goal();

    this->pf->set_points(ep.start, ep.goal);

    this->running = true;
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
