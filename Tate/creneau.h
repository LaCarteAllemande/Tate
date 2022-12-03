#ifndef HEURE_H
#define HEURE_H

#include <string>
#include "tache.h"
#include "Day.h"

class Creneau
{
private:
    Tache* tache;
    unsigned int heureDebut;
    Day* j;

public:
    Creneau(Tache* t,unsigned int debut,  Day* j);
    Tache* getTask();
    void setTache(Tache* t);
    Day* getJour();
    unsigned int getDebut();
    void supprimerTache();
};

#endif // HEURE_H
