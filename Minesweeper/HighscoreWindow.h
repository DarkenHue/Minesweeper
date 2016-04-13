#include <qdialog>
#include <QListView>
class HighScoreWindow : public QDialog
{
	Q_OBJECT 
public:
	HighScoreWindow();
private:
	QListView *m_list_view;
};