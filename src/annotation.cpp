#include "annotation.h"
#include "ui_annotation.h"

Annotation::Annotation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Annotation)
{
    ui->setupUi(this);
}

Annotation::~Annotation()
{
    delete ui;
}
