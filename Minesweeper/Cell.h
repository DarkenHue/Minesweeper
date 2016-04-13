#include "globals.h"
struct Cell
{
	bool is_mined;
	bool is_covered;
	bool is_flaged;
	uint mined_neighbour_count;
	uint neighbour_count;

	Cell* neighbours[8];
	uint x;
	uint y;
};