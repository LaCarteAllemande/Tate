#include "btnTache.h"
/*
Bouton servant � interagir et � representer les taches dans le widget taches de l'onglet agenda
 - Tache du bouton
 - Widget et onglet n�cessaire
*/
BtnTache::BtnTache(Tache* t, QWidget* wdg, CalendarTab* tab)
{
	this->setParent(wdg);
	this->setText(QString::fromStdString(t->getName()));
	this->tache = t;
	this->ongletAgenda = tab;
	this->setCursor(Qt::PointingHandCursor);
	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	this->setStyleSheet(generateStyle(false, t->getCouleur()));
	connect(this, SIGNAL(clicked(bool)), this, SLOT(click()));
	connect(this, SIGNAL(rightClicked()), this, SLOT(clicDroit()));
}

/*
Renvoi la tache associ�e au bouton*/
Tache* BtnTache::getTask()
{
	return this->tache;
}

/*
Gestionnaire d'�v�nement (permet de g�rer les clic gauche et droit)
*/
void BtnTache::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton)
		emit clicked(); 
	else if (e->button() == Qt::RightButton)
		emit rightClicked();
}

/*
G�n�re le stylesheet pour un bouton
- Si le bouton n�cessite une bordure (d�pend de s'il a �t� cliqu�)
- La couleur de la tache du bouton
*/
QString BtnTache::generateStyle(bool borderOrNot, std::string c)
{
	QString border;
	if (borderOrNot)
		border = "1px solid black";
	else
		border = "1px solid white ; border-style: hidden";

	return "BtnTache{font-size:16px; border:" + border + "; background-color: #" + QString::fromStdString(c) + "; padding : 3px 5px;} BtnTache::menu-indicator{ width:0px; };";
}

/*
Comportement au clic droit*/
void BtnTache::clicDroit()
{
	QObject* sender = this->sender();
	BtnTache* btnTache = qobject_cast<BtnTache*>(sender);

	//creation d'un menu d�roulant
	QMenu menu(btnTache);
	menu.setStyleSheet("QMenu{background-color:#"+ QString::fromStdString(btnTache->getTask()->getCouleur()) + ";}");
	menu.setCursor(Qt::PointingHandCursor);

	//diff�rents options du menu d�roulant
	QAction* nom = new QAction("Renommer", &menu);
	QAction* couleur = new QAction("Changer couleur", &menu);
	QAction* supprimer = new QAction("Supprimer tache", &menu);
	menu.addAction(nom);
	menu.addAction(couleur);
	menu.addAction(supprimer);
	connect(couleur, SIGNAL(triggered()), this, SLOT(changementCouleur()));
	connect(supprimer, SIGNAL(triggered()), this, SLOT(supprimer()));
	connect(nom, SIGNAL(triggered()), this, SLOT(changementNom()));

	//gestions de la taille et du positionnement du menu
	int menuWidth = menu.sizeHint().width();
	int x = btnTache->width() - menuWidth;
	int y = btnTache->height();
	QPoint pos(btnTache->mapToGlobal(QPoint(x, y)));
	menu.popup(pos); 


	btnTache->setMenu(&menu);
	btnTache->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
	menu.exec();
}

/*
Comportement au clic*/
void BtnTache::click()
{
	//on ajoute une bordure a ce bouton 
	QObject* sender = this->sender();
	BtnTache* btnTache = qobject_cast<BtnTache*>(sender);

	//on change la tache selectionn�e
	ongletAgenda->setTacheSelectionnee(btnTache->getTask());
	ongletAgenda->updateTaskButtons();
}

/*
Permet � l'utilisateur de changer la couleur de la tache*/
void BtnTache::changementCouleur()
{
	QColor c = ongletAgenda->askColorToUser(this->getTask()->getCouleur());

	//si la couleur est diff�rente de noir (afin d�viter que la couleur soit noir apr�s que l'utilisateur a annul� la boite de dialogue)
	if (!(c.red() ==0 && c.green() == 0 && c.blue() == 0))
	{
		std::string s = c.name().toStdString().erase(0, 1);
		this->getTask()->setCouleur(s);
		ongletAgenda->updateTaskButtons();
	}
}

/*
Permet � l'utilisateur de changer le nom de la tache*/
void BtnTache::changementNom()
{
	ongletAgenda->changementNomTache(this->getTask());
}

/*
Supprime le bouton et sa tache associ�e*/
void BtnTache::supprimer()
{
	ongletAgenda->deleteTask(this);
}

