#pragma once

#include "qwidget.h"
#include <qlayout.h>


/*
Abstract class for representing a tab
*/

class Tate;

class Tab : public QWidget {
public:
	/**
	 * Show the tab and ask the application to hide the others tabs
	 *
	*/
	void showTab();
	
	QVBoxLayout* getLayout();
	Tate* getMainWindow();
	QString getName();
	void setName(QString);
	

protected:
	QVBoxLayout* layout;
	Tate* application;
	QString name;

	//constructeur protected pour que seules les enfants peuvent y accéder
	Tab(QWidget* pere, Tate* application);
	
};