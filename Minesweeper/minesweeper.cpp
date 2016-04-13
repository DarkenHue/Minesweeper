#include "minesweeper.h"
#include "BoardView.h"
#include <QHBoxLayout>
#include "OptionsWindow.h"
#include <QDesktopWidget>
#include <QSizePolicy>
#include <QHBoxLayout>
#include "HighscoreWindow.h"
Minesweeper::Minesweeper(QWidget *parent)
:	QMainWindow(parent)
{
	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	//ui.setupUi(this);
	QCoreApplication::setOrganizationName("Sawicki");
	QCoreApplication::setOrganizationDomain("Milan");
	QCoreApplication::setApplicationName("Minesweeper");

	m_game = new Game(this);
	m_game->initialize();
	m_game->start();

	QLabel* time_text_label = new QLabel("Time:");
	m_time_label = new QLabel();
	QHBoxLayout *time_layout = new QHBoxLayout();
	time_layout->addWidget(time_text_label);
	time_layout->addWidget(m_time_label);

	m_board = new BoardView(m_game);
	m_board->recalculate_size();
	central_widget = new QWidget();
	QVBoxLayout *vertical_layout = new QVBoxLayout();
	vertical_layout->addItem(time_layout);
	vertical_layout->addWidget(m_board);
	central_widget->setLayout(vertical_layout);
	vertical_layout->setSizeConstraint(QLayout::SetFixedSize);
	setCentralWidget(central_widget);


	QMenu *fileMenu;
	fileMenu = menuBar()->addMenu("&Game");

	QAction *action = new QAction("&New", this);
	action->setShortcuts(QKeySequence::New);
	action->setStatusTip(tr("Create a new file"));
	connect(action, SIGNAL(triggered()), this, SLOT(new_game()));
	fileMenu->addAction(action);

	action = new QAction("&Options", this);
	connect(action, SIGNAL(triggered()), this, SLOT(option_window()));
	fileMenu->addAction(action);
	
	action = new QAction("&Highscores", this);
	connect(action, SIGNAL(triggered()), this, SLOT(highscores_window()));
	fileMenu->addAction(action);

	action = new QAction("&Quit", this);
	action->setShortcuts(QKeySequence::Quit);
	connect(action, SIGNAL(triggered()), this, SLOT(quit()));
	fileMenu->addAction(action);

	

}
void Minesweeper::new_game()
{
	
	m_game->start();
	update_tick_count();
	m_board->repaint();
}

void Minesweeper::update_tick_count()
{
	m_time_label->setText(QString::number(m_game->get_seconds_passed()));
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
		m_board->recalculate_size();
		//this->setFixedSize(central_widget->size());
		//this->setFixedSize(central_widget->maximumSize());

	}
	delete window;
}
void Minesweeper::highscores_window()
{
	HighScoreWindow *window = new HighScoreWindow();
	window->setModal(true);
	window->exec();
}
Minesweeper::~Minesweeper()
{

}
