#include "mainwindow.h"
#include "tabwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    TabWindow t;
    t.show();
//    w.show();
    return a.exec();
}
