#pragma once

#include <string>
#include <vector>
#include "tache.h"
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qcombobox.h>

class Objectif {
private:
	std::string nom;
	std::string description;
	unsigned int joursRestants; //!!!! 
	std::string date;
	//unsigned int nbtaches;
	std::vector<Tache*> tasks;
	bool atteint;
	QComboBox* comboBox;
	
public:
	Objectif(std::string nom, std::string date, std::string description);
	std::string getName();
	std::string getDescription();
	unsigned int getJours();
	std::string getDate();
	unsigned int getNbTaches();
	void setAtteint();
	bool getEtat();
	void initComboBox(QComboBox*);
	void majComboBox();
	Tache* getTache(unsigned int index);
	void ajouterTache(Tache*);
	void enlever(Tache*);
	QString getActualTacheComboBox();
	void setNom(std::string);
	void setDescription(std::string);

};
