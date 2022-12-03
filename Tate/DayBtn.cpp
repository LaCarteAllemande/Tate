#include "DayBtn.h"
#include "CalendarTab.h"
#include "Day.h"


DayBtn::DayBtn(CalendarTab* calendar)
{
	this->calendarTab = calendar;

	this->setParent(calendar);
	this->setCursor(Qt::PointingHandCursor);
	connect(this, SIGNAL(clicked(bool)), this, SLOT(click()));
}

void DayBtn::click()
{
	calendarTab->showSidePanel(day);
}

void DayBtn::setDay(Day* day) {
	this->day = day;
	this->setText(QString::fromStdString(day->getDate()));
}
