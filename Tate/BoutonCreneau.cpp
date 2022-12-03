#include "BoutonCreneau.h"


const QString BoutonCreneau::DEFAULT_STYLE = "background-color: Lightgrey; margin:0px;";
const QString BoutonCreneau::PX_BORDURES = "1px";


BoutonCreneau::BoutonCreneau(Week* semaine, Creneau* c, QWidget* wdg, CalendarTab* tab, QPoint p)
{
	creneau = c;
	this->semaine = semaine;
	this->tab = tab;
	this->setParent(wdg);
	this->positionLayout = p;
	Tache* t = creneau->getTask();
	if (t != nullptr)
		this->setText(QString::fromStdString(t->getName()));
	else
		this->setText("");

	connect(this, SIGNAL(clicked(bool)), this, SLOT(click()));
	connect(this, SIGNAL(rightClicked()), this, SLOT(clicDroit()));
	this->setCursor(Qt::PointingHandCursor);
	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

}

Day* BoutonCreneau::getJour()
{
	return this->creneau->getJour();
}

unsigned int BoutonCreneau::getX()
{
	return positionLayout.x();
}

unsigned int BoutonCreneau::getY()
{
	return positionLayout.y();
}

void BoutonCreneau::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton)
		emit clicked();
	else if (e->button() == Qt::RightButton)
		emit rightClicked();
}
QString BoutonCreneau::numberOfPixel(unsigned int nbLettres)
{
	//switch
	if (nbLettres == 0)
		return "0";
	else if (nbLettres > 5 && nbLettres < 10)
		return "17";

	else if (nbLettres > 10 && nbLettres < 20)
		return "16";

	else if (nbLettres > 20)
		return "15";

	else if (nbLettres > 25)
		return "14";

	return "18";
}

/*
* Fonction appellée en cas de clic gauche sur le bouton
*/
void BoutonCreneau::click()
{
	//on récupère l'envoyeur de l'évènement et on le convertit en bouton
	QObject* sender = this->sender();
	BoutonCreneau* btn = qobject_cast<BoutonCreneau*>(sender);

	//on récupère la tache sélectionnée qui correpsond à la nouvelle tache du bouton
	Tache* tacheSelectionnee = tab->getTacheSelectionnee();
	
	//si la tache sléctionnée n'est pas vide
	if (tacheSelectionnee != nullptr)
	{
		//on met à jour le bouton
		creneau->setTache(tacheSelectionnee);
		btn->setText(QString::fromStdString(tacheSelectionnee->getName()));
		btn->setStyleSheet(getStyleBoutonHoraire(tacheSelectionnee->getName(), QString::fromStdString(tacheSelectionnee->getCouleur()), this->semaine->calculBorderCreneau(this)));

		//on enregistre un changement dans les creneaux du jour
		this->getJour()->enregistrer();
		semaine->majCreneaux();
	}
}

/*
* Fonction appellée en cas de clic droit sur le bouton
*/
void BoutonCreneau::clicDroit()
{
	//on réinitialise le bouton
	this->creneau->setTache(nullptr);
	this->getJour()->enregistrer();
	semaine->majCreneaux();
}
Creneau* BoutonCreneau::getCreneau()
{
	return creneau;
}
Tache* BoutonCreneau::getTask()
{
	return creneau->getTask();
}

QString BoutonCreneau::getStyleBoutonHoraire(std::string text, QString couleur, QString border)
{
	size_t nbLettres = text.length();
	QString generateStyle = "background-color: #" + couleur + "; margin:0px;font-size:" + numberOfPixel(nbLettres) + "px; padding:0px 5px; " + border;
	return generateStyle;
}

void BoutonCreneau::setTache(Tache* t)
{
	this->creneau->setTache(t);
}

void BoutonCreneau::setCreneau(Creneau* c)
{
	creneau = c;
}

