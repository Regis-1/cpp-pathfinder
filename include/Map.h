#pragma once

#include <cstddef>
#include <vector>

enum class NodeType
{
    Empty,
    Wall,
    Start,
    Goal
};

struct Coord
{
    int row;
    int col;
};

class Map
{
public:
    Map(int w, int h, std::vector<NodeType> n);

    Coord to_coord(const int index);
    int to_index(const Coord coord);

    const int size() const;

    const NodeType& operator[](size_t index) const;
    NodeType& operator[](size_t index);

    int width;
    int height;

private:
    std::vector<NodeType> nodes;
};
