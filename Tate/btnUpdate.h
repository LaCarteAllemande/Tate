#pragma once

#include "qpushbutton.h"

class CalendarTab;

class btnUpdate : public QPushButton
{
	Q_OBJECT

public:
	btnUpdate(QWidget* wdg, CalendarTab* tab);
	
public slots:
	void click();

private:
	static QString getStyleBtn();
	CalendarTab* tab;
	const QString STYLE = "background-color: white; font-size:16px; font-weight:bold;";
};
