#pragma once

#include <cstddef>
#include <vector>
#include <string>

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
    Map(int w, int h, int tile_size, int tile_offset, std::vector<NodeType> n);
    Map(const std::string &&path, int tile_size, int tile_offset);

    Coord to_coord(const int index) const;
    int to_index(const Coord coord) const;

    const int size() const;
    const int get_width() const;
    const int get_height() const;
    const int get_tile_size() const;
    const int get_tile_offset() const;

    const bool is_start_set() const;
    const bool is_goal_set() const;
    void set_start(const bool value);
    void set_goal(const bool value);

    const NodeType& operator[](size_t index) const;
    NodeType& operator[](size_t index);

private:
    std::vector<NodeType> nodes;

    int width;
    int height;
    int tile_size;
    int tile_offset;

    bool start_set;
    bool goal_set;
};
