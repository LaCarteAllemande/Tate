#include "labelObjectif.h"

QString STYLE_CASE = "background-color: white;font-size:18px;border:1px solid black; padding: 10px 20px;";

LabelObjectif::LabelObjectif(std::string nom, QWidget* wdg)
{
	setParent(wdg);
	setText(QString::fromStdString(nom));
	setAlignment(Qt::AlignCenter);
	setStyleSheet(STYLE_CASE);
}