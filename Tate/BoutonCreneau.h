#pragma once

#include "qpushbutton.h"
#include "qwidget.h"
#include "creneau.h"
#include "CalendarTab.h"
#include "qevent.h"
#include "week.h"

class BoutonCreneau : public QPushButton
{
	Q_OBJECT

		
public:
	
	BoutonCreneau(Week* semaine, Creneau* c, QWidget* wdg, CalendarTab* tab, QPoint p);
	Tache* getTask();
	static QString getStyleBoutonHoraire(std::string text, QString c, QString border);
	static const QString DEFAULT_STYLE;
	static const QString PX_BORDURES;
	void setTache(Tache* t);
	Creneau* getCreneau();
	void setCreneau(Creneau*);
	Day* getJour();
	CalendarTab* getOnglet();
	unsigned int getX();
	unsigned int getY();

public slots:
	void mousePressEvent(QMouseEvent* e);
	void click();
	void clicDroit();
private:
	Creneau* creneau;
	CalendarTab* tab;
	Week* semaine;
	QPoint positionLayout;
	static QString numberOfPixel(unsigned int nbLettres);
	

signals:
	void rightClicked();
};
