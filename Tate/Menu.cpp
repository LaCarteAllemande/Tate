#include "Menu.h"
#include "TopWindow.h"


Menu::Menu(TopWindow* father)
{
    setParent(father);
    this->father = father;
	setStyleSheet(STYLE);
	lyt = new QHBoxLayout(this);
	lyt->setSpacing(0);
	lyt->setContentsMargins(0, 0, 0, 0);
    this->focusedBtn = nullptr;
}

void Menu::changeFocus(MenuBtn& btn)
{
    //we change the style only if the button with focus is not the same
    if (&btn != focusedBtn && focusedBtn != nullptr)
        this->focusedBtn->setFocus(false);
    this->focusedBtn = &btn;
}


void Menu::addMenuButton(Tab& tab, bool lastTab)
{
    buttons.append(new MenuBtn(*this, tab));
    lyt->addWidget(buttons.last()); //add the last button to the layout
    //lyt->addStretch(0);
    //we give focus to the first button of the menu
    if (buttons.count() == 1) {
        buttons.at(0)->setFocus(true);
        focusedBtn = buttons.at(0);
    }

    if (!lastTab) //we add spacing except for the last tab
        lyt->addStretch(1);
    

}

void Menu::addLogo()
{
    QPushButton* btn = new QPushButton(this);
    btn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    //btn->setStyleSheet("border: 0px; background-image: url("+ ICONS_PATH[0]+")");
    btn->setStyleSheet("border: 0px;background-color:red;padding:0x;margin:0px;");
    btn->setCursor(Qt::PointingHandCursor);

    QIcon icon(ICONS_PATH[0]);
    QSize size = btn->size();
    btn->setIcon(icon);
    btn->setIconSize(QSize(50,40));


    connect(btn, SIGNAL(clicked(bool)), this, SLOT(nietzsche()));
    lyt->addWidget(btn);
    lyt->addStretch(2);
    
}

void Menu::addIcons()
{
    lyt->addStretch(2);
    for (qsizetype i = 1; i < ICONS_PATH.count(); ++i) {
        QPushButton* btn = new QPushButton(this);
        btn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        btn->setStyleSheet("QPushButton:hover{background-color:" + BG_COLOR_ON_CLICK + " }");
        QIcon icon(ICONS_PATH[i]);
        btn->setIcon(icon);
        btn->setIconSize(QSize(20, 20)); 
        switch (i) {
        case 1:
            connect(btn, SIGNAL(clicked(bool)), this, SLOT(minimizeApp()));
            btn->setIconSize(QSize(30, 30));
            break;

        case 2:
            connect(btn, SIGNAL(clicked(bool)), this, SLOT(closeApp()));
            break;
        }
        lyt->addWidget(btn);
    }
}

void Menu::nietzsche()
{
    QString link = "https://en.wikipedia.org/wiki/Friedrich_Nietzsche";
    QDesktopServices::openUrl(QUrl(link));
}


void Menu::closeApp() {

    this->father->closeApp();
}



