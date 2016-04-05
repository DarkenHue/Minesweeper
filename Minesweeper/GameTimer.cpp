#include "GameTimer.h"
#include "minesweeper.h"
GameTimer::GameTimer(Minesweeper *minesweeper)
{
	m_main_window = minesweeper;
	m_timer = new QTimer();
	m_timer->setInterval(1000);
	m_timer->setSingleShot(false);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
}
void GameTimer::start()
{
	m_tick_count = 0;
	m_timer->start();
}
void GameTimer::timer_timeout()
{
	m_tick_count++;
	m_main_window->update_tick_count();

}
void GameTimer::stop()
{


}
uint GameTimer::get_tick_count()
{
	return m_tick_count;
}
GameTimer::~GameTimer()
{
	delete m_timer;
}
