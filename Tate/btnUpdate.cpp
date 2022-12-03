#include "btnUpdate.h"
#include "CalendarTab.h"


btnUpdate::btnUpdate(QWidget* wdg, CalendarTab* tab) {
	this->tab = tab;
	this->setParent(wdg);
	this->setText("Clear");
	this->setCursor(Qt::PointingHandCursor);
	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	this->setStyleSheet(STYLE);
	connect(this, SIGNAL(clicked(bool)), this, SLOT(click()));
}

/*
Comportement au clic, on informe l'onglet de supprimer tous les creneaux de la semaine affichée*/
void btnUpdate::click()
{
	QMessageBox msgBox;
	msgBox.setText("Etes vous sur de vouloir reinitialiser cette semaine ?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	int ret = msgBox.exec();

	if (ret == QMessageBox::Yes)
		tab->clearActualWeek();
}
