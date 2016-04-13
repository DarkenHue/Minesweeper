#include "HighscoreWindow.h"
#include <QStandardItemModel>
#include <QVBoxLayout>
HighScoreWindow::HighScoreWindow()
{
	m_list_view = new QListView();
	m_list_view->setViewMode(QListView::ListMode);

	QStandardItemModel *model = new QStandardItemModel(3, 3);
	model->setHeaderData(0, Qt::Horizontal, QObject::tr("test header"));
	QStandardItem *item = new QStandardItem(QString("TEST 1"));
	model->setItem(0, 0, item);
	QStandardItem *item2 = new QStandardItem(QString("TEST 2"));
	model->setItem(0, 1, item2);
	m_list_view->setModel(model);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(m_list_view);
	setLayout(layout);
}