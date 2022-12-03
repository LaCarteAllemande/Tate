#include "btnObjectif.h"
#include <qmenu.h>
#include "ongletObjectif.h"
#include <QCheckBox>

QString btnObjectif::getStyleBtnObjectif()
{
	return "btnObjectif {background-color: white;font-size:18px;border:1px solid black; padding: 10px 20px;}"
                            "btnObjectif:hover{background-color:grey}"
        "btnObjectif::menu-indicator{ width:0px; };";
}

Objectif* btnObjectif::getObjectif()
{
    return o;
}


btnObjectif::btnObjectif(Objectif* o, QWidget* wdg, OngletObjectif* tab)
{
    this->o = o;
    this->tab = tab;
    this->nomO = QString::fromStdString(o->getName());
    this->descriptionO = QString::fromStdString(o->getDescription());
    setText(nomO);
    setParent(wdg);
    setStyleSheet(getStyleBtnObjectif());
    setCursor(Qt::PointingHandCursor);
    connect(this, SIGNAL(clicked(bool)), this, SLOT(click()));
}

void btnObjectif::click()
{
    /*
    QObject* sender = this->sender();
    btnObjectif* btn = qobject_cast<btnObjectif*>(sender); */
    QMenu menu(this);

    menu.setCursor(Qt::PointingHandCursor);
    QAction* objectif = new QAction("Modifier objectif", &menu);
    QAction* tasks = new QAction("Modifier taches associes", &menu);
    QAction* supprimer = new QAction("Supprimer objectif", &menu);
    menu.addAction(objectif);
    menu.addAction(tasks);
    menu.addAction(supprimer);
    connect(objectif, SIGNAL(triggered()), this, SLOT(modifierObjectif()));
    connect(tasks, SIGNAL(triggered()), this, SLOT(tasks()));
    connect(supprimer, SIGNAL(triggered()), this, SLOT(supprimer()));


    int menuWidth = menu.sizeHint().width();
    int x = this->width() - menuWidth;
    int y = this->height();

    QPoint pos(this->mapToGlobal(QPoint(x, y)));
    menu.popup(pos);
    //QString::fromStdString(std::to_string(btn->height()))
    //menu->setStyleSheet("QMenu::item { width:"+ QString::fromStdString(std::to_string(btn->width() -10 ))+" px; margin: 0px; }  }");
    this->setMenu(&menu);
    this->setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);
    menu.exec();
}

void btnObjectif::modifierObjectif()
{

    QDialog dialog(this);
    //dialog.setAttribute(Qt::WA_DeleteOnClose);
    this->dialog = &dialog;
    QGridLayout lyt(&dialog);

    //obliger de mettre ces deux objets sur la heap car on n'en a besoin après cette fonction afin de récupérer les entrées utilisateurs
    QLineEdit nom(QString::fromStdString(this->o->getName()), &dialog);
    QLineEdit description(QString::fromStdString(this->o->getDescription()), &dialog);
    connect(&nom, SIGNAL(textChanged(QString)), this, SLOT(nameChanged(QString)));
    connect(&description, SIGNAL(textChanged(QString)), this, SLOT(desChanged(QString)));


    QCheckBox checkbox("Objectif atteint", &dialog);
    connect(&checkbox, SIGNAL(clicked()), this, SLOT(checkBoxClick()));
    QLabel label("Nom de l'objectif", &dialog);
    QLabel label2("Description de l'objectif", &dialog);
    QPushButton btn("Sauvegarder", &dialog);

    connect(&btn, SIGNAL(clicked()), this, SLOT(valider()));
    lyt.addWidget(&label, 0,0);
    lyt.addWidget(&nom, 0, 1);
    lyt.addWidget(&label2, 1, 0);
    lyt.addWidget(&description, 1, 1);
    lyt.addWidget(&checkbox, 2, 0);
    lyt.addWidget(&btn, 2, 1);

    dialog.exec();
    
}

void btnObjectif::tasks()
{
    dialog = new QDialog(this);
    QComboBox comboBox(dialog);
    o->initComboBox(&comboBox);
    QGridLayout lyt(dialog);
    
    QPushButton btn1("Ajouter tache", dialog);
    connect(&btn1, SIGNAL(clicked()), this, SLOT(ajouterTache()));
    QPushButton btn2("Modifier tache", dialog);
    connect(&btn2, SIGNAL(clicked()), this, SLOT(modifierTache()));
    QPushButton btn3("Supprimer tache", dialog);
    connect(&btn3, SIGNAL(clicked()), this, SLOT(supprimerTache()));
    lyt.addWidget(&comboBox, 1, 1, 1,3);
    lyt.addWidget(&btn1, 2, 1);
    lyt.addWidget(&btn2, 2, 2);
    lyt.addWidget(&btn3, 2, 3); 
    dialog->exec();

}

void btnObjectif::supprimer()
{
    tab->deleteObjective(this);
    //this->deleteLater();
    tab->afficher();

}

void btnObjectif::ajouterTache()
{
    Tache*t = tab->nouvelleTache(o);
    if (t !=  nullptr)
        o->ajouterTache(t);

}

void btnObjectif::modifierTache()
{
    QString s = o->getActualTacheComboBox();
    this->tab->changementNomTache(s);
    o->majComboBox();
}

void btnObjectif::supprimerTache()
{
    tab->supprimerTacheComboBox(o->getActualTacheComboBox());
    o->majComboBox();
}

void btnObjectif::checkBoxClick()
{
    atteint = !atteint;
}

void btnObjectif::valider()
{

    o->setNom(nomO.toStdString());
    o->setDescription(descriptionO.toStdString());
    dialog->close();
    dialog->deleteLater();
    if (atteint)
        this->o->setAtteint();
    tab->afficher();
}

void btnObjectif::nameChanged(QString s)
{
    nomO = s;
}

void btnObjectif::desChanged(QString s)
{
    descriptionO = s;
}
