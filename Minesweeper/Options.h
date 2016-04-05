#ifndef OPTIONS_H
#define OPTIONS_H
struct Options {
	bool show_initial_cell;
	enum BoardSize
	{
		TINY, SMALL, MEDIUM, BIG, HUGE
	};
	BoardSize board_size;
	int mine_count;
};
#endif