#pragma once

#include "Pathfinder.h"

struct InputState;

struct Endpoints {
    Coord start;
    Coord goal;
};

class Simulation
{
public:
    Simulation();
    ~Simulation();

    void process_input(InputState &is);
    void update();
    const Map& get_map() const;
    const std::vector<int>& get_path() const;

private:
    const bool in_boundries(const int x , const int y) const;

    Endpoints find_start_and_goal();

    Pathfinder *pf;
    Map map;

    std::vector<int> path;

    bool running;
    bool path_computed;
};
