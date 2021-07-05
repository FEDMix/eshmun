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
    // disable drag & drop
    ui->previewWidget->setDragEnabled(false);
    // disable moving icons
    ui->previewWidget->setMovement(QListView::Static);
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
    directory.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);

    QFileInfoList filelistinfo = directory.entryInfoList();
    foreach (const QFileInfo &fileinfo, filelistinfo) {
        // push image paths into thumbnails array
        thumbnails << fileinfo.absoluteFilePath();
    }
    const int numRows = thumbnails.size();
    for(int i=0;i<numRows;++i) {
        // load base image
        // get parent path
        QDir current_path = QDir::cleanPath(path);
        current_path.cdUp();
        QString parent_path = current_path.path();
        qInfo( "Check this: %s", qUtf8Printable(parent_path));
        QString path_scan = QDir::cleanPath(parent_path + QDir::separator()
                                            + "scans" + QDir::separator()+ "scan_to_annotate");
        vtkSmartPointer<vtkDICOMImageReader> dicomReader_scan =
            vtkSmartPointer<vtkDICOMImageReader>::New();
        dicomReader_scan->SetDirectoryName(path_scan.toStdString().c_str());
        dicomReader_scan->Update();
        vtkSmartPointer<vtkImageData> imageData_scan = dicomReader_scan->GetOutput();

        // load annotation
        vtkSmartPointer<vtkDICOMImageReader> dicomReader_annotation =
            vtkSmartPointer<vtkDICOMImageReader>::New();
        dicomReader_annotation->SetDirectoryName(thumbnails.at(i).toStdString().c_str()); //path need to be std::string
        dicomReader_annotation->Update();

        vtkSmartPointer<vtkImageData> imageData_annotation = dicomReader_annotation->GetOutput();

        // Set-up list widget
        auto item = new QListWidgetItem();
        SceneWidget *widget = new SceneWidget(this);
        widget->show();
        widget->SetImageData(imageData_scan);
        widget->AnnotationOverlay(imageData_annotation);
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
    QString path_sync = thumbnails.at(clikedItemIndex);
    emit sync_path_signal(path_sync);
}
// Get the path of annotation when selection is updated on prev,next click
void PreviewAnnotation::update(const QModelIndex &current, const QModelIndex &previous){
    ui->previewWidget->scrollTo(ui->previewWidget->currentIndex());
    ui->previewWidget->selectionModel()->select(ui->previewWidget->currentIndex(),QItemSelectionModel::Select);
    

    int clikedItemIndex = ui->previewWidget->row(ui->previewWidget->currentItem());
    QString path_sync = thumbnails.at(clikedItemIndex);
    emit sync_path_signal(path_sync);

}



