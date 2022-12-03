#pragma once

#include "qpushbutton.h"
#include "qevent.h"
#include "week.h"
#include "qmenu.h"

class CalendarTab;

class BtnHeure : public QPushButton
{
	Q_OBJECT

public:
	BtnHeure(unsigned int, Week* , QWidget* wdg, CalendarTab* o);
	unsigned int getHeure();

public slots:
	void mousePressEvent(QMouseEvent* e);
	void clicDroit();
	void click();

private:
	unsigned int heure;
	Week* semaine;
	CalendarTab* tab;

	void boutonAjout();

signals:
	void rightClicked();
};

