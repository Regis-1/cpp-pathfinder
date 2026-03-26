#include <utility>

#include "Map.h"

Map::Map(const int w, const int h, std::vector<Node> &&nodes)
    : width(w), height(h), nodes(std::move(nodes)), origin_x(w/2), origin_y(h/2)
{}

int Map::index(const int x, const int y) const
{
    int ax = x + this->origin_x;
    int ay = this->origin_y - y;
    return ay * this->width + ax;
}

Node& Map::at(const int x, const int y)
{
    int index = this->index(x, y);
    return this->nodes[index];
}

int Map::size() const
{
    return this->width * this->height;
}

Node& Map::operator[](size_t index)
{
    return this->nodes[index];
}

const Node& Map::operator[](size_t index) const
{
    return this->nodes[index];
}
