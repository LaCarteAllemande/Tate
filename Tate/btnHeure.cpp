#include "btnHeure.h"
#include "CalendarTab.h"

BtnHeure::BtnHeure(unsigned int h, Week* semaine, QWidget* wdg, CalendarTab* tab)
{
    this->heure = h;
    this->semaine = semaine;
	this->tab = tab;
    setText(QString::number(h)+ "h ");
    setParent(wdg);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setStyleSheet("background-color: white;font-size:16px;font-weight:bold; border-style:none;");
    if (h == semaine->getHoraireMin() || h == semaine->getHoraireMax())
    {
        boutonAjout();
    }
}

void BtnHeure::boutonAjout()
{
    this->setCursor(Qt::PointingHandCursor);
    connect(this, SIGNAL(clicked(bool)), this, SLOT(click()));
    connect(this, SIGNAL(rightClicked()), this, SLOT(clicDroit()));
}
void BtnHeure::click()
{
	QObject* sender = this->sender();
	BtnHeure* btnheure = qobject_cast<BtnHeure*>(sender);
	if (btnheure->getHeure() > 0 && btnheure->getHeure() < 24)
	{
		semaine->ajouterHoraire(btnheure->getHeure());
		tab->changementSemaine("");
	}

	//semaine->reafficher();
}

unsigned int BtnHeure::getHeure()
{
	return this->heure;
}

void BtnHeure::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
        emit clicked();
    else if (e->button() == Qt::RightButton)
        emit rightClicked();
}

void BtnHeure::clicDroit()
{

	QObject* sender = this->sender();
	BtnHeure* btnheure = qobject_cast<BtnHeure*>(sender);
	semaine->supprimerHoraire(btnheure->getHeure());
	tab->changementSemaine("");
}

