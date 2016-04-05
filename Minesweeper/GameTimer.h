#ifndef GAME_TIMER_H
#define GAME_TIMER_H
#include <qobject>
#include <Qtimer>
class Minesweeper;
class GameTimer : public QObject {

	Q_OBJECT

private:
	QTimer* m_timer;
	int m_tick_count;
	Minesweeper *m_main_window;
public:
	GameTimer(Minesweeper *m);
	~GameTimer();
	void start();
	void stop();
	uint get_tick_count();
	private slots:
	void timer_timeout();
	
};


#endif