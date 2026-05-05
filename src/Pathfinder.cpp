#include <limits>

#include "Pathfinder.h"

Pathfinder::Pathfinder(Map &map, HeuristicFn heuristic)
    : map(map), heuristic(heuristic)
{
    size_t nodes_count = map.size();

    this->g_score.assign(nodes_count, std::numeric_limits<float>::infinity());
    this->came_from.assign(nodes_count, -1);
    this->close_set.assign(nodes_count, false);

    this->open_set.clear();
}

void Pathfinder::set_points(const Coord &start, const Coord &goal)
{
    this->start = this->map.to_index(start);
    this->goal = this->map.to_index(goal);
}

void Pathfinder::reset()
{
    std::fill(this->g_score.begin(), this->g_score.end(),
              std::numeric_limits<float>::infinity());
    std::fill(this->came_from.begin(), this->came_from.end(), -1);
    std::fill(this->close_set.begin(), this->close_set.end(), false);

    this->open_set.clear();
}

std::vector<int> Pathfinder::a_star()
{
    std::vector<int> path;

    g_score[this->start] = 0.0f;
    float h_cost = this->heuristic(map.to_coord(this->start),
                                   map.to_coord(this->goal));

    this->open_set.push(NodeRecord{this->start, h_cost});

    while (!this->open_set.is_empty())
    {
        NodeRecord current = this->open_set.top();

        this->open_set.pop();

        if (close_set[current.index])
        {
            continue;
        }

        if (current.index == this->goal)
        {
            for (int idx = goal; idx != -1; idx = came_from[idx])
            {
                path.push_back(idx);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        this->close_set[current.index] = true;

        for (int neighbor : get_neighbors(current.index))
        {
            if (this->close_set[neighbor])
            {
                continue;
            }

            // +1.0f as each travelable tile is equal in movement terms
            float tentative_g = g_score[current.index] + 1.0f;

            if (tentative_g < g_score[neighbor])
            {
                g_score[neighbor] = tentative_g;
                came_from[neighbor] = current.index;

                h_cost = this->heuristic(map.to_coord(neighbor),
                                         map.to_coord(this->goal));

                open_set.push(NodeRecord{neighbor, tentative_g + h_cost});
            }
        }
    }

    return path;
}

bool Pathfinder::a_star_step() // NOT IMPLEMENTED YET!
{
    return false;
}

void Pathfinder::set_heuristic(HeuristicFn new_heuristic)
{
    this->heuristic = new_heuristic;
}

std::vector<int> Pathfinder::get_neighbors(int index)
{
    std::vector<int> neighbors;
    neighbors.reserve(4);

    int w = this->map.get_width();
    int h = this->map.get_height();

    int row = index / w;
    int col = index % w;

    const int d_row[] = { -1, 1, 0, 0 };
    const int d_col[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; ++i)
    {
        int new_row = row + d_row[i];
        int new_col = col + d_col[i];

        if (new_row >= 0 && new_row < h && new_col >= 0 && new_col < w)
        {
            int new_index = new_row * w + new_col;

            if (this->map[new_index] != NodeType::Wall)
            {
                neighbors.push_back(new_index);
            }
        }
    }

    return neighbors;
}
