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


    ui->previewContainer->layout()->addWidget(preview);
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

void Annotation::LoadData(QString path) {
    ImageLoader* imageloader = new ImageLoader();
    // create vtk pointer for patient scan
    QString path_scan = imageloader->image_scan(path);
    vtkSmartPointer<vtkDICOMImageReader> dicomReader_scan =
        vtkSmartPointer<vtkDICOMImageReader>::New();
    dicomReader_scan->SetDirectoryName(path_scan.toStdString().c_str()); //path need to be std::string
    dicomReader_scan->Update();

    vtkSmartPointer<vtkImageData> imageData = dicomReader_scan->GetOutput();
    ui->sceneWidget->SetImageData(imageData);
    ui->sceneWidget2->SetImageData(imageData);
    ui->sceneWidget3->SetImageData(imageData);

    // create vtk pointer for all annotations
    QString path_annotation = imageloader->image_annotation(path);
    preview->loadPreview(path_annotation);

}


