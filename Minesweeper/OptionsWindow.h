#ifndef OPTIONS_WINDOW_H
#define OPTIONS_WINDOW_H
#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include "Options.h"
class OptionsWindow : public QDialog {
	Q_OBJECT
public:
	OptionsWindow(Options &options);
	bool is_ok_clicked();
private:
	Options* m_options;
	bool m_is_ok_clicked;
	QCheckBox *m_show_initial_cell_checkbox;
	QComboBox *m_board_size_combobox;
	QComboBox *m_mine_percentage_select;
private slots:
	void ok_clicked();
	void cancel_clicked();
	
};

#endif