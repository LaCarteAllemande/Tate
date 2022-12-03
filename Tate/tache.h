#pragma once

#include "qwidget.h"
#include "qgridlayout.h"
#include <string>
#include <fstream>

class Objectif;

class Tache
{
private:
    std::string nom;
    std::string couleur;
    Objectif* objectif;
public:
    Tache(std::string nom, std::string couleur, Objectif* o);
    ~Tache();
    std::string getName();
    void setNom(std::string s);
    void setCouleur(std::string c);
    std::string getCouleur();
    Objectif* getObjetif();
    void setObjectif(Objectif*);
};


