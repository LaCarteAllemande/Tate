#pragma once
#include "Tab.h"
#include "tache.h"
#include <vector>
#include <qpushbutton.h>

#include <qlabel.h>
#include "Calendar.h"
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include <QPalette>
#include "objectif.h"
#include "labelObjectif.h"
#include <QListWidgetItem>
#include <json/json.h>

class btnObjectif;
class Tate;

class OngletObjectif : public Tab {
	Q_OBJECT

public:
	using Tab::Tab;
	OngletObjectif(QWidget* pere, Tate* application);
	void enlever(btnObjectif*);
	void deleteObjective(btnObjectif*);
	void afficher();
	QPushButton* btn;
	Tache* nouvelleTache(Objectif* o);
	void changementNomTache(QString);
	void supprimerTacheComboBox(QString);
	//void clicBoutonPlus();

private:
	QWidget* wdgObjectif;
	QGridLayout* lytObjectif;
	std::string file_Objectif = "./meta/objectifs.txt";

	
	std::vector<LabelObjectif*> labels;
	static const unsigned int NB_COLONNES = 4;
	void save();
	std::string nomsColonnes[50] = { "Objectif", "Description", "Date limite", "Jours restants"};
	//~OngletObjectif();
	std::vector<Objectif*> objectifs;
	void creationBtnPlus();
	void initObjectifs();
	~OngletObjectif();

private slots:
	void click();
	bool eventFilter(QObject* watched, QEvent* event);
};

