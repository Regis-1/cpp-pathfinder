#include <cassert>

#include "Map.h"

Map::Map(int w, int h, std::vector<NodeType> n)
    : width(w), height(h), nodes(std::move(n))
{
    assert(this->nodes.size() == this->width * this->height);
}

Coord Map::to_coord(const int index)
{
    return Coord{index / this->width, index % this->width};
}

int Map::to_index(const Coord coord)
{
    return coord.row * this->width + coord.col;
}

const int Map::size() const
{
    return this->width * this->height;
}

const NodeType& Map::operator[](size_t index) const
{
    return this->nodes[index];
}

NodeType& Map::operator[](size_t index)
{
    return this->nodes[index];
}
