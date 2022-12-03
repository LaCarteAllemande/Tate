#pragma once

#include <vector>
#include <fstream>
#include "qwidget.h"
#include "qgridlayout.h"

class Week;
class Tache;
class CalendarTab;

/*
Classe servant à centraliser toute les informations relatives à l'agenda
*/
class Calendar : public QWidget
{

    Q_OBJECT
private:
    std::vector<Week*> semaines;
    unsigned int nbSemaines;
    CalendarTab* tab;
    static std::string fistDayOfCurrentWeek();
    
public:
    Calendar(QWidget*,CalendarTab*);
    void supprimerTache(Tache* t);
    void ajouterSemaine(Week* s);
    Tache* trouverTache(std::string);
    Week* semaineActuelle();
    std::string dateSemainePrecedente(Week*);
    Week* getSemaineSuivante(Week*);
    std::string getDateSemaineS(Week*);
    void afficherSemaine(Week*);
    
};

