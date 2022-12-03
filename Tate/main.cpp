#include "Tate.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));
    Tate w(a);

    w.showMaximized();
    return a.exec();
}
