#pragma once

#include "qpushbutton.h"
#include "qwidget.h"


/*
Button that display the date of a day in the calendar tab
Open the daily tasks tab when clicked
*/

class CalendarTab; 
class Day;

class DayBtn : public QPushButton
{
	Q_OBJECT


public:

	DayBtn(CalendarTab* calendarTab);
	void setDay(Day* day);


public slots:
	void click();

private:
	CalendarTab* calendarTab;
	Day* day;

};

