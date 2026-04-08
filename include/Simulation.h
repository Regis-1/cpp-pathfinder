#pragma once

#include "Pathfinder.h"

struct InputState
{
    float x;
    float y;
    NodeType selected_tile_type;
    bool mouse_button_down;
    bool exit;
};

class Simulation
{
public:
    Simulation();

    void process_input(InputState &is);
    void update();
    const Map& get_map() const;

private:
    const bool in_boundries(const int x , const int y) const;

    Map map;
};
