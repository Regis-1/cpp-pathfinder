#include <cassert>
#include <fstream>

#include "Map.h"

namespace
{
    void load_map_from_file(const std::string &path, int &w, int &h,
                            std::vector<NodeType> &nodes)
    {
        assert(!path.empty());

        std::ifstream map_file(path);

        map_file >> w;
        map_file >> h;

        int type = 0;
        while(map_file >> type)
        {
            if (type == 0)
            {
                nodes.push_back(NodeType::Empty);
            }
            else if (type == 1)
            {
                nodes.push_back(NodeType::Wall);
            }
        }

        map_file.close();
        assert(nodes.size() == w * h);
    }
}

Map::Map(int w, int h, int tile_size, int tile_offset, std::vector<NodeType> n)
    : width(w), height(h), tile_size(tile_size), tile_offset(tile_offset),
      nodes(std::move(n)), start_set(false), goal_set(false)
{
    assert(this->nodes.size() == this->width * this->height);
}

Map::Map(const std::string &&path, int tile_size, int tile_offset)
    : tile_size(tile_size), tile_offset(tile_offset),
      start_set(false), goal_set(false)
{
    load_map_from_file(path, this->width, this->height, this->nodes);
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
