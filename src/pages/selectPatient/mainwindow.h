#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QString>
#include <QIODevice>
#include <QDebug>
#include "../patientView/annotation.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void pushButton_addPatient();

    void on_pageSelect_windowTitleChanged(const QString &title);

    void on_pageSelect_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    Annotation *annotation;
};
#endif // MAINWINDOW_H
