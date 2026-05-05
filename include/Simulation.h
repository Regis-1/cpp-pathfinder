#pragma once

#include "Pathfinder.h"

class Command;

struct Endpoints {
    Coord start;
    Coord goal;
};

class Simulation
{
public:
    Simulation(Map &&map);
    ~Simulation();

    void apply_command(Command *&command);
    void update();
    const Map& get_map() const;
    const std::vector<int>& get_path() const;

    void set_tile_pixels(float x, float y, NodeType type);
    void set_tile_coord(Coord pos, NodeType type);

    void start_simulation();


private:
    const bool in_boundries(const int x , const int y) const;

    Endpoints find_start_and_goal();

    Pathfinder *pf;
    Map map;

    std::vector<int> path;

    bool running;
};
