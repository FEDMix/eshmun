#include "annotationpreview.h"
#include "ui_annotationpreview.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>
AnnotationPreview::AnnotationPreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnnotationPreview)
{
    ui->setupUi(this);

    // Set up List View
       ui->previewScans->setFlow(QListView::LeftToRight);
       ui->previewScans->setResizeMode(QListView::Adjust);
       ui->previewScans->setViewMode(QListView::ListMode);
       ui->previewScans->setIconSize(QSize(150,130));
       ui->previewScans->setWrapping(false);
       ui->previewScans->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}
void AnnotationPreview::loadPreview(QString path){
    if(!path.isEmpty()){
            QDir dir(path);
            QStringList filter;
            filter << QLatin1String("*.dcm");
            dir.setNameFilters(filter);
            QFileInfoList filelistinfo = dir.entryInfoList();

            foreach (const QFileInfo &fileinfo, filelistinfo) {
                // push image paths into thumbnails array
                thumbnails << fileinfo.absoluteFilePath();
            }
        }
    qDebug() << "Scans" << thumbnails.size();
//    // Create Model
//    model = new QStandardItemModel(this);
//    proxyModel = new QSortFilterProxyModel(this);
//    model->insertColumn(0);
//    const int numRows = thumbnails.size();
//    model->insertRows(0, numRows);

//    // Iterate through imagepaths & create an image/preview from each image path

//    for(int i=0;i<numRows;++i){
//        vtkSmartPointer<vtkDICOMImageReader> dicomReader_scan =
//            vtkSmartPointer<vtkDICOMImageReader>::New();
//        dicomReader_scan->SetDirectoryName(thumbnails.at(i).toStdString().c_str()); //path need to be std::string
//        dicomReader_scan->Update();

//        vtkSmartPointer<vtkImageData> imageData = dicomReader_scan->GetOutput();
//        SceneWidget scene1 = SceneWidget();
//        scene1.SetImageData(imageData);

////        model->setData(model->index(i,0),scene1,Qt::DecorationRole);
//    }

//    proxyModel->setSourceModel(model);
//    proxyModel->setFilterKeyColumn(0);
//    ui->previewScans->setModel(model);
//    selectionModel = ui->previewScans->selectionModel();
//    QModelIndex currentIndex = ui->previewScans->currentIndex();

// selectionModel->setCurrentIndex(model->index(1,currentIndex.column()),QItemSelectionModel::SelectCurrent);
// selectionModel->select(model->index(1,currentIndex.column()),QItemSelectionModel::SelectCurrent);
// // emit the selection change event
// connect(selectionModel, &QItemSelectionModel::currentChanged, this,&AnnotationPreview::update);
}

AnnotationPreview::~AnnotationPreview()
{
    delete ui;
}

void AnnotationPreview::on_prevScan_clicked()
{
//    QModelIndex mi = ui->previewScans->currentIndex();
//            if(mi.row() > 0) {
//                ui->previewScans->setCurrentIndex(mi.sibling(mi.row()-1,mi.column()));
//                ui->previewScans->scrollTo(ui->previewScans->currentIndex());
//            }
}
void AnnotationPreview::on_nextScan_clicked()
{
//    QModelIndex mi = ui->previewScans->currentIndex();
//        if(mi.row() < ui->previewScans->model()->rowCount()-1){
//            ui->previewScans->setCurrentIndex(mi.sibling(mi.row()+1,mi.column()));
//            ui->previewScans->scrollTo(ui->previewScans->currentIndex());
//        }

}
void AnnotationPreview::update(const QModelIndex &current, const QModelIndex &previous){
//    qDebug() << "changed" << "current" << thumbnails.at(current.row()) << "previous" << previous.row();

}
