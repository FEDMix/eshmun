#include "pages/selectPatient/mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>
#include <QVTKOpenGLNativeWidget.h>

int main(int argc, char *argv[])
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());
    QApplication a(argc, argv);
    a.setStyleSheet("./stylesheet.qss"); // this stylesheet doesn't work
    Q_INIT_RESOURCE(resources);
    MainWindow w;
    w.show();
    return a.exec();
}
