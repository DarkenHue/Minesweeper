#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include <qwidget>
#include "Game.h"
class BoardView : public QWidget
{
	Q_OBJECT
public:
	BoardView(Game *game);
	virtual void paintEvent(QPaintEvent*) override;
	virtual void mousePressEvent(QMouseEvent *eventPress) override;
private:
	Game* m_game;
	int const FIELD_WIDTH = 40;
	int const FIELD_HEIGHT = 40;
};
#endif