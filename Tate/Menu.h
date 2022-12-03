#pragma once

#include "qframe.h"
#include <qboxlayout.h>
#include "MenuBtn.h"
#include "Tab.h"


class Tate;
class TopWindow;

class Menu : public QFrame {
	Q_OBJECT

public:
	Menu(TopWindow* father);

	/**
	 * Makes the button with actual focus lose it
	 * 
	 * @param The button which has now focus
	*/
	void changeFocus(MenuBtn&);

	/**
	 * Create a button linked to a tab and add it to the menu
	 *
	 * @param The tab which the button should be linked
	 * @param If the tab is the last tab of the list of tabs
	*/
	void addMenuButton(Tab&, bool lastTab);

	/**
	 * Create a button with the logo of the application
	 *
	 * 
	*/
	void addLogo();

	/**
	 * Create buttons with the basic icons for the application (minimize, close...)
	 *
	 *
	*/
	void addIcons();
	
	
private:
	//members
	QHBoxLayout* lyt;
	QList<MenuBtn*> buttons;
	MenuBtn* focusedBtn; //the button with actual focus
	TopWindow* father;
	const QString BG_COLOR_ON_CLICK = "#6C757D";
	const QString BG_COLOR = "#1B1F22";
	const QString STYLE = "background-color:"+ BG_COLOR + "; margin:0px; padding:10px; ";
	const QList<QString> ICONS_PATH = { "./icons/logo.jpg", "./icons/minimize.png", "./icons/close.png" };


private slots:
	void closeApp();
	void nietzsche();
	
};

