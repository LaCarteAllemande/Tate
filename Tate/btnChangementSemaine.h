#pragma once

#include "qpushbutton.h"

class CalendarTab;

class btnChangementSemaine : public QPushButton
{
	Q_OBJECT

public:
	btnChangementSemaine(CalendarTab* tab);

public slots:
	void click();

private:
	const QString STYLE = "background-color: white;font-size:12px;font-weight:bold;padding: 5px 15px 5px;";
	CalendarTab* tab;
	static int numeroBtn; //compteur de boutons qui permet de determiner lequel des boutons est le premier (celui de gauche) ou le deuxième (de droite)
};
