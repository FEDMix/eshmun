#include "tabscreen.h"
#include "ui_tabscreen.h"

tabscreen::tabscreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tabscreen)
{
    ui->setupUi(this);
}

tabscreen::~tabscreen()
{
    delete ui;
}
