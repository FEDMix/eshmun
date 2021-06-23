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
    // signal from annotation preview -> slot update the othogonal view
    connect(preview,SIGNAL(sync_path_signal(QString)),this,SLOT(SyncPreview(QString)));
}

void Annotation::pushButton_initVTK()
{
    vtkSmartPointer<vtkImageData> dummyData = ui->mainSceneAxial->GetDummyData();
    ui->mainSceneAxial->SetImageData(dummyData);
    ui->mainSceneCoronal->SetImageData(dummyData);
    ui->mainSceneSagittal->SetImageData(dummyData);
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
        ui->mainSceneAxial->SetImageData(imageData);
        ui->mainSceneCoronal->SetImageData(imageData);
        ui->mainSceneSagittal->SetImageData(imageData);
        ui->mainSceneAxial->SetPlaneOrientationToAxial();
        ui->mainSceneCoronal->SetPlaneOrientationToCoronal();
        ui->mainSceneSagittal->SetPlaneOrientationToSagittal();

        ui->mainSceneAxial->AddLinkedSceneWidget(ui->mainSceneCoronal, true);
        ui->mainSceneAxial->AddLinkedSceneWidget(ui->mainSceneSagittal, true);
        ui->mainSceneCoronal->AddLinkedSceneWidget(ui->mainSceneSagittal, true);

        // create vtk pointer for all annotations
        QString path_annotation = imageloader->image_annotation(path);
        preview->loadPreview(path_annotation);
}
void Annotation::SyncPreview(QString path) {
    qInfo( "Directory path to annotation images to sync preview: %s", qUtf8Printable(path));
    vtkSmartPointer<vtkDICOMImageReader> dicomReader =
        vtkSmartPointer<vtkDICOMImageReader>::New();
    dicomReader->SetDirectoryName(path.toStdString().c_str()); //path need to be std::string
    dicomReader->Update();

    vtkSmartPointer<vtkImageData> imageData = dicomReader->GetOutput();
    ui->mainSceneAxial->SetImageData(imageData);
}




