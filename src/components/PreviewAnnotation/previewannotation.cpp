#include "previewannotation.h"
#include "ui_previewannotation.h"
#include "../../components/VTKWidget/scenewidget.h"
//#include "../../pages/patientView/annotation.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>

PreviewAnnotation::PreviewAnnotation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreviewAnnotation)
{
    ui->setupUi(this);
    ui->previewWidget->setSpacing(5);

    ui->previewWidget->setStyleSheet("QListWidget::item { border: 1px solid black; padding:5px; margin-top:5px; } QListWidget::item:selected { border: 1px solid blue; }");
    //Set the display mode
    ui->previewWidget->setViewMode(QListWidget::IconMode);
    // set flow to horizontal only
    ui->previewWidget->setFlow(QListWidget::LeftToRight);
    ui->previewWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->previewWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->previewWidget->setWrapping(false);

    ui->previewWidget->setAutoScroll(false);
    //Set picture size in item
     ui->previewWidget->setIconSize(QSize(100,100));
    //Set layout policy (Adjust to, Fixed not to)
    ui->previewWidget->setResizeMode(QListWidget::Fixed);
    // set the selection mode
    ui->previewWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->previewWidget->setSelectionRectVisible(true);

    selectionModel = ui->previewWidget->selectionModel();
    selectionModel->setCurrentIndex(ui->previewWidget->currentIndex(),QItemSelectionModel::SelectCurrent);
    selectionModel->select(ui->previewWidget->currentIndex(),QItemSelectionModel::SelectCurrent);
    connect(selectionModel, &QItemSelectionModel::currentChanged, this,&PreviewAnnotation::update);
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

void PreviewAnnotation::on_nextButton_clicked()
{
     int currentIndex = ui->previewWidget->currentRow();
    qDebug() << "next index" << currentIndex << thumbnails.size();

    if(currentIndex >= thumbnails.size() - 1) {
        ui->nextButton->setDisabled(true);
        ui->prevButton->setDisabled(false);
    } else {
        ui->previewWidget->setCurrentRow(currentIndex+1);
    }

}

void PreviewAnnotation::on_prevButton_clicked()
{
    int currentIndex = ui->previewWidget->currentRow();
    if(currentIndex <= 0) {
        ui->prevButton->setDisabled(true);
        ui->nextButton->setDisabled(false);
    } else {
        ui->previewWidget->setCurrentRow(currentIndex-1);
    }
}

// Get the path of annotation clicked
void PreviewAnnotation::on_previewWidget_itemClicked(QListWidgetItem *item)
{
    int clikedItemIndex = ui->previewWidget->row(item);
    qDebug() << "item" << thumbnails.at(clikedItemIndex);
    QString path_sync = thumbnails.at(clikedItemIndex);
    emit sync_path_signal(path_sync);
}
// Get the path of annotation when selection is updated on prev,next click
void PreviewAnnotation::update(const QModelIndex &current, const QModelIndex &previous){
    ui->previewWidget->scrollTo(ui->previewWidget->currentIndex());
    ui->previewWidget->selectionModel()->select(ui->previewWidget->currentIndex(),QItemSelectionModel::Select);
    qDebug() << "changed" << "current" << ui->previewWidget->selectedItems();

    int clikedItemIndex = ui->previewWidget->row(ui->previewWidget->currentItem());
    qDebug() << "item" << thumbnails.at(clikedItemIndex);
    QString path_sync = thumbnails.at(clikedItemIndex);
    emit sync_path_signal(path_sync);

}



