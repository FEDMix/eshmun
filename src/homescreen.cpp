#include "homescreen.h"
#include "ui_homescreen.h"

HomeScreen::HomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen)
{
    ui->setupUi(this);
    QPixmap cover(":/Resources/figs/cover.png");
    int width = ui->orthoView->width();
    int height = ui->orthoView->height();
    ui->orthoView->setPixmap(cover.scaled(width, height, Qt::KeepAspectRatio));
    ui->orthoView->setPixmap(cover);
}

HomeScreen::~HomeScreen()
{
    delete ui;
}
