#pragma once

#include "Tab.h"
#include "tache.h"
#include <vector>
#include <qpushbutton.h>

#include <qlabel.h>
#include "Calendar.h"
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include <QPalette>
#include <QtWidgets>




/*
Onglet permettant de representer l'agenda
Cet onglet est composé d'un widget "agenda" representant l'agenda et d'un widget 'taches" qui permet à l'utilisateur d'interagir avec ses taches
*/
class BtnTache;
class Calendar;
class Week;
class Day;

class Tate;
class DayBtn;


class CalendarTab : public Tab {
	Q_OBJECT

public:
	CalendarTab(QWidget* pere, Tate* application);
	void setTacheSelectionnee(Tache* t);
	Tache* getTacheSelectionnee();
	void updateTaskButtons();
	Calendar* getAgenda();
	void updateTaskWidget();
	void deleteTask(BtnTache* btn);
	QGridLayout* getLayoutAgenda();
	Tache* trouverTache(std::string);
	void changementSemaine(QString s);
	void clearActualWeek();
	void newTaskButton(Tache* t);
	void changementNomTache(Tache* t);
	QColor askColorToUser(std::string);
	void showSidePanel(Day* jour);

	
	/**
	 * Set the day to his button
	 * @param The day to set
	 * @param The number of the day in the week (0-6)
	 */
	void setDayToDayBtn(Day* day, size_t index);


public slots:
	void clicBoutonPlus();

private : 
	//members

	const int MAX_BTN_TACHES_PAR_LIGNE = 7;
	const int LIGNE_MAX = 4;
	Tache* tacheSelectionnee; //tache actuelle selectionnée par l'utilisateur à travers les boutons taches
	//coordonnées du prochain emplacement dans le widget tache
	unsigned short colonneWdgTaches; 
	unsigned short ligneWdgTaches;
	Calendar* agenda;
	Week* semaineAffichee;
	std::vector<BtnTache*> boutonsTache; //réfrences de tous les boutons taches
	QWidget* wdgTaches;
	std::vector<QLayout*> layouts;
	QGridLayout* lytTaches;

	QFrame* wdgAgenda;
	
	QGridLayout* lytWdgAgenda;
	QPushButton* boutonPlus;
	//mettre la constante jour par semaine dans cette classe
	DayBtn* dayBtns[7] ; //Array of the buttons used to display the date of a day
	

	void creationBoutonsTache(QWidget* wdg);
	void addBtnToTaskWidget(QPushButton* btn);
	
	void afficherTaches();


	QPushButton* createBtnPlus(QWidget* wdg);

};
