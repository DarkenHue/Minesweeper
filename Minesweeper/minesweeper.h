#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QtWidgets/QMainWindow>
#include "ui_minesweeper.h"
#include "Game.h"
#include "BoardView.h"
class Minesweeper : public QMainWindow
{
	Q_OBJECT

public:
	Minesweeper(QWidget *parent = 0);
	~Minesweeper();
private:
	Ui::MinesweeperClass ui;
	Game* m_game;
	BoardView* m_board;
private slots:
	void new_game();
	void quit();
	void option_window();
};

#endif // MINESWEEPER_H
