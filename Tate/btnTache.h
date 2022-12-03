#pragma once

#include "qevent.h"
#include "qpushbutton.h"
#include "qwidget.h"
#include "tache.h"

#include "CalendarTab.h"
#include "qmenu.h"
#include <qcolordialog.h>
#include <QInputDialog>

class CalendarTab;
class BtnTache: public QPushButton
{
	Q_OBJECT

public:
	BtnTache(Tache* t, QWidget* wdg, CalendarTab* tab);
	Tache* getTask();
	static QString generateStyle(bool border, std::string c);
	
private slots:
	void mousePressEvent(QMouseEvent* e);
	void clicDroit();
	void click();
	void changementCouleur();
	void changementNom();
	void supprimer();
private:
	Tache* tache;
	CalendarTab* ongletAgenda;
		
signals:
	void rightClicked(); 
};
