#pragma once

#include "qdialog.h"
#include <qpushbutton.h>
#include "Day.h"
#include <qlineedit.h>
#include <qgroupbox.h>
#include <qlistwidget.h>


/*
Dialog that enables the user to add and delete daily tasks for a day
This class should always be temporary and shouldn't be stored
*/
class DailyTaskWindow : public QDialog {
	Q_OBJECT


public:
	DailyTaskWindow(QWidget* father, Day* day) ;


public slots:

	void deleteDT();
	void addDT();
private:
	
	QPushButton deleteBtn;
	QBoxLayout layout;
	QPushButton addBtn;
	QGroupBox groupBox;
	QLineEdit lineEdit;

	Day* day=nullptr; //The day the dialog will handle


	QListWidget list;

	/**
	 * Add the daily tasks of the day to the list
	 */
	void addTaskstoList();
};
