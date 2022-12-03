#include "objectif.h"
#include "qdatetime.h"

#include <QtWidgets/qpushbutton.h>



Tache* Objectif::getTache(unsigned int index)
{
	return tasks[index];
}

void Objectif::ajouterTache(Tache* t)
{
	tasks.push_back(t);
	if (comboBox != nullptr)
		comboBox->addItem(QString::fromStdString(t->getName()));
}

void Objectif::enlever(Tache* t)
{
	tasks.erase(std::remove(tasks.begin(), tasks.end(), t), tasks.end());
	//comboBox->clear();
	//initComboBox(comboBox);
}

QString Objectif::getActualTacheComboBox()
{
	if (comboBox != nullptr)
		return comboBox->currentText();
	return nullptr;
}

void Objectif::setNom(std::string s)
{
	this->nom = s;
}

void Objectif::setDescription(std::string s)
{
	this->description = s;
}

Objectif::Objectif(std::string nom, std::string date, std::string description)
{
	this->nom = nom;
	this->date = date;
	this->description = description;
	this->atteint = false;
	this->comboBox = nullptr;
    int yy, month, dd;
	
    const char* zStart = date.c_str();

    sscanf(zStart, "%d/%d/%d", &dd, &month, &yy);
	QDate q(yy, month, dd);
	int t = QDate::currentDate().daysTo(q);
	if (t < 0)
		t = 0;

    this->joursRestants = t;

    //std::strftime(dateJour, 50, "%d.%m.%Y", localtime(&date));
	//this->joursRestants = QDate::currentDate().daysTo(d);
}

std::string Objectif::getName()
{
	return nom;
}

std::string Objectif::getDescription()
{
	return description;
}

unsigned int Objectif::getJours()
{
	return joursRestants;
}

std::string Objectif::getDate()
{
	return date;
}

unsigned int Objectif::getNbTaches()
{
	return tasks.size();
}

void Objectif::setAtteint()
{
	this->atteint = true;
}

bool Objectif::getEtat()
{
	return atteint;
}

void Objectif::initComboBox(QComboBox* list)
{
	this->comboBox = list;
	for (Tache* t : tasks)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(t->getName()));
		list->addItem(QString::fromStdString(t->getName()));
	} 
}

void Objectif::majComboBox()
{
	if (comboBox != nullptr)
	{
		int index = comboBox->currentIndex();
		comboBox->clear();
		initComboBox(comboBox);
		comboBox->setCurrentIndex(index);
	}
			
}
