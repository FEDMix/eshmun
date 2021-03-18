#include "tabwindow.h"
#include "ui_tabwindow.h"


TabWindow::TabWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabWindow)
{
    ui->setupUi(this);

}

TabWindow::~TabWindow()
{
    delete ui;
}
