#include "gowidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GoWidget w;
    w.show();
    return a.exec();
}
