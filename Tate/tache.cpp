#include "tache.h"
#include "qlabel.h"
#include "objectif.h"


Tache::Tache(std::string nom, std::string c, Objectif* o)
{
	this->nom = nom;
	this->objectif = o;
	couleur = c;
}
Tache::~Tache()
{

}
void Tache::setCouleur(std::string c)
{
	couleur = c;
}

std::string Tache::getCouleur()
{
	return couleur;
}

Objectif* Tache::getObjetif()
{
	return objectif;
}

void Tache::setObjectif(Objectif* o)
{
	this->objectif = o;
}

std::string Tache::getName()
{
	return nom;
}

void Tache::setNom(std::string s)
{
	this->nom = s;
}

