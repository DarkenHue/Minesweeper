#include "OptionsWindow.h"
#include <QFormLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QString>
#include <qpushbutton>
#include <QHBoxLayout>
OptionsWindow::OptionsWindow(Options &options)
{
	m_options = &options;

	m_is_ok_clicked = false;
	QGroupBox *formGroupBox = new QGroupBox(tr("Options"));
	QFormLayout *form_layout = new QFormLayout; 
	formGroupBox->setLayout(form_layout);

	m_board_size_combobox = new QComboBox(this);
	m_board_size_combobox->addItem("Tiny", Options::TINY);
	m_board_size_combobox->addItem("Small", Options::SMALL);
	m_board_size_combobox->addItem("Medium", Options::MEDIUM);
	m_board_size_combobox->addItem("Big", Options::BIG);
	m_board_size_combobox->addItem("Huge", Options::HUGE);
	int index = m_board_size_combobox->findData(m_options->board_size);
	m_board_size_combobox->setCurrentIndex(index);

	m_show_initial_cell_checkbox = new QCheckBox(this);
	m_show_initial_cell_checkbox->setChecked(m_options->show_initial_cell);


	m_mine_count_select = new QComboBox(this);
	m_mine_count_select->addItem("10%", 10);
	m_mine_count_select->addItem("20%", 20);
	m_mine_count_select->addItem("30%", 30);
	m_mine_count_select->addItem("40%", 40);
	m_mine_count_select->addItem("50%", 50);
	int mine_index = m_mine_count_select->findData(m_options->mine_count);
	m_mine_count_select->setCurrentIndex(mine_index);


	form_layout->addRow("&Show initial cell", m_show_initial_cell_checkbox);
	form_layout->addRow("Board size: ", m_board_size_combobox);
	form_layout->addRow("Difficulty: ", m_mine_count_select);
	QVBoxLayout *vbox_layout = new QVBoxLayout;
	vbox_layout->addWidget(formGroupBox);


	QPushButton *ok_button = new QPushButton("OK");
	connect(ok_button, SIGNAL(clicked()), this, SLOT(ok_clicked()));
	QPushButton *cancel_button = new QPushButton("Cancel");
	connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancel_clicked()));
	QHBoxLayout *hbox_layout = new QHBoxLayout;
	hbox_layout->addWidget(ok_button);
	hbox_layout->addWidget(cancel_button);
	vbox_layout->addItem(hbox_layout);
	setLayout(vbox_layout);
}
void OptionsWindow::ok_clicked() 
{
	m_options->show_initial_cell = m_show_initial_cell_checkbox->checkState();
	m_options->board_size = (Options::BoardSize)m_board_size_combobox->currentData().toInt();
	m_options->mine_count = m_mine_count_select->currentData().toInt();
	m_is_ok_clicked = true;
	close();

}
void OptionsWindow::cancel_clicked()
{
	this->close();
}
bool OptionsWindow::is_ok_clicked()
{
	return m_is_ok_clicked;
}

