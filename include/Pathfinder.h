#pragma once

#include <vector>
#include <functional>

#include "Map.h"
#include "MinHeap.hpp"

struct NodeRecord
{
    int index;
    float f;

    bool operator<(const NodeRecord &other) const
    {
        return this->f < other.f;
    }

    bool operator<=(const NodeRecord &other) const
    {
        return this->f <= other.f;
    }
};

using HeuristicFn = std::function<float(const Coord&, const Coord&)>;

class Pathfinder
{
public:
    Pathfinder(Map &map, HeuristicFn heuristic);

    void set_points(const Coord &start, const Coord &goal);
    void reset();

    std::vector<int> a_star();
    bool a_star_step(); // NOT IMPLEMENTED YET!

    void set_heuristic(HeuristicFn new_heuristic);

private:
    std::vector<int> get_neighbors(int index);

    Map &map;
    int start;
    int goal;

    HeuristicFn heuristic;

    MinHeap<NodeRecord> open_set;

    std::vector<bool> close_set;
    std::vector<float> g_score;
    std::vector<int> came_from;
};
