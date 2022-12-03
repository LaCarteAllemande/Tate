#include "TopWindow.h"

TopWindow::TopWindow(Tate& application)
{
	this->application = &application;
}

void TopWindow::closeApp()
{
	this->application->quit();
}
