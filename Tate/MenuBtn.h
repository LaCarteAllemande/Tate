#pragma once

#include "qpushbutton.h"
#include "qpainter.h"
#include <QPaintEvent>

class Menu;
class Tab;

/*
Button used in the Menu of the application
*/
class MenuBtn : public QPushButton
{
	Q_OBJECT

public:

	/**
	 * Constructor
	 * @param The menu the button is in
	 * @param The tab the button should point to
	 * @return A button for the menu of the application
	*/
	MenuBtn(Menu& menu, Tab& tab);

	/**
	 * Generate the QSS style for a menu button
	 * @param Does the button have focus ?
	 * @return The style as a QSTRING
	*/
	static QString generateStyle(bool setFocus);

	/**
	 * Tell the button if it has focus
	 * @param Focus or not
	*/
	void setFocus(bool focus);


	inline static const QString BG_COLOR = "#1B1F22";
	inline static const QString TEXT_COLOR = "#F8F9FA";
	inline static const QString ON_CLICK_BG_COLOR = "#1B1F22";

public slots:
	void click();

private:
	Menu* menu; //the menu of the application
	Tab* tab; //the tab the button should point to
	bool focus; //if the button has focus
	void paintEvent(QPaintEvent*);
};


