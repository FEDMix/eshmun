#include "mainwindow.h"
#include "tabscreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    tabscreen t;
    t.show();
//    w.show();
    return a.exec();
}
