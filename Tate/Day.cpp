#include "Day.h"
#include "creneau.h"
#include "week.h"

int Day::getNbCreneaux()
{
	return creneaux.size();
}

Creneau* Day::getCreneauHoraire(unsigned int horaire)
{
	for (int i = 0; i < creneaux.size(); ++i)
	{
		if (creneaux[i]->getDebut() == horaire)
			return creneaux[i];
	}
	return nullptr;
}

std::string Day::getDate()
{
	return this->date;
}

void Day::enregistrer()
{

	if (!isVide())
	{
		std::ofstream out("./meta/jours/" + date + ".txt");
		std::string nomTache;
		std::string done = "ND";

		for (size_t i = 0; i < creneaux.size(); i++)
		{
			if (creneaux[i]->getTask() != nullptr)
			{
				nomTache = creneaux[i]->getTask()->getName();

				out << creneaux[i]->getDebut() << " " << nomTache << std::endl;
				nomTache = "";
			}
		}

		for (qsizetype i = 0; i < this->dailyTasks.count(); ++i) {
			if (this->dailyTasks.at(i)->isDone())
				done = "D";
			out << done << " "<< this->dailyTasks.at(i)->getName().toStdString() << std::endl;
		}
		out.close();
	}

	else {
		std::string s = "./meta/jours/" + date + ".txt";
		const char* file = s.c_str();
		remove(file);
	}
		

}

void Day::ajouterCreneau(Creneau* c , unsigned int i)
{
	for (Creneau* creneau : creneaux)
	{
		if (creneau->getDebut() > i)
		{
			auto it = find(creneaux.begin(), creneaux.end(), creneau);
			creneaux.insert(it, c);
			return;
		}
	}

	creneaux.insert(creneaux.end(), c);
	
	
}

bool Day::isVide()
{
	if (this->dailyTasks.count() > 0)
		return false;
	for (Creneau* c : creneaux)
	{
		if (c->getTask() != nullptr)
			return false;
	}
	return true;
}

Day::Day(std::string date, Week* s)
{
	this->date = date;
	this->s = s;


	std::ifstream in("./meta/jours/"+date+".txt");

	std::string ligne;
	std::string heureDebut, nom;
	while (std::getline(in, ligne)) {
			size_t pos = ligne.find(" ");
			heureDebut = ligne.substr(0, pos);
			nom = ligne.substr(pos + 1, ligne.size());
			if (heureDebut == "D" || heureDebut == "ND") //in case it is a daily task
			{
				bool done = false;
				if (heureDebut == "D")
					done = true;

				this->dailyTasks.append(new DailyTask(QString::fromStdString(nom), done));
			}

			else {
				
				Tache* tache = s->trouverTache(nom); 
				Creneau* c = new Creneau(tache, stoi(heureDebut), this);
				creneaux.push_back(c);
			}

			heureDebut = "";
			nom = "";
	}
}

unsigned int Day::getHoraireMin()
{
	if (creneaux.size() > 0)
		return creneaux[0]->getDebut();
	else
		return DEFAULT_MIN;

}

unsigned int Day::getHoraireMax()
{
	if (creneaux.size() > 0)
		return creneaux[creneaux.size() - 1]->getDebut();
	else
		return DEFAULT_MAX;
}

/*
Supprime la référence de la tache pour chaque créneau du jour qui correspond à cette tache
*/
void Day::supprimerTache(Tache* t)
{
	for (Creneau* creneau : creneaux)
	{
		if (creneau->getTask() == t)
			creneau->supprimerTache();
	}
}

void Day::supprimerCreneau(Creneau* c)

{
	creneaux.erase(std::remove(creneaux.begin(), creneaux.end(), c), creneaux.end());
}

qsizetype Day::nbDailyTasks()
{
	return this->dailyTasks.size();
}

DailyTask* Day::getDailyTask(qsizetype index)
{
	return this->dailyTasks.at(index);
}

DailyTask* Day::getDailyTask(QString NAME)
{
	for (DailyTask* task : this->dailyTasks)
		if (task->getName() == NAME)
			return task;
	return nullptr;
}

void Day::addDailyTask(QString taskName)
{
	this->dailyTasks.append(new DailyTask(taskName, false));
}

/*
Met tous les creneaux du jour à null*/
void Day::setVide()
{
	for (Creneau* c : creneaux)
	{
		c->setTache(nullptr);
	}
	
}

void Day::supprimerCreneau(unsigned int i)
{
	creneaux.erase(creneaux.begin()+i);
}

bool Day::dailyTaskExists(QString NAME)
{
	for (DailyTask* task : this->dailyTasks)
		if (task->getName() == NAME)
			return true;
	return false;
}

void Day::deleteDailyTask(QString NAME) {
	this->dailyTasks.takeAt(dailyTasks.indexOf(this->getDailyTask(NAME)));
}


