#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
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
    void pushButton_selectSubject();
    void pushButton_goBack();
    void pushButton_subject1();
    void pushButton_subject2();
    void pushButton_subject3();

private:
    Ui::MainWindow *ui;
    Annotation *annotation1;
    Annotation *annotation2;
    Annotation *annotation3;
};
#endif // MAINWINDOW_H
