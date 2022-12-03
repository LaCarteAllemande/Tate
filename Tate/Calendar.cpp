#include "Calendar.h"
#include "week.h"
#include "CalendarTab.h"

/*
Renvoi la date du premier jour de la semaine actuelle au format "dd/MM/yyyy"
*/
std::string Calendar::fistDayOfCurrentWeek()
{
    QDate date = QDate::currentDate(); // on obtient la date actuelle

    // on soustrait a la date le numéro du jour actuel dans la semaine pour obtenir la date du premier jour de la semaine actuelle
    date = date.addDays(1 - date.dayOfWeek());

    //on convertit au format approprié
    return date.toString("dd/MM/yyyy").toStdString();
}

/*
Constructeur d'un agenda, nécessite un widget père et son onglet agenda
*/
Calendar::Calendar(QWidget* pere, CalendarTab* o)
{
    this->setParent(pere);
    tab = o;

    //on crée la semaine actuelle et on l'ajoute à la liste de semaine
    Week* semaineActuelle = new Week(nullptr, fistDayOfCurrentWeek(), this);
    semaines.push_back(semaineActuelle);
}

/*
Supprime les références d'une tache des différentes semaines de l'agenda
*/
void Calendar::supprimerTache(Tache* t)
{
    for (size_t i = 0; i < semaines.size(); ++i)
    {
        semaines[i]->supprimerTache(t);
    }
}

/*
Ajoute une semaine à la liste de semaines
*/
void Calendar::ajouterSemaine(Week* s)
{
    /*Si la semaine n'a pas de semaine qui l'a précède ou qu'aucune semaine n'est enregistrée
    * on enregistre la semaine au début*/
    if (s->getPrecedente() == nullptr && semaines.size() > 0)
        semaines.insert(semaines.begin(), s);

    //sinon on ajoute la semaine à la suite
    else
        this->semaines.push_back(s);
}


Tache* Calendar::trouverTache(std::string nom)
{
    return tab->trouverTache(nom);
}

/*
Renvoi la semaine actuelle
Lève une exeption si aucune semaine ne correspond à la date actuelle 
*/
Week* Calendar::semaineActuelle()
{
    std::string premierJourDeLaSemaine = fistDayOfCurrentWeek();
    for (size_t i = 0; i < semaines.size(); ++i)
    {
        if (semaines[i]->getPremierJour() == premierJourDeLaSemaine)
            return semaines[i];
    }

    throw;
    return nullptr;
}

//a mettre dans semaine
std::string Calendar::dateSemainePrecedente(Week* semaine)
{
    char dateSemaine[51];
    int yy, month, dd;
    struct tm Tdate;
    std::string t = semaine->getPremierJour();
    const char* zStart = t.c_str();

    sscanf(zStart, "%d/%d/%d", &dd, &month, &yy);
    Tdate.tm_year = yy - 1900;
    Tdate.tm_mon = month - 1;
    Tdate.tm_mday = dd;
    Tdate.tm_hour = 0;
    Tdate.tm_min = 0;
    Tdate.tm_sec = 0;
    Tdate.tm_isdst = 0;
    time_t date = mktime(&Tdate);
    date = date - Week::SECONDES_PAR_JOUR * 7;

    std::strftime(dateSemaine, 50, "%d/%m/%Y", localtime(&date));
    return dateSemaine;
}

Week* Calendar::getSemaineSuivante(Week* semaine)
{
    auto it = std::find(semaines.begin(), semaines.end(), semaine);
    int index = it - semaines.begin();
    if (semaines.size()>index+1)
        return semaines[index+1];
    
    return nullptr;
}

std::string Calendar::getDateSemaineS(Week* semaine)
{
    char dateSemaine[51];
    int yy, month, dd;
    struct tm Tdate;
    std::string t = semaine->getPremierJour();
    const char* zStart = t.c_str();

    sscanf(zStart, "%d/%d/%d", &dd, &month, &yy);
    Tdate.tm_year = yy - 1900;
    Tdate.tm_mon = month - 1;
    Tdate.tm_mday = dd;
    Tdate.tm_hour = 0;
    Tdate.tm_min = 0;
    Tdate.tm_sec = 0;
    Tdate.tm_isdst = 0;
    time_t date = mktime(&Tdate);
    date = date + Week::SECONDES_PAR_JOUR * 7;

    std::strftime(dateSemaine, 50, "%d/%m/%Y", localtime(&date));
    return dateSemaine;
}

void Calendar::afficherSemaine(Week* s)
{
    s->afficher(this->parentWidget(), this->tab->getLayout(), tab);
}




