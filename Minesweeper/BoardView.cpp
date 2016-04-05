#include "BoardView.h"
#include "QPainter"
#include <QMouseEvent>
#include <string>
#include <QMessageBox>
BoardView::BoardView(Game* game)
{
	m_game = game;
}
void BoardView::paintEvent(QPaintEvent*)
{

	QPainter p(this);
//	p.setBrush(QBrush(Qt::green));
	QPen border_light_pen(Qt::white);
	QPen border_dark_pen(Qt::black);
	QColor color;

	for (int x = 0, xe = m_game->get_board_width(); x < xe; x++)
	{
		for (int y = 0, ye = m_game->get_board_height(); y < ye; y++)
		{
			if (m_game->is_initial_cell(y, x))
				color = Qt::yellow;
			else 
				color = Qt::gray;
			p.fillRect(x * FIELD_WIDTH, y * FIELD_HEIGHT, FIELD_WIDTH, FIELD_HEIGHT, color);
			Cell* cell = m_game->get_cell(y, x);
			if (cell->is_covered)
			{
				p.setPen(border_light_pen);
				p.drawLine(x * FIELD_WIDTH, y * FIELD_HEIGHT, x * FIELD_WIDTH + 40, y * FIELD_HEIGHT);
				p.drawLine(x * FIELD_WIDTH, y * FIELD_HEIGHT, x * FIELD_WIDTH, y * FIELD_HEIGHT + 40);
				p.setPen(border_dark_pen);
				p.drawLine(x * FIELD_WIDTH + 40 - 1, y * FIELD_HEIGHT, x * FIELD_WIDTH + 40, y * FIELD_HEIGHT + 40 - 1);
				p.drawLine(x * FIELD_WIDTH, y * FIELD_HEIGHT + 40 - 1, x * FIELD_WIDTH + 40 - 1, y * FIELD_HEIGHT + 40 - 1);
			}
			if (!cell->is_covered)
			{

				{
					if (cell->is_mined)
					{
						p.fillRect(x*FIELD_WIDTH, y*FIELD_HEIGHT,FIELD_WIDTH, FIELD_HEIGHT, Qt::red);
					}
					else if (cell->mined_neighbour_count!=0)
						p.drawText(x * FIELD_WIDTH, y * FIELD_HEIGHT, 40, 40, Qt::AlignCenter, QString::number(cell->mined_neighbour_count));
						
				}
					
			}
			
		}
	}
}
void BoardView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && !m_game->is_game_over())
	{
		QPoint pos = event->pos();
		int x = pos.x() / FIELD_WIDTH;
		int y = pos.y() / FIELD_HEIGHT;
		if (x >= 0 && y >= 0 && x <= m_game->get_board_width() && y <= m_game->get_board_height())
		{
			m_game->uncover_cell(y, x);
			repaint();//TODO czy to jest prawidlowa metoda? 
			if (m_game->is_game_over())
				QMessageBox::information(this, "Mina!", "Koniec gry.");
		}
			
	}
	
}
void BoardView::recalculate_size()
{
	int width = FIELD_WIDTH*m_game->get_board_width();
	int height = FIELD_HEIGHT*m_game->get_board_height();
	this->setFixedSize(width, height);
}