#pragma once

#include "NodeType.h"

class Simulation;

class Command
{
public:
    virtual ~Command() = default;

    virtual void execute(Simulation &sim) = 0;
};

class SetTileCommand : public Command
{
public:
    SetTileCommand(float x, float y, NodeType type);

    void execute(Simulation &sim);

private:
    float x, y;
    NodeType tile_type;
};

class StartSimulationCommand : public Command
{
public:
    StartSimulationCommand() = default;

    void execute(Simulation &sim);
};
