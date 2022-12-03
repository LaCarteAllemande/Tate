

#include "MenuBtn.h"
#include "menu.h"
#include "Tab.h"


MenuBtn::MenuBtn(Menu& menu, Tab& tab)
{
    this->setParent(&menu);
    this->menu = &menu;
    this->tab = &tab;
    this->focus = false;
    this->setText(tab.getName());
    this->setStyleSheet(generateStyle(false));
    this->setCursor(Qt::PointingHandCursor);
    connect(this, SIGNAL(clicked(bool)), this, SLOT(click()));
}

QString MenuBtn::generateStyle(bool setFocus)
{
    QString color = BG_COLOR;
    if (setFocus)
        color = ON_CLICK_BG_COLOR;
    
    return "background-color:" + color + "; color:"+ TEXT_COLOR +"; font-weight:bold; border: 0 px;font-size:20px;}";
}

void MenuBtn::setFocus(bool focus)
{
    this->focus = focus;
    this->setStyleSheet(generateStyle(focus));
    this->update();

}

void MenuBtn::paintEvent(QPaintEvent* event)
{
    QPushButton::paintEvent(event);
    if (this->focus) {
        
        QColor color(TEXT_COLOR);
        QPainter painter(this);
        QPoint pos = this->pos();
        QSize size = this->size();
        painter.setPen(QPen(color, 6));
        painter.drawLine(pos.x(), size.height(), 0, size.height());
    }

}

void MenuBtn::click()
{
    this->menu->changeFocus(*this);
    this->setFocus(true);
    this->tab->showTab();
    
}
