#pragma once

#include "NodeType.h"

struct InputState
{
    float x;
    float y;
    NodeType selected_tile_type;
    bool mouse_button_down;
    bool simulation_run;
    bool exit;
};
