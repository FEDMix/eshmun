#include "annotation.h"
#include "ui_annotation.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>

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
    vtkSmartPointer<vtkImageData> dummyData = ui->sceneWidget->GetDummyData();
    ui->sceneWidget->SetImageData(dummyData);
    ui->sceneWidget2->SetImageData(dummyData);
    ui->sceneWidget3->SetImageData(dummyData);
}

Annotation::~Annotation()
{
    delete ui;
}

void Annotation::LoadData(std::string path) {
    vtkSmartPointer<vtkDICOMImageReader> dicomReader =
        vtkSmartPointer<vtkDICOMImageReader>::New();
    dicomReader->SetDirectoryName(path.c_str());
    dicomReader->Update();

    vtkSmartPointer<vtkImageData> imageData = dicomReader->GetOutput();
    ui->sceneWidget->SetImageData(imageData);
    ui->sceneWidget2->SetImageData(imageData);
    ui->sceneWidget3->SetImageData(imageData);
}
