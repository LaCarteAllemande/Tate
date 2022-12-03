#pragma once

#include <QMainWindow>
#include "ui_Tate.h"
#include "qboxlayout.h"
#include "qpushbutton.h"
#include "qframe.h"
#include "qobjectdefs.h"
#include <qlabel.h>


#include "btnTache.h"
#include "tache.h"
#include "Calendar.h"
#include "Menu.h"



/*
The application
Could be static
*/

class TopWindow;
class Tate : public QMainWindow
{
    Q_OBJECT

public:
    Tate(QApplication& parent);
    ~Tate();
    /**
     * Get a task specified by its index
     *
     * @param The index of the task
     * @return A reference to the task or nullptr if index is invalid
    */
    Tache* getTask(size_t);
    void changementNomTache(Tache* t);
    void supprimerTache(Tache*);
    void ajouterTache(Tache*);
    Tache* trouverTache(std::string);
    Tache* nouvelleTache(QWidget*, Objectif*);
    bool isTacheExistante(std::string s);
    std::string generateColor();

    /**
     * Allow a user to pick a color and returns it
     *
     * @param Color the user wish to change (or "" if none)
     * @return The color choose by the user
    */
    QColor askColorToUser(std::string hex);

    /**
     * Number of tasks in the program
     *
     * @return The number of tasks
    */
    size_t getNbTasks();

    /**
     * Change the focused tab
     *
     * @return The number of tasks
    */
    void changeFocus(Tab&);

    /**
     * Close the application
     *
    */
    void quit();

private:
    //ui components
    Ui::DeepWorkClass ui;
    QVBoxLayout* mainLayout;
    TopWindow* topWindow; //Top level widget that contains all the widget of the application
    Menu* wdgMenu;
    QList<Tab*> tabs;
    QList<QLayout*> lytOnglets;
    CalendarTab* ongletAgenda;
    Menu* menu;
    QApplication* parent;

    Tab* focusedTab; //the actual tab that ahs focus



    //application attributs
 
    const QString NAME = "Tate"; //name of the application
    const QList<QString> TABS_NAME = { "Overview", "Objectives" };
    
    const std::string HEX = "0123456789ABCDEF";//all the values that can be used to build an hexadecimal number
    const std::string file_taches = "./meta/taches.txt";
    QList<Tache*> tasks;


    void sauvegarde();
    /**
     * Initialize the array of tasks 
    */
    void initializeTasks();

    /**
     * Initialize the menu
    */
    void initializeMenu();
};
