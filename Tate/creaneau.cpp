#include "creneau.h"

Creneau::Creneau(Tache* t, unsigned int d, Day* j)
{
    this->tache = t;
    this->heureDebut=d;
    this->j = j;
}

Tache* Creneau::getTask()
{
    return tache;
}

void Creneau::setTache(Tache* t)
{
    tache = t;
}

Day* Creneau::getJour()
{
    return j;
}

unsigned int Creneau::getDebut()
{
    return heureDebut;
}
/*
Supprime la référence vers la tache du creneau
La mémoire est liberé par la main window
*/
void Creneau::supprimerTache()
{
    this->tache = nullptr;
}
