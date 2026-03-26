#pragma once

#include <array>
#include <vector>
#include <functional>

#include "Map.h"

class Pathfinder
{
public:
    // Pathfinder(const Map *map, HeuristicFn heuristic);

    // Path a_star(const Node &start, const Node &end);

    // void init(const Node &start, const Node &end);
    // bool a_star_step();

    // void update_heuristic(HeuristicFn new_heuristic);
    // void update_map(const Map *new_map);

    // const std::vector<Node>& get_open_set() const;
    // const std::vector<Node>& get_closed_set() const;
    // const Path& get_path() const;

private:
    const Map *map;
    // HeuristicFn heuristic;

    // std::vector<Node> open_set;
    // std::vector<Node> closed_set;

    // Path path;

    int start[2];
    int end[2];
};
