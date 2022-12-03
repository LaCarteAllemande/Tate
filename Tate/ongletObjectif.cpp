#include "ongletObjectif.h"
#include "Tate.h"

#include <qformlayout.h>
#include <qdialogbuttonbox.h>
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QCalendarWidget>
#include "btnObjectif.h"
#include <qcombobox.h>
#include <qlistwidget.h>
//#include <jsoncpp/json/json.h>

static const std::string JSON_FILE = "./data/objectives.json"; 


OngletObjectif::OngletObjectif(QWidget* pere, Tate* application)
    : Tab(pere, application)
{
    
    initObjectifs();
    wdgObjectif = new QFrame(this);
    wdgObjectif->setObjectName("WidgetAgenda");
    //wdgObjectif->setStyleSheet("QWidget#WidgetAgenda {background-color: white; margin:0px; padding:0px; border: 3px solid; border-left:none}");

    lytObjectif = new QGridLayout(this);
    lytObjectif->setContentsMargins(0, 0, 0, 0);
    lytObjectif->setSpacing(0);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    afficher();
}


void OngletObjectif::deleteObjective(btnObjectif* o)
{

    int nbTaches = o->getObjectif()->getNbTaches();
    for (int i = 0; i < nbTaches; ++i)
    {
        application->supprimerTache(o->getObjectif()->getTache(0));
    }
    objectifs.erase(std::remove(objectifs.begin(), objectifs.end(), o->getObjectif()), objectifs.end());
    delete o->getObjectif();
    this->save();
}

void OngletObjectif::afficher()
{

    QLayoutItem* child;
    while ((child = lytObjectif->takeAt(0)) != nullptr) {
        child->widget()->deleteLater(); // delete the widget
        delete child;   // delete the layout item
    }

    for (int i = 0; i < NB_COLONNES; ++i)
    {
        QLabel* l = new QLabel(QString::fromStdString(nomsColonnes[i]), wdgObjectif);
        l->setAlignment(Qt::AlignCenter);
        l->setStyleSheet("background-color: white;font-size:20px;font-weight:bold;border:1px solid black;margin left:3px; padding: 10px 20px;");
        lytObjectif->addWidget(l, 0, i);
    }
    int i = 1;

    for (Objectif* o : objectifs)
    {
        //lytObjectif->addWidget(new LabelObjectif(o->getNom(), wdgObjectif), i, 0);
        if (o->getEtat() == false)
        {
            btnObjectif* btn = new btnObjectif(o, wdgObjectif, this);
            lytObjectif->addWidget(btn, i, 0);

            labels.push_back(new LabelObjectif(o->getDescription(), wdgObjectif));
            lytObjectif->addWidget(labels.back(), i, 1);

            labels.push_back(new LabelObjectif(o->getDate(), wdgObjectif));
            lytObjectif->addWidget(labels.back(), i, 2);

            labels.push_back(new LabelObjectif(std::to_string(o->getJours()), wdgObjectif));
            lytObjectif->addWidget(labels.back(), i, 3);

            i = i + 1;
        }

    }

    //lytObjectif->addWidget(new QSpacerItem(1, 1));



    creationBtnPlus();
    lytObjectif->setRowStretch(lytObjectif->rowCount(), 1);
}

Tache* OngletObjectif::nouvelleTache(Objectif* o)
{
    return application->nouvelleTache(this, o);
}

void OngletObjectif::changementNomTache(QString s)
{
    Tache* t = application->trouverTache(s.toStdString());
    if (t!= nullptr)
        application->changementNomTache(t);

}

void OngletObjectif::supprimerTacheComboBox(QString s)
{
    application->supprimerTache(application->trouverTache(s.toStdString()));
}

void OngletObjectif::save()
{
    std::ofstream out(file_Objectif);

    size_t nbObjectives = objectifs.size();

    //In the case in which there are no objectives
    if (objectifs.size() == 0)
    {
        out << "";
        out.close();
        return;
    }

    for (size_t i = 0; i < nbObjectives; ++i)
    {
        out << objectifs[i]->getName() << std::endl;
        out << objectifs[i]->getDate() << std::endl;
        out << objectifs[i]->getDescription() << std::endl;
        out << std::to_string(objectifs[i]->getNbTaches()) << std::endl;
        for (size_t t = 0; t < objectifs[i]->getNbTaches(); ++t)
        {
            out << objectifs[i]->getTache(t)->getName() << std::endl;
        }
    }
    out.close();


    std::ofstream file(JSON_FILE, std::ifstream::binary);

    Json::StyledWriter writer();
    Json::Value data;
    Json::Value objectives;

    data["name"] = "test";
    objectives.append(data);

    file.close();

}

void OngletObjectif::creationBtnPlus()
{
    QPushButton* btnPlus = new QPushButton("+", wdgObjectif);
    connect(btnPlus, SIGNAL(clicked(bool)), this, SLOT(click()));
    lytObjectif->addWidget(btnPlus, objectifs.size()+1, 0);
}

void OngletObjectif::initObjectifs()
{
    std::string ligne;
    int nbLignes =0, nbTaches=0;
    
    std::ifstream in(file_Objectif); // the in flag is optional

    std::string nom,description, date;
    int nbJours;

    while (std::getline(in, ligne)) {

        if (nbLignes == 0)
        {
            nom = ligne;
            nbLignes++;

        }

        else if (nbLignes == 1)
        {
            date = ligne;
            nbLignes++;
        }

        else if (nbLignes == 2)
        {
            description = ligne;
            Objectif* o= new Objectif(nom,date , description);
            objectifs.push_back(o);
            nbLignes++;

        }
        else if (nbLignes == 3)
        {
            nbTaches = stoi(ligne);
            for (int i = 0; i < nbTaches; ++i)
            {
                std::getline(in, ligne);
                Tache* t = application->trouverTache(ligne);
                if (t != nullptr)
                {
                    objectifs.back()->ajouterTache(t);
                    t->setObjectif(objectifs.back());
                }
                    
            }
            nbLignes = 0;

        }

        description = "";
        
        
    }

    in.close();
}

OngletObjectif::~OngletObjectif()
{
    for (Objectif* o : objectifs)
    {
        delete o;
    }
}

void OngletObjectif::click()
{
    QDialog dialog(this);

    // Use a layout allowing to have a label next to each field

    QString nom, description;
    QFormLayout* formLayout = new QFormLayout(&dialog);
    //dialog.setLayout()

    QDateTimeEdit* dateEdit = new QDateTimeEdit(QDate::currentDate()); 
    dateEdit->setCalendarPopup(true);
    QCalendarWidget* calendar = new QCalendarWidget(&dialog);
    dateEdit->setCalendarWidget(calendar);

    QLineEdit lineNom(&dialog);
    QLineEdit lineDescription(&dialog);

    formLayout->addRow("Objectif:", &lineNom);
    formLayout->addRow("Description:", &lineDescription);
    formLayout->addRow("Date limite:", dateEdit);


    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    formLayout->addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        nom = lineNom.text();
        description = lineDescription.text();
        if (nom =="" || description=="")
        {
            QMessageBox msgBox;
            msgBox.setText("Entree incomplete");
            msgBox.exec();
        }

        else
        {
            QDate d = dateEdit->date();
            
            Objectif* o = new Objectif(nom.toStdString(), d.toString("dd/MM/yyyy").toStdString(), description.toStdString());
            objectifs.push_back(o);
            save();
            afficher();
        }
    }
}

bool  OngletObjectif::eventFilter(QObject* watched, QEvent* event)
{
    if ((watched == btn) && (event->type() == QEvent::HoverEnter))
    {
        qDebug() << "Button is hovered !";
    }

    return false;
}


