#include "btnChangementSemaine.h"
#include "CalendarTab.h"

const static QString LEFT = "<";
const static QString RIGHT = ">";
int btnChangementSemaine::numeroBtn = 0;

/*
Bouton qui sert � passer d'une semaine � l'autre, n�cessite un onglet agenda */
btnChangementSemaine::btnChangementSemaine(CalendarTab* tab)
{
	this->setParent(tab);
	this->tab = tab;

	// On attribue le caract�re correspondant au bouton selon s'il est celui de gauche ou de droite
	if(numeroBtn==0)
		this->setText(LEFT);
	else
		this->setText(RIGHT);

	this->setCursor(Qt::PointingHandCursor);
	this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	this->setStyleSheet(STYLE);
	connect(this, SIGNAL(clicked(bool)), this, SLOT(click()));

	numeroBtn = +1; // on incr�mente le compteur de boutons
}

/*
Comportement au clic*/
void btnChangementSemaine::click()
{
	tab->changementSemaine(this->text());
}
