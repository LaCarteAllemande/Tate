#pragma once
#include "Day.h"
#include "btnHeure.h"
#include "qwidget.h"
#include "qgridlayout.h"
#include "qmainwindow.h"
#include "CalendarTab.h"
#include "btnUpdate.h"
#include "btnChangementSemaine.h"

class BoutonCreneau;
class BtnHeure;

class Week
{
public:
    enum JourSemaine { Lundi = 0, Mardi = 1, Mercredi = 2, Jeudi = 3, Vendredi = 4, Samedi = 5, Dimanche = 6 };
    const static unsigned int JOURS_PAR_SEMAINE = 7;
    const static unsigned int SECONDES_PAR_JOUR = 86400;
    
    Week(Week*, std::string, Calendar*);
    ~Week();
    void majCreneaux();
    QString calculBorderCreneau(BoutonCreneau* btn);
    void definirJour(JourSemaine jour, Day* j);
    void supprimerTache(Tache* t);
    void afficher(QWidget* wdg, QLayout* lyt, CalendarTab* tab);
    void supprimerBtnCreneau(BoutonCreneau* btn, QGridLayout* lyt);
    Tache* trouverTache(std::string);
    std::string getPremierJour();
    Week* getPrecedente();
    void setPrecedente(Week*);
    void clearWeek();
    bool isVide();
    void reinitiliserCreneaux();
    unsigned int getHoraireMin();
    void ajouterHoraire(unsigned int);
    void supprimerHoraire(unsigned int h);
    void reafficher();
    unsigned int getHoraireMax();


private:
    Week* precedente;
    Calendar* a;
    std::string premierJour;
    Day* jours[JOURS_PAR_SEMAINE];
    std::vector<BoutonCreneau*> btnsCreaneau;
    std::vector<BtnHeure*> horaires;
    unsigned int horaireMin;
    unsigned int horaireMax;
    unsigned int calculHoraireMin();
    unsigned int calculHoraireMax();

    QGridLayout* lyt;
};

