#include <cassert>

#include "Map.h"

Map::Map(int w, int h, int tile_size, int tile_offset, std::vector<NodeType> n)
    : width(w), height(h), tile_size(tile_size), tile_offset(tile_offset),
      nodes(std::move(n)), start_set(false), goal_set(false)
{
    assert(this->nodes.size() == this->width * this->height);
}

Coord Map::to_coord(const int index) const
{
    return Coord{index / this->width, index % this->width};
}

int Map::to_index(const Coord coord) const
{
    return coord.row * this->width + coord.col;
}

const int Map::size() const
{
    return this->width * this->height;
}

const int Map::get_width() const
{
    return this->width;
}

const int Map::get_height() const
{
    return this->height;
}

const int Map::get_tile_size() const
{
    return this->tile_size;
}

const int Map::get_tile_offset() const
{
    return this->tile_offset;
}

const bool Map::is_start_set() const
{
    return start_set;
}

const bool Map::is_goal_set() const
{
    return goal_set;
}

void Map::set_start(const bool value)
{
    this->start_set = value;
}

void Map::set_goal(const bool value)
{
    this->goal_set = value;
}

const NodeType& Map::operator[](size_t index) const
{
    return this->nodes[index];
}

NodeType& Map::operator[](size_t index)
{
    return this->nodes[index];
}
