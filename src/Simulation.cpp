#include "Simulation.h"

Simulation::Simulation()
    : map("starter_map.txt", 32, 4)
{
}

void Simulation::process_input(InputState &is)
{
    if (is.mouse_button_down)
    {
	if ((is.selected_tile_type == NodeType::Start && this->map.is_start_set()) ||
	    (is.selected_tile_type == NodeType::Goal && this->map.is_goal_set()))
	{
	    is.mouse_button_down = false;
	    return;
	}

	int x = static_cast<int>(is.x);
	int y = static_cast<int>(is.y);

	int segment_size = this->map.get_tile_size() + this->map.get_tile_offset();
	int local_x = x % segment_size;
	int local_y = y % segment_size;

	if (in_boundries(x, y) &&
	    (local_x < this->map.get_tile_size() || local_y < this->map.get_tile_size()))
	{
	    int idx = this->map.to_index(Coord{y / segment_size,
					       x / segment_size});

	    NodeType prev_type = this->map[idx];

	    this->map[idx] = is.selected_tile_type;

	    if (prev_type == NodeType::Start)
	    {
		this->map.set_start(false);
	    }
	    else if (prev_type == NodeType::Goal)
	    {
		this->map.set_goal(false);
	    }

	    if (is.selected_tile_type == NodeType::Start)
	    {
		this->map.set_start(true);
	    }
	    else if (is.selected_tile_type == NodeType::Goal)
	    {
		this->map.set_goal(true);
	    }

	}

	is.mouse_button_down = false;
    }
}

void Simulation::update()
{
}

const Map& Simulation::get_map() const
{
    return map;
}

const bool Simulation::in_boundries(const int x, const int y) const
{
    int tile_size = this->map.get_tile_size();
    int tile_offset = this->map.get_tile_offset();

    int max_x = (tile_size + tile_offset) * this->map.get_width() - tile_offset;
    int max_y = (tile_size + tile_offset) * this->map.get_height() - tile_offset;

    if (x >= max_x || y >= max_y)
    {
	return false;
    }

    return true;
}
