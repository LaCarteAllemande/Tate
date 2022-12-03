#include "CalendarTab.h"
#include "btnTache.h"
#include "week.h"
#include "Tate.h"
#include "DayBtn.h"
#include "DailyTaskWindow.h"




CalendarTab::CalendarTab(QWidget* father, Tate* application)
	: Tab(father, application)
{
	
	//initilisation des valeurs � 0
	this->tacheSelectionnee = nullptr;
	colonneWdgTaches=0;
	ligneWdgTaches=0;

	this->name = "Overview";

	//widget contenant l'agenda
	wdgAgenda = new QFrame(this);
	wdgAgenda->setObjectName("WidgetAgenda");
	wdgAgenda->setStyleSheet("QWidget#WidgetAgenda {background-color: white; margin:0px; padding:0px; border: 3px solid; border-left:none}");
	//son layout
	lytWdgAgenda = new QGridLayout(wdgAgenda);
	lytWdgAgenda->setSpacing(0);
	lytWdgAgenda->setContentsMargins(10, 0, 10, 10);

	//widget pour int�ragir avec les taches
	wdgTaches = new QWidget(this);
	wdgTaches->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	//layout principal auquel on ajoute les widgets
	layout = new QVBoxLayout(this);
	layout->addWidget(wdgAgenda, 8);
	layout->addWidget(wdgTaches, 2);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);

	//pas ouf de devoir passer l'onglet
	agenda = new Calendar(wdgAgenda, this);

	//boutons permettant de changer de semaine
	btnChangementSemaine* btnSemainePrecedente = new btnChangementSemaine(this);
	btnChangementSemaine* btnSemaineSuivante = new btnChangementSemaine(this);
	lytWdgAgenda->addWidget(btnSemainePrecedente, 0, 0, 1, 1);
	lytWdgAgenda->addWidget(btnSemaineSuivante, 0, 1, 1, 1);

	//bouton � fonction indetermin�
	btnUpdate* btnU = new btnUpdate(father, this);
	lytWdgAgenda->addWidget(btnU, 1, 0, 1, 2);

	for (int i = 1; i <= Week::JOURS_PAR_SEMAINE; ++i)
	{
		DayBtn* btn = new DayBtn(this);
		dayBtns[i-1] = btn;
		btn->setStyleSheet("background-color: white;font-size:16px;font-weight:bold; border:0px");
		btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
		lytWdgAgenda->addWidget(btn, 0, i + 1, 2, 1);
	}

	semaineAffichee = agenda->semaineActuelle();

	semaineAffichee->afficher(wdgAgenda, lytWdgAgenda, this);

	afficherTaches();
}

void CalendarTab::creationBoutonsTache(QWidget* wdg)
{
	for (size_t i = 0; i < application->getNbTasks(); i++)
	{
		BtnTache* b = new BtnTache(application->getTask(i), wdg, this);
		boutonsTache.push_back(b);
	}
}

Tache* CalendarTab::trouverTache(std::string nom)
{
	return this->getMainWindow()->trouverTache(nom);
}

/*
Change de semaine affich�e � partir du symbole pass� en param�tre
*/
void CalendarTab::changementSemaine(QString s)
{
	//on enl�ve la semaine actuelle de l'interface graphique 
	semaineAffichee->clearWeek(); 

	if (s == "<")
	{
		// Si une semaine pr�c�dente existe, on l'affiche 
		if (semaineAffichee->getPrecedente() != nullptr)
		{
			semaineAffichee = semaineAffichee->getPrecedente();
		}

		// dans le cas ou la semaine pr�c�dente est inexistante
		else
		{
			// on cr�e une nouvelle semaine correspondante � la semaine pr�cedente � la semaine affich�e
			Week* nouvelleSemaine = new Week(nullptr, agenda->dateSemainePrecedente(semaineAffichee), agenda);
			semaineAffichee->setPrecedente(nouvelleSemaine);
			semaineAffichee = nouvelleSemaine;

			//on ajoute la nouvelle semaine
			agenda->ajouterSemaine(nouvelleSemaine);
		}
	}

	else if (s == ">")
	{
		// Si une semaine suivante existe, on l'affiche 
		if (agenda->getSemaineSuivante(semaineAffichee) != nullptr)
		{
			semaineAffichee = agenda->getSemaineSuivante(semaineAffichee);
		}

		// dans le cas ou la semaine suivante est inexistante
		else
		{
			semaineAffichee = new Week(semaineAffichee, agenda->getDateSemaineS(semaineAffichee), agenda);

			//on ajoute la nouvelle semaine
			agenda->ajouterSemaine(semaineAffichee);
		}
	}


	semaineAffichee->afficher(wdgAgenda, lytWdgAgenda, this);
}

/*
Reinitialise les creneaux de la semaine affich�e*/
void CalendarTab::clearActualWeek()
{
	semaineAffichee->reinitiliserCreneaux();
}
void CalendarTab::afficherTaches() {


	wdgTaches->setStyleSheet("margin:0px; background-color: white;");
	QLabel* labelTache = new QLabel("Taches", wdgTaches);

	labelTache->setStyleSheet("font-size:20px; font-weight:bold;  margin:0px;");
	labelTache->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	QWidget* q = new QWidget(wdgTaches);
	lytTaches = new QGridLayout(q);

	QVBoxLayout* lytPage = new QVBoxLayout(wdgTaches);

	lytPage->addWidget(labelTache, 2);
	lytPage->addWidget(q, 8);
	lytPage->setContentsMargins(10, 0, 0, 0);
	lytPage->setSpacing(0);
	wdgTaches->setLayout(lytPage);
	creationBoutonsTache(wdgTaches);
	for (size_t i = 0; i < application->getNbTasks(); i++)
	{
		addBtnToTaskWidget(boutonsTache[i]);
	}

	createBtnPlus(wdgTaches);
	addBtnToTaskWidget(boutonPlus);
	wdgTaches->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	//lyt->setSpacing(0);
	lytTaches->setContentsMargins(10, 10, 10, 10);
	//lyt->setAlignment(Qt::Alignement )

}


/*
Passe en param la derni�re tache s�lectionn�e par l'utilisateur
*/
void CalendarTab::setTacheSelectionnee(Tache* t)
{
	tacheSelectionnee = t;
}

/*
Renvoi la derni�re tache s�lectionn�e par l'utilisateur
*/
Tache* CalendarTab::getTacheSelectionnee()
{
	return tacheSelectionnee;
}

/*
Ajoute un bouton pass� en param au widget tache
*/
void CalendarTab::addBtnToTaskWidget(QPushButton* btn)
{
	assert(boutonsTache.size() < MAX_BTN_TACHES_PAR_LIGNE * LIGNE_MAX);

	//v�rifie si une ligne de boutons est pleine (nombre de boutons total divisible par nombre de boutons max par ligne et nombre de boutons total diff�rent de 0)
	if (lytTaches->count() % MAX_BTN_TACHES_PAR_LIGNE == 0 && lytTaches->count() != 0)
	{
		// on incr�mente la ligne et met la colonne � 0
		ligneWdgTaches += 1;
		colonneWdgTaches = 0;
	}

	lytTaches->addWidget(btn, ligneWdgTaches, colonneWdgTaches);
	colonneWdgTaches += 1; // on incr�mente la colonne
}

/*Comportement au clic du bouton "+" dans le wiget taches servant � ajouter des taches
*/
void CalendarTab::clicBoutonPlus() {

	//On v�rifie si le nombre de taches a �t� atteint
	if (lytTaches->count() == MAX_BTN_TACHES_PAR_LIGNE * LIGNE_MAX)
	{
		QMessageBox msgBox;
		msgBox.setText("Nombre maximum de taches atteintes.");
		msgBox.exec();
	}

	else
	{	
		//on demande � la MainWindow de cr�e une nouvelle tache
		application->nouvelleTache(this, nullptr);
	}
}

/*
Cr�e un nouveau bouton tache dans le widget taches*/
void CalendarTab::newTaskButton(Tache* t)
{
	BtnTache* nouveauBouton = new BtnTache(t, wdgTaches, this);
	boutonsTache.push_back(nouveauBouton);

	//on supprime le bouton "+" du widget taches

	QWidget* parent = boutonPlus->parentWidget();
	lytTaches->removeWidget(boutonPlus);
	boutonPlus->deleteLater();
	boutonPlus->setVisible(false);
	colonneWdgTaches = colonneWdgTaches - 1;

	//on ajoute le nouveauBouton
	addBtnToTaskWidget(nouveauBouton);

	//on recr�e un bouton "+" et on l'ajoute au widget taches
	createBtnPlus(parent);
	addBtnToTaskWidget(boutonPlus);
}

QPushButton* CalendarTab::createBtnPlus(QWidget* wdg)
{
	boutonPlus = new QPushButton("+", wdg);
	boutonPlus->setStyleSheet("background-color: white; font-size:16px; font-weight:bold; border:1px solid black;"); //padding:0px 10px 5px;
	boutonPlus->setCursor(Qt::PointingHandCursor);
	boutonPlus->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	connect(boutonPlus, SIGNAL(clicked(bool)), this, SLOT(clicBoutonPlus()));
	//lytTaches->addWidget(boutonPlus, 1, taches.size());

	return nullptr;
}

/*
Met � jour le styleshet et le textes des boutons taches*/
void CalendarTab::updateTaskButtons()
{
	bool borderOrNot=false;
	for (BtnTache* btn : boutonsTache)
	{
		Tache* tache = btn->getTask();
		//si la taches est la tache selectionn�, on veut ajouter une bordure autoyr du bouton
		if (tache == tacheSelectionnee)
		{
			borderOrNot = true;
		}

		btn->setStyleSheet(BtnTache::generateStyle(borderOrNot, tache->getCouleur()));
		btn->setText(QString::fromStdString(tache->getName()));
		borderOrNot = false;
	}
	semaineAffichee->majCreneaux();
}

Calendar* CalendarTab::getAgenda()
{
	return agenda;
}

/*
Met � jour le widget tache en supprimant tous les boutons taches et en les recr�ant 
Pas du tout optimis� mais seul moyen de supprimer des �l�ments du widget � ce jour*/
void CalendarTab::updateTaskWidget()
{
	//vide le layout taches
	QLayoutItem* child;
	while ((child = lytTaches->takeAt(0)) != nullptr) {
		child->widget()->deleteLater(); // delete the widget
		delete child;   // delete the layout item
	}

	//supprime les r�f�rences des boutons taches
	boutonsTache.clear(); 
	//r�initialise les variables de placement
	colonneWdgTaches = 0;
	ligneWdgTaches = 0;

	//creation d'un bouton tache pour chaque tache et ajout de celle-ci au widget 
	for (size_t i = 0; i < application->getNbTasks(); ++i)
	{
		boutonsTache.push_back(new BtnTache(application->getTask(i), wdgTaches, this));
		addBtnToTaskWidget(boutonsTache[i]);
	}
	
	createBtnPlus(wdgTaches);
	addBtnToTaskWidget(boutonPlus);

	semaineAffichee->majCreneaux();
}

/*
Supprime une tache ainsi que son bouton correspondant pass� en param�tre*/
void CalendarTab::deleteTask(BtnTache* btn)
{
	Tache* t = btn->getTask();
	application->supprimerTache(t);
}

QGridLayout* CalendarTab::getLayoutAgenda()
{
	return lytWdgAgenda;
}

/*
Permet de changer le nom d'une tache pass�e en param�tre*/
void CalendarTab::changementNomTache(Tache* tache)
{
	application->changementNomTache(tache);
}

/*
Demande � la mainwindow de cr�er une boite de dialogue pour demander une couleur
- La couleur actuelle de l'�l�ment dans le cas o� il faut changer une couleur, sinon null*/
QColor CalendarTab::askColorToUser(std::string hex)
{
	return this->application->askColorToUser(hex);
}

void CalendarTab::setDayToDayBtn(Day* day, size_t numberOfDay) {
	this->dayBtns[numberOfDay]->setDay(day);
}



void CalendarTab::showSidePanel(Day* day)
{

	DailyTaskWindow topWindow(this, day);
	topWindow.exec();

}
