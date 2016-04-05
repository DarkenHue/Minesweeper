#include "minesweeper.h"
#include "BoardView.h"
#include <QHBoxLayout>
#include "OptionsWindow.h"

Minesweeper::Minesweeper(QWidget *parent)
:	QMainWindow(parent)
{
	//ui.setupUi(this);
	//QHBoxLayout* layout = new QHBoxLayout();
	m_game = new Game();
	m_game->initialize();
	m_game->start();
	m_board = new BoardView(m_game);
	//layout->addWidget(board);
	this->setCentralWidget(m_board);
	
	
	QMenu *fileMenu;

	fileMenu = menuBar()->addMenu("&Game");
	QAction *action = new QAction("&New", this);
	action->setShortcuts(QKeySequence::New);
	action->setStatusTip(tr("Create a new file"));
	connect(action, SIGNAL(triggered()), this, SLOT(new_game()));
	fileMenu->addAction(action);

	action = new QAction("&Quit", this);
	action->setShortcuts(QKeySequence::Quit);
	connect(action, SIGNAL(triggered()), this, SLOT(quit()));
	fileMenu->addAction(action);

	action = new QAction("&Opcje", this);
	connect(action, SIGNAL(triggered()), this, SLOT(option_window()));
	fileMenu->addAction(action);
	

}
void Minesweeper::new_game()
{
	m_game->start();
	m_board->repaint();
}

void Minesweeper::quit()
{
	QApplication::quit();
}
void Minesweeper::option_window()
{
	Options options = m_game->get_options();
	OptionsWindow *window = new OptionsWindow(options);
	window->setModal(true);
	window->exec();
	if (window->is_ok_clicked())
	{
		m_game->set_options(options);
	}
	delete window;
}
Minesweeper::~Minesweeper()
{

}
