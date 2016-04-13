#ifndef GAME_H
#define GAME_H
#include <random>
#include <vector>
#include <iostream>
#include "Cell.h"
#include "globals.h"
#include "Options.h"
#include "GameTimer.h"

class Minesweeper; 

class Game 
{
private:
	uint CELLS_X;
	uint CELLS_Y;
	uint CELLS_N;
	double mine_percentage;
	Cell **m_board;
	Cell* initial_cell;
	bool game_is_over;
	Options m_options; 
	void put_mines();
	void pick_initial_cell();
	GameTimer m_game_timer;
	uint m_uncovered_cells_count;

public:
	Game(Minesweeper *m);
	bool is_game_over();
	int get_board_width();
	int get_board_height();
	Cell* get_cell(uint x, uint y);
	void initialize();
	void start();
	void draw();
	void uncover_cell(uint y, uint x);
	bool is_initial_cell(uint y, uint x);
	const Options &get_options() const;
	void set_options(const Options& options);
	void toggle_cell_flag(uint x, uint y);
	uint get_seconds_passed();
};
#endif