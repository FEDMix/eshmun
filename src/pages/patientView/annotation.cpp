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

    

    // Set up List View
    ui->previewScans->setFlow(QListView::LeftToRight);
    ui->previewScans->setResizeMode(QListView::Adjust);
    ui->previewScans->setViewMode(QListView::IconMode);
    ui->previewScans->setIconSize(QSize(150,130));
    ui->previewScans->setWrapping(false);
    ui->previewScans->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create Model
    model = new QStandardItemModel(this);
    proxyModel = new QSortFilterProxyModel(this);

    //Make Data
    QDir directory("/Users/pushpanjali/eScience/FedMix/ExampleData/");
    // read file paths from images directory
    const QString folderPath = directory.filePath("images/");
    if(!folderPath.isEmpty()){
        QDir dir(folderPath);
        QStringList filter;
        filter << QLatin1String("*.png");
        filter << QLatin1String("*.jpeg");
        filter << QLatin1String("*.jpg");
        dir.setNameFilters(filter);
        QFileInfoList filelistinfo = dir.entryInfoList();

        foreach (const QFileInfo &fileinfo, filelistinfo) {
            // push image paths into thumbnails array
            thumbnails << fileinfo.absoluteFilePath();
        }
    }


    model->insertColumn(0);
    const int numRows = thumbnails.size();
    model->insertRows(0, numRows);
    // Iterate through imagepaths & create an image/preview from each image path
    for(int i=0;i<numRows;++i){
        // This will be replaced by creating sceneWidget
         QPixmap thumbnail = QPixmap(thumbnails.at(i)).scaled(140,120);

         model->setData(model->index(i,0),thumbnail,Qt::DecorationRole);
    }

    proxyModel->setSourceModel(model);
    proxyModel->setFilterKeyColumn(0);
    ui->previewScans->setModel(model);
    selectionModel = ui->previewScans->selectionModel();
    QModelIndex currentIndex = ui->previewScans->currentIndex();
//    selectionModel->setCurrentIndex(model->index(1,currentIndex.column()),QItemSelectionModel::SelectCurrent);
//    selectionModel->select(model->index(1,currentIndex.column()),QItemSelectionModel::SelectCurrent);
    // emit the selection change event
    connect(selectionModel, &QItemSelectionModel::currentChanged, this, &Annotation::update);



}

// preview scan selection changed
void Annotation::update(const QModelIndex &current, const QModelIndex &previous){
    qDebug() << "changed" << "current" << thumbnails.at(current.row()) << "previous" << previous.row();
    // set the selected preview scan in orthogonal view
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

void Annotation::on_nextScan_clicked()
{
    QModelIndex mi = ui->previewScans->currentIndex();
    if(mi.row() < ui->previewScans->model()->rowCount()-1){
        ui->previewScans->setCurrentIndex(mi.sibling(mi.row()+1,mi.column()));
        ui->previewScans->scrollTo(ui->previewScans->currentIndex());
    }
}

void Annotation::on_prevScan_clicked()
{
    QModelIndex mi = ui->previewScans->currentIndex();
        if(mi.row() > 0) {
            ui->previewScans->setCurrentIndex(mi.sibling(mi.row()-1,mi.column()));
            ui->previewScans->scrollTo(ui->previewScans->currentIndex());
        }
}

