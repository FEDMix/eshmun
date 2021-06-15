#include "previewannotation.h"
#include "ui_previewannotation.h"
#include "../../components/VTKWidget/scenewidget.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>

PreviewAnnotation::PreviewAnnotation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewAnnotation)
{
    ui->setupUi(this);
    ui->previewWidget->setSpacing(10);
    //Set the display mode, picture on top, name on bottom
    ui->previewWidget->setViewMode(QListWidget::IconMode);
    ui->previewWidget->setFlow(QListWidget::LeftToRight);
    //Set picture size in item
     ui->previewWidget->setIconSize(QSize(100,100));
    //Set layout policy (Adjust to, Fixed not to)
     ui->previewWidget->setResizeMode(QListWidget::Fixed);
     ui->previewWidget->setCurrentRow(1);

       ui->previewWidget->setWrapping(false);
    //Set cell item cannot be dragged
     ui->previewWidget->setMovement(QListWidget::Static);
    //Set scroll bar not to display
     ui->previewWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     ui->previewWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);


     ui->previewWidget->setVerticalScrollMode(QListWidget::ScrollPerPixel);

}
void PreviewAnnotation::loadPreview(QString path){
    QDir directory(path);
    qDebug() << "Path" << path;
    directory.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);

    QFileInfoList filelistinfo = directory.entryInfoList();
    foreach (const QFileInfo &fileinfo, filelistinfo) {
        // push image paths into thumbnails array
        thumbnails << fileinfo.absoluteFilePath();
    }
    qDebug() << "Scans" << thumbnails;
    const int numRows = thumbnails.size();
    for(int i=0;i<numRows;++i) {

        vtkSmartPointer<vtkDICOMImageReader> dicomReader_scan =
            vtkSmartPointer<vtkDICOMImageReader>::New();
        qDebug() << "item" << thumbnails.at(i);
        dicomReader_scan->SetDirectoryName(thumbnails.at(i).toStdString().c_str()); //path need to be std::string
        dicomReader_scan->Update();

        vtkSmartPointer<vtkImageData> imageData = dicomReader_scan->GetOutput();
        qDebug() << "imageDta" << imageData;
        auto item = new QListWidgetItem();
        SceneWidget *widget = new SceneWidget(this);
        widget->show();
        widget->SetImageData(imageData);
        item->setSizeHint(QSize(100,120));

        ui->previewWidget->insertItem(i,item);
        ui->previewWidget->setItemWidget(item,widget);
    }
}
PreviewAnnotation::~PreviewAnnotation()
{
    delete ui;
}
