#include "Game.h"
#include "Qsettings"
Game::Game(Minesweeper *minesweeper)
:m_game_timer(minesweeper)
{
	m_options.show_initial_cell = true;
	m_options.board_size = Options::BIG;
	m_options.mine_percentage = 20;
	
}
void Game::put_mines()
{

	Cell** cells = new Cell*[CELLS_N];

	uint cell = 0;
	for (uint y = 0; y < CELLS_Y; y++)
	{
		for (uint x = 0; x < CELLS_X; x++)
			cells[cell++] = &m_board[y][x];
	}

	const uint mine_percentage = m_options.mine_percentage;

	for (uint i = 0; i <mine_percentage; i++)
	{
		uint index = rand() % (CELLS_N - i);
		cells[index]->is_mined = true;
		for (uint j = 0; j < cells[index]->neighbour_count; j++)
			cells[index]->neighbours[j]->mined_neighbour_count++;
		std::swap(cells[index], cells[CELLS_N - i - 1]);
	}

}


void Game::pick_initial_cell()
{
	initial_cell = NULL;
	if (m_options.show_initial_cell)
	{
		std::vector<Cell*> cells;
		for (int x = 0; x < CELLS_X; x++)
		{
			for (int y = 0; y < CELLS_Y; y++)
			{
				if (m_board[y][x].mined_neighbour_count == 0 && !m_board[y][x].is_mined)
					cells.push_back(&m_board[y][x]);

			}
		}
		if (cells.size() != 0)
			initial_cell = cells[rand() % cells.size()];
	}
}

int Game::get_board_width()
{
	return CELLS_X;
}
int Game::get_board_height()
{
	return CELLS_Y;
}
Cell* Game::get_cell(uint x, uint y)
{
	return &m_board[x][y];
}

void Game::initialize()
{

	QSettings settings;
	settings.beginGroup(QString(game_settings_group_name));
	m_options.show_initial_cell = settings.value("show_initial_cell", true).toBool();
	m_options.mine_percentage = settings.value("mine_percentage", 10).toInt();
	m_options.board_size = (Options::BoardSize)settings.value("board_size", Options::TINY).toInt();
	settings.endGroup();
	m_uncovered_cells_count = 0;
	switch (m_options.board_size)
	{
	case Options::TINY:
		{
			CELLS_X = 8; 
			CELLS_Y = 8;
				
			break;
		}
	case Options::SMALL:
	{
			CELLS_X = 10;
			CELLS_Y = 10;
			break;
	}
	case Options::MEDIUM:
	{
			CELLS_X = 12;
			CELLS_Y = 12;
			break;
	}
	case Options::BIG:
	{
			CELLS_X = 15;
			CELLS_Y = 10;
			break;
	}
	case Options::HUGE:
	{
			CELLS_X = 25;
			CELLS_Y = 20;
			break;
	}
	}
	CELLS_N = CELLS_X*CELLS_Y;
	mine_percentage = m_options.mine_percentage;
	m_board = new Cell*[CELLS_Y];
	for (int i = 0; i < CELLS_Y; i++)
		m_board[i] = new Cell[CELLS_X];

	for (uint y = 0; y < CELLS_Y; y++)
	{
		for (uint x = 0; x < CELLS_X; x++)
		{
			Cell& cell = m_board[y][x];
			cell.x = x;
			cell.y = y;
			cell.neighbour_count = 0;
			for (int yy = int(y) - 1; yy <= int(y) + 1; yy++)
			{
				if (yy < CELLS_Y && yy >= 0)
				{
					for (int xx = int(x) - 1; xx <= int(x) + 1; xx++)
					{
						if (xx < CELLS_X && xx >= 0 && (x != xx || y != yy))
						{
							cell.neighbours[cell.neighbour_count++] = &m_board[yy][xx];
						}
					}
				}
			}
		}
	}
}
void Game::start()
{
	for (uint y = 0; y < CELLS_Y; y++)
	{
		for (uint x = 0; x < CELLS_X; x++)
		{
			m_board[y][x].mined_neighbour_count = 0;
			m_board[y][x].is_mined = false;
			m_board[y][x].is_covered = true;
			m_board[y][x].is_flaged = false;
		}
	}

	game_is_over = false;
	put_mines();
	pick_initial_cell();
	m_game_timer.start();
	
}
void Game::draw()
{

	for (uint y = 0; y < CELLS_Y; y++)
	{
		for (uint x = 0; x < CELLS_X; x++)
		{
			if (m_board[y][x].is_covered)
			{
				if (Game::initial_cell != NULL && &m_board[y][x] == Game::initial_cell)
				{
					std::cout << "!";
				}
				else
				{
					std::cout << ".";
				}

			}
			else if (m_board[y][x].is_mined)
			{
				std::cout << "X";
			}

			else
				std::cout << m_board[y][x].mined_neighbour_count;

		}
		std::cout << std::endl;
	}
	if (game_is_over == true)
	{
		std::cout << "GAME OVER" << std::endl;
	}

}
void Game::uncover_cell(uint y, uint x)
{
	if (!game_is_over)
	{
		Cell& cell = m_board[y][x];
		if (!cell.is_covered)
			return;
		cell.is_covered = false;
		cell.is_flaged = false;
		initial_cell = NULL;

		if (cell.is_mined == true)
		{
			game_is_over = true;
		}
		else if (cell.mined_neighbour_count == 0)
		{
			for (int j = 0; j < cell.neighbour_count; j++)
			{

				uncover_cell(cell.neighbours[j]->y, cell.neighbours[j]->x);
				m_uncovered_cells_count++;
			}
		}
			
	}

}
void Game::toggle_cell_flag(uint x, uint y)
{
	if (m_board[y][x].is_covered && !m_board[y][x].is_flaged)
	{
		m_board[y][x].is_flaged = true;
	}
	else
		m_board[y][x].is_flaged = false;
}
bool Game::is_initial_cell(uint y, uint x)
{
	return &m_board[y][x] == initial_cell;

}

bool Game::is_game_over()
{
	return game_is_over;
}
const Options &Game::get_options() const
{
	return m_options;
}
	
uint Game::get_seconds_passed()
{
	return m_game_timer.get_tick_count();
}
void Game::set_options(const Options& options)
{
	m_options = options;

	initialize();
	start();
}