#pragma once

#include "qwidget.h"
#include "Tate.h"

class TopWindow : public QWidget
{
	Q_OBJECT
public:
	TopWindow(Tate& application);
	/***
	* Close the application
	*/
	void closeApp();

private:
	Tate* application;
};