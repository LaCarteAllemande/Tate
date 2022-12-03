#pragma once

#pragma once

#include "qevent.h"
#include "qpushbutton.h"
#include "qwidget.h"
#include "objectif.h"


class OngletObjectif;

class btnObjectif : public QPushButton
{
	Q_OBJECT

public:
	btnObjectif(Objectif* o, QWidget* wdg, OngletObjectif*);
	static QString getStyleBtnObjectif();
	Objectif* getObjectif();

public slots:
	//void mousePressEvent(QMouseEvent* e);
	//void clicDroit();
	void click();
	void modifierObjectif();
	void tasks();
	void supprimer();
	void ajouterTache();
	void modifierTache();
	void supprimerTache();
	void checkBoxClick();
	void valider();
	void nameChanged(QString);
	void desChanged(QString);
private:
	Objectif* o;
	OngletObjectif* tab;
	bool atteint = false;

	QString nomO;
	QString descriptionO;
	QDialog* dialog;


signals:
	void rightClicked();
};

