#include "Command.h"

#include "Simulation.h"

SetTileCommand::SetTileCommand(float x, float y, NodeType type)
    : x(x), y(y), tile_type(type)
{}

void SetTileCommand::execute(Simulation &sim)
{
    sim.set_tile_pixels(this->x, this->y, this->tile_type);
}

void StartSimulationCommand::execute(Simulation &sim)
{
    sim.start_simulation();
}
