#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QtWidgets/QMainWindow>
#include "ui_minesweeper.h"
#include "Game.h"
#include "BoardView.h"
#include <qlabel>
class Minesweeper : public QMainWindow
{
	Q_OBJECT

public:
	Minesweeper(QWidget *parent = 0);
	~Minesweeper();
	void update_tick_count();
private:
	Ui::MinesweeperClass ui;
	Game *m_game;
	BoardView *m_board;
	QLabel *m_time_label;

private slots:
	void new_game();
	void quit();
	void option_window();
	
};

#endif // MINESWEEPER_H
