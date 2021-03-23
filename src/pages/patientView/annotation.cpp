#include "annotation.h"
#include "ui_annotation.h"

Annotation::Annotation(QWidget *parent) : QDialog(parent),
                                          ui(new Ui::Annotation)
{
    ui->setupUi(this);
    // push button on select page
    QPushButton *button_initVTK = Annotation::findChild<QPushButton *>("initVTK"); // search for a widget by providing a name
    connect(button_initVTK, SIGNAL(released()), this,
            SLOT(pushButton_initVTK())); // assign signals and slots
}

void Annotation::pushButton_initVTK()
{
    ui->sceneWidget->SetImageData(0);
    ui->sceneWidget2->SetImageData(0);
    ui->sceneWidget3->SetImageData(0);
}

Annotation::~Annotation()
{
    delete ui;
}