#include "Tab.h"
#include "Tate.h"

Tab::Tab(QWidget* father, Tate* application)
	: QWidget(father)
{
	this->application = application;
	this->layout = nullptr;
}

void Tab::showTab()
{
	this->application->changeFocus(*this);
	this->setVisible(true);
}

QVBoxLayout* Tab::getLayout()
{
	return layout;
}

Tate* Tab::getMainWindow()
{
	return this->application;
}

QString Tab::getName()
{
	return this->name;
}

void Tab::setName(QString name)
{
	this->name = name;
}


