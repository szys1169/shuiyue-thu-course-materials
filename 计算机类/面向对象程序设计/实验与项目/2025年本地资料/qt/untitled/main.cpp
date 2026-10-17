#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    dictionary();
    QApplication a(argc, argv);
    GamestartWindow w;
    w.show();
    return a.exec();
}
