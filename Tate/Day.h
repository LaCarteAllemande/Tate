#pragma once

#include <list>
#include <ctime>
#include <string>
#include <vector>
#include "tache.h"
#include "DailyTask.h"

class Week;
class Creneau;

class Day
{
   private :
        std::string date;
        std::vector<Creneau*> creneaux;
        Week* s;
        QList<DailyTask*> dailyTasks;

    public:
        Day(std::string date, Week*);
        void supprimerTache(Tache* t);
        void supprimerCreneau(Creneau* c);

        /**
         * Returns the number of daily tasks
         * @return Number of daily tasks
         */
        qsizetype nbDailyTasks();

        /**
         * Returns the daily task at the given index
         * @param The index of the task
         * @return The daily task, or nullptr if invalid index
         */
        DailyTask* getDailyTask(qsizetype index);

        /**
         * Returns a daily task with that name
         * @param The name of the task
         * @return The daily task, or nullptr if invalid name
         */
        DailyTask* getDailyTask(QString NAME);


        /**
         * Add a daily task to the day if that task does not already exists
         * @param The name of the new task
         */
        void addDailyTask(QString task);

        /**
         * Returns true if the day has a daily task that has the same name as the one passed as param
         * @param The name to check
         * @return Yes or no
         */
        bool dailyTaskExists(QString NAME);

        /**
         * Delete a daily task 
         * @param The name of the task to delete
         */
        void deleteDailyTask(QString NAME);
    
        void setVide();
        void supprimerCreneau(unsigned int h);
        int getNbCreneaux();
        //Creneau* getCreneau(int i);
        Creneau* getCreneauHoraire(unsigned int horaire);
        std::string getDate();
        void enregistrer();
        void ajouterCreneau(Creneau*, unsigned int);
        bool isVide();
        unsigned int getHoraireMin();
        unsigned int getHoraireMax();
        const static unsigned int DEFAULT_MIN = 8;
        const static unsigned int DEFAULT_MAX = 22;
};

