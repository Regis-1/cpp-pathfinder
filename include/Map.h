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

struct Node
{
    int x;
    int y;
    NodeType type;
};

class Map
{
public:
    Map() = delete;
    Map(const int w, const int h, std::vector<Node> &&nodes);

    int index(const int x, const int y) const;
    Node& at(const int x, const int y);
    int size() const;

    Node& operator[](size_t index);
    const Node& operator[](size_t index) const;

private:
    std::vector<Node> nodes;

    int width, height;
    int origin_x, origin_y;
};
