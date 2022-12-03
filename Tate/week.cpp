#include "week.h"
#include <assert.h>
#include "CalendarTab.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "BoutonCreneau.h"
#include "btnHeure.h"
#include "DayBtn.h"



Week::Week(Week* s, std::string datePremierJour, Calendar* a)
{

	precedente = s;
	premierJour = datePremierJour;
	this->a = a;
	QDate date = QDate::fromString(QString::fromStdString(datePremierJour), "dd/MM/yyyy");

    // on soustrait au nombre de jours de la date le numéro du jour actuel dans la semaine pour obtenir la date du premier jour de la semaine actuelle


	for (unsigned int i = 0; i < JOURS_PAR_SEMAINE; ++i)
	{
		jours[i] = new Day(date.addDays(i).toString("dd.MM.yyyy").toStdString(), this);
	}

	horaireMin = calculHoraireMin();
	horaireMax = calculHoraireMax();

}

Week::~Week()
{
	for (size_t i = 0; i < JOURS_PAR_SEMAINE; ++i)
	{
		jours[i]->enregistrer();
		delete jours[i];
	}
}

unsigned int Week::calculHoraireMin()
{

	int horaireMin = jours[0]->getHoraireMin();
	for (int i = 1; i < JOURS_PAR_SEMAINE; ++i)
	{
		if (jours[i]->getNbCreneaux() > 0)
		{
			if (jours[i]->getHoraireMin() < horaireMin)
				horaireMin = jours[i]->getHoraireMin();
		}
	}

	return horaireMin;
}
unsigned int Week::calculHoraireMax()
{
	int horaireMax = jours[0]->getHoraireMax();
	for (int i = 1; i < JOURS_PAR_SEMAINE; ++i)
	{
		if (jours[i]->getNbCreneaux() > 0)
		{
			if (jours[i]->getHoraireMax() > horaireMax)
				horaireMax = jours[i]->getHoraireMax();
		}
	}

	return horaireMax;
}

Tache* Week::trouverTache(std::string nom)
{
	return a->trouverTache(nom);
}

std::string Week::getPremierJour()
{
	return premierJour;
}

Week* Week::getPrecedente()
{
	return precedente;
}

void Week::setPrecedente(Week* s)
{
	this->precedente = s;
}

/*
Destroy all the graphic components of the weeks of the GUI
*/
void Week::clearWeek()
{
	for (BoutonCreneau* btn : btnsCreaneau)
	{
		delete btn;
	}

	btnsCreaneau.clear();

	for (BtnHeure* l : horaires)
	{
		delete l;
	}

	horaires.clear();
}

bool Week::isVide()
{
	for (int i = 0; i < JOURS_PAR_SEMAINE; ++i)
	{
		if (!jours[i]->isVide())
			return false;
	}
	return true;
}

/*
Reinitialise les creneaux de la semaine*/
void Week::reinitiliserCreneaux()
{
	//Met les boutons creneaux de la semaine à null 
	for (BoutonCreneau* btn : btnsCreaneau)
	{
		btn->setTache(nullptr);
	}

	//Met les creneaux des jours de la semaine à null et les enregistre
	for (size_t i = 0; i < JOURS_PAR_SEMAINE; ++i)
	{
		jours[i]->setVide();
		jours[i]->enregistrer();
	}
		

	majCreneaux();
}

unsigned int Week::getHoraireMin()
{
	return horaireMin;
}

void Week::ajouterHoraire(unsigned int h)
{
	if (h == horaireMin && h >= 0)
	{
		horaireMin = horaireMin - 1;
		for (Day* j : jours)
		{
			Creneau* c = new Creneau(nullptr, h - 1, j);
			j->ajouterCreneau(c, h - 1);
		}
	}

	else if (h == horaireMax && h <= 24)
	{
		horaireMax = horaireMax + 1;
		for (Day* j : jours)
		{
			Creneau* c = new Creneau(nullptr, h + 1, j);
			j->ajouterCreneau(c, h + 1);
		}
	}
}

void Week::supprimerHoraire(unsigned int h)
{
	if (jours[0]->getNbCreneaux() > 5)
	{

		if (h == horaireMin)
		{
			horaireMin = horaireMin + 1;
			for (Day* j : jours)
			{
				j->supprimerCreneau(1 - 1);
			}
		}

		else if (h == horaireMax && h <= 24)
		{
			horaireMax = horaireMax - 1;
			for (Day* j : jours)
			{
				j->supprimerCreneau(j->getNbCreneaux() - 1);
			}
		}
	}
}

void Week::reafficher()
{
	this->clearWeek();
	a->afficherSemaine(this);
}

unsigned int Week::getHoraireMax()
{
	return horaireMax;
}


void Week::afficher(QWidget* pere, QLayout* lytAgenda, CalendarTab* tab)
{

	for (size_t i = 0; i < JOURS_PAR_SEMAINE; ++i)
		tab->setDayToDayBtn(this->jours[i], i);
	this->lyt = qobject_cast<QGridLayout*>(lytAgenda);
	for (int i = 0; i <= horaireMax - horaireMin; i++)
	{
		BtnHeure* l = new BtnHeure(i + horaireMin, this, pere, tab);

		horaires.push_back(l);
		this->lyt->addWidget(l, i + 2, 0, 1, 2);
	}
	for (int i = 1; i <= JOURS_PAR_SEMAINE; ++i)
	{
		QLayoutItem* item = this->lyt->itemAtPosition(0, i + 1);
		DayBtn* btn = qobject_cast<DayBtn*>(item->widget());
		btn->setText(QString::fromStdString(jours[i - 1]->getDate().substr(0, 5)));
	}

	for (int i = 1; i <= JOURS_PAR_SEMAINE; ++i)
	{

		for (int j = horaireMin; j <= horaireMax; j++)
		{


			Creneau* c;
			if (jours[i - 1]->getCreneauHoraire(j) == nullptr)
			{
				// creneau temporaire qui ne sera pas enregistré
				c = new Creneau(nullptr, j, jours[i - 1]);
				jours[i - 1]->ajouterCreneau(c, j);
			}

			else
			{
				c = jours[i - 1]->getCreneauHoraire(j);
			}
			BoutonCreneau* b = new BoutonCreneau(this, c, pere, tab, QPoint(j - horaireMin + 2, i + 1));
			btnsCreaneau.push_back(b);
			b->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
			if (b->getTask() == nullptr)
				b->setStyleSheet(BoutonCreneau::DEFAULT_STYLE); //inutile

			else
			{
				//b->setStyleSheet(BoutonCreneau::getStyleBoutonHoraire(QString::fromStdString(b->getTache()->getCouleur()), calculBorderCreneau(b->getType())));
				b->setText(QString::fromStdString(b->getTask()->getName()));

			}
			this->lyt->addWidget(b, (j - horaireMin) + 2, i + 1); // i +1 a cause des boutons de changements de semaines
		}
	}
	majCreneaux();
}

void Week::supprimerBtnCreneau(BoutonCreneau* btn, QGridLayout* lyt)
{
	lyt->removeWidget(btn);//removes and then it causes some zigzag drawing at (0,0)
	btn->setVisible(false);//asks to redraw the component internally
	btnsCreaneau.erase(std::remove(btnsCreaneau.begin(), btnsCreaneau.end(), btn), btnsCreaneau.end());
	this->majCreneaux();
}

void Week::majCreneaux()
{
	int nbCreneauxLies = 1;

	for (int i = 0; i < btnsCreaneau.size(); ++i)
	{
		Tache* t = btnsCreaneau[i]->getTask();
		if (t != nullptr)
		{
			if (i != 0 && t == btnsCreaneau[i - 1]->getTask() && btnsCreaneau[i - 1]->getJour() == btnsCreaneau[i]->getJour())
			{
				nbCreneauxLies = nbCreneauxLies + 1;

				for (int c = (i - nbCreneauxLies) + 1; c <= i; ++c)
				{
					btnsCreaneau[c]->setText("");
					btnsCreaneau[c]->setStyleSheet(BoutonCreneau::getStyleBoutonHoraire(t->getName(), QString::fromStdString(t->getCouleur()), calculBorderCreneau(btnsCreaneau[c])));
				}

				btnsCreaneau[i - 1]->setStyleSheet(BoutonCreneau::getStyleBoutonHoraire(t->getName(), QString::fromStdString(t->getCouleur()), calculBorderCreneau(btnsCreaneau[i - 1])));
				btnsCreaneau[i - nbCreneauxLies / 2]->setText(QString::fromStdString(t->getName()));

				btnsCreaneau[i]->setStyleSheet(BoutonCreneau::getStyleBoutonHoraire(t->getName(), QString::fromStdString(t->getCouleur()), calculBorderCreneau(btnsCreaneau[i])));
				//btnsCreaneau[i]->getCreneau()->getJour()->supprimerCreneau(btnsCreaneau[i]->getCreneau());

			}
			else
			{
				nbCreneauxLies = 1;
				btnsCreaneau[i]->setText(QString::fromStdString(t->getName()));
				btnsCreaneau[i]->setStyleSheet(BoutonCreneau::getStyleBoutonHoraire(btnsCreaneau[i]->text().toStdString(), QString::fromStdString(t->getCouleur()), calculBorderCreneau(btnsCreaneau[i])));

			}
		}

		else
		{
			nbCreneauxLies = 1;
			btnsCreaneau[i]->setText("");
			btnsCreaneau[i]->setStyleSheet(BoutonCreneau::DEFAULT_STYLE + calculBorderCreneau(btnsCreaneau[i]));
		}
	}

}

QString Week::calculBorderCreneau(BoutonCreneau* btn)
{
	QString bordures[4] = { "0px", "0px", "0px", "0px" };
	bordures[2] = BoutonCreneau::PX_BORDURES;
	// ligne - colonne
	unsigned int x = btn->getX(), y = btn->getY();
	unsigned int nbCreneaux = this->horaireMax - this->horaireMin;

	if (x - 1 < 2) //dépasse de l'agenda par en haut 
	{
		bordures[0] = BoutonCreneau::PX_BORDURES;
	}

	else
	{
		QLayoutItem* item = lyt->itemAtPosition(x - 1, y);
		if (item != nullptr)
		{
			BoutonCreneau* voisin = qobject_cast<BoutonCreneau*>(item->widget());
			if (voisin->getTask() != btn->getTask() || voisin->getTask() == nullptr)
				bordures[0] = BoutonCreneau::PX_BORDURES;
		}
	}

	if (x + 1 > nbCreneaux + 2) //dépasse de l'agenda par en bas 
	{
		bordures[3] = BoutonCreneau::PX_BORDURES;
	}

	if (y == JOURS_PAR_SEMAINE + 1)
	{
		bordures[1] = BoutonCreneau::PX_BORDURES;
	}

	return "border-style: solid; border-color: black; border-width:" + bordures[0] + " " + bordures[1] + " " + bordures[3] + " " + bordures[2] + ";";

}

void Week::definirJour(JourSemaine i, Day* j)
{
	this->jours[i] = j;
}

/*
Supprime les réfrences d'une tache de la semaine
*/
void Week::supprimerTache(Tache* t)
{
	//on supprime la tache dans chaque jour
	for (size_t i = 0; i < JOURS_PAR_SEMAINE; ++i)
	{
		jours[i]->supprimerTache(t);
	}

	//on efface la tache des boutons correspondant
	for (size_t i = 0; i < btnsCreaneau.size(); ++i)
	{
		if (t == btnsCreaneau[i]->getTask())
		{
			btnsCreaneau[i]->setTache(nullptr);
		}
	}
}

