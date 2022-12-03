#include <fstream>

#include "Tate.h"
#include "CalendarTab.h"
#include "ongletObjectif.h"
#include "TopWindow.h"



Tate::Tate(QApplication& parent)
{

	//initializing the application's UI
	topWindow = new TopWindow(*this);
	this->menu = new Menu(this->topWindow);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	
	//initializing the main layout
	mainLayout = new QVBoxLayout(this);
	mainLayout->setSpacing(0); //set no space between the main components
	mainLayout->setContentsMargins(0, 0, 0, 0); //set no space around the main components
	mainLayout->addWidget(menu, 0); //adding the menu
	topWindow->setLayout(mainLayout); //setting the main layout


	//initializing the application's data
	this->parent = &parent;
	setStatusBar(nullptr);
	setWindowTitle(NAME);
	initializeTasks();
	setWindowIcon(QIcon("./icons/logo.jpg"));
	setStyleSheet("display:none;"); //see blank zones
	setCentralWidget(topWindow);


	//TO IMPROVE

	// layouts et widgets de l'onglet agenda
	ongletAgenda = new CalendarTab(topWindow, this);
	tabs.append(ongletAgenda);
	lytOnglets.append(tabs[0]->getLayout());
	mainLayout->addWidget(tabs[0], 8);

	focusedTab = tabs.at(0);



	// layouts et widgets de l'onglet objectif
	tabs.append(new OngletObjectif(topWindow, this));
	lytOnglets.append(tabs[1]->getLayout());
	tabs[1]->setVisible(false);
	mainLayout->addWidget(tabs[1], 8);
	


	initializeMenu();
	tabs[0]->setVisible(true);

	

}



Tate::~Tate()
{
	delete tabs[0];
	delete tabs[1];

	sauvegarde();
	for (QList<Tache*>::iterator i = tasks.begin(); i != tasks.end(); i++)
	{
		delete (*i);
		tasks.removeFirst();

	}

	//delete ui; reste du transfert de VS19

}


Tache* Tate::getTask(size_t index)
{
	assert(index < tasks.size());
	if (index < tasks.size())
		return tasks[index];
	return nullptr; //in case index is not valid
}

/*
Permet � l'utilisateur de changer le nom d'une tache pass�e en param�tre*/
void Tate::changementNomTache(Tache* tache)
{
	//boite de dialogue
	QString text = QInputDialog::getText(this, tr("Nouveau nom de la tache"),
		tr("Nom de la tache"), QLineEdit::Normal);


	//si l'utilisateur a bien rentr� un nom
	if (!text.isEmpty())
	{
		//on v�rifie que la tache n'existe pas d�j�
		if (!isTacheExistante(text.toStdString()))
		{
			tache->setNom(text.toStdString());
			ongletAgenda->updateTaskButtons();
		}

		//message d'erreur
		else {
			QMessageBox msgBox;
			msgBox.setText("Une tache poss�de d�j� ce nom");
			msgBox.exec();
		}
	}
}

/*
Supprime une tache du logiciel et son bouton associ�*/
void Tate::supprimerTache(Tache* t)
{
	//Supprime les r�frences de la tache de l'agenda
	ongletAgenda->getAgenda()->supprimerTache(t);
	if (t->getObjetif() != nullptr)
		t->getObjetif()->enlever(t); //enl�ve la tache de son objectif

	//supprime la r�f�rence de la liste des taches
	tasks.erase(std::remove(tasks.begin(), tasks.end(), t), tasks.end());
	//rend la m�moire
	delete t;
	//supprime le bouton tache associ�es
	ongletAgenda->updateTaskWidget();
}


void Tate::ajouterTache(Tache* t)
{
	tasks.push_back(t);
	sauvegarde();
}

Tache* Tate::trouverTache(std::string nom)
{
	for (Tache* t : tasks) {
		if (t->getName().compare(nom) == 0)
			return t;
	}

	return nullptr;
}

/*Permet à l'utilisateur de créer une nouvelle tache.
- Le Widget passé en paramètre sert à créer la boite de dialogue
- l'objectif passé en paramètre sera attribuer à la tache
 Renvoi la tache ou nullptr si la tache existe déjà
  */
Tache* Tate::nouvelleTache(QWidget* wdg, Objectif* o)
{

	//entr�e de l'utilisateur
	QString text = QInputDialog::getText(wdg, tr("Nouvelle tache"),
		tr("Nom de la tache"), QLineEdit::Normal);

	//on v�rifie que l'entr�e n'est pas vide
	if (!text.isEmpty())
	{
		//on v�rifie que la tache n'existe pas d�j�
		if (!isTacheExistante(text.toStdString()))
		{
			//on cr�e une nouvelle tache correspondate � l'entr�e de l'utilisateur et on l'ajoute � la liste de taches
			Tache* t = new Tache(text.toStdString(), generateColor(), o);
			ajouterTache(t);

			// on cr�e un bouton correzspondant � cette nouvelle tache dans l'onglet agenda
			ongletAgenda->newTaskButton(t);
			return t;
		}

		// dans le cas où la tache existe déjà
		else
		{
			QMessageBox msgBox;
			msgBox.setText("Tache d�j� cr�e.");
			msgBox.exec();
		}

	}

	return nullptr;
}

/*
Renvoi true si le string passé en param�tre correspond au nom d'une tache*/
bool Tate::isTacheExistante(std::string nomTache)
{
	for (size_t i = 0; i < tasks.size(); ++i)
	{
		if (tasks[i]->getName() == nomTache)
			return true;
	}

	return false;
}


std::string Tate::generateColor()
{
	

	std::string s = "";
	for (unsigned int i = 0; i < 6; i++)
	{
		s += HEX[rand() % 16];
	}
	return s;
}

QColor Tate::askColorToUser(std::string hex)
{
	//if the color passed in argument is null
	if (hex == "")
		hex = "0000000"; //give it the default black color

	QColor c;
	//put the hex code into rgb
	unsigned int r, g, b;
	sscanf(hex.c_str(), "%02x%02x%02x", &r, &g, &b);
	c.setRgb(r, g, b);
	//ask the user a color
	c = QColorDialog::getColor(c, this, "Chosse a color");
	return c;
}

size_t Tate::getNbTasks()
{
	return tasks.size();
}

void Tate::changeFocus(Tab& tab)
{

	this->focusedTab->setVisible(false);
	this->focusedTab = &tab;
}

void Tate::quit()
{
	this->parent->quit();
}

void Tate::initializeTasks()
{
	std::string ligne;
	int nbLignes = 0;
	std::string nom;
	std::string couleur;
	std::ifstream in(file_taches); // the in flag is optional
	while (std::getline(in, ligne)) {
		if (nbLignes == 0)
		{
			nom = ligne;
			++nbLignes;
		}

		else if (nbLignes == 1)
		{
			couleur = ligne;
			Tache* t = new Tache(nom, couleur, nullptr);
			tasks.append(t);
			nom = "";
			couleur = "";
			nbLignes = 0;
		}
	}

}

void Tate::initializeMenu()
{

	menu->addLogo();
	
	int i = 0;
	for (Tab* tab : tabs) {

		tab->setName(TABS_NAME[i].toUpper());
		menu->addMenuButton(*tabs.at(i), tab == tabs.last());
		++i;
	}
	menu->addIcons();

	
}

void Tate::sauvegarde()
{
	std::ofstream out(file_taches);

	for (size_t i = 0; i < tasks.size(); ++i)
	{
		out << tasks[i]->getName() <<std::endl << tasks[i]->getCouleur() << std::endl;

	}

	out.close();

}

