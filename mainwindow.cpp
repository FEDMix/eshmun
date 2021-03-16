#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

#include <vtkDataSetReader.h>
#include <vtkVolume16Reader.h>

MainWindow::MainWindow(QWidget* parent)
    :     QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::showAboutDialog()
{
    QMessageBox::information(
        this, "About",
        "TODO");
}

void MainWindow::showOpenFileDialog()
{
    // QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "",
    //     "VTK Files (*.vtk)");

    // // Open file
    // QFile file(fileName);
    // file.open(QIODevice::ReadOnly);

    // // Return on Cancel
    // if (!file.exists())
    //     return;

    // openFile(fileName);
    openFile("");
}

void MainWindow::openFile(const QString& fileName)
{
    ui->sceneWidget->removeDataSet();

    // // Create reader
    // vtkSmartPointer<vtkDataSetReader> reader = vtkSmartPointer<vtkDataSetReader>::New();
    // reader->SetFileName(fileName.toStdString().c_str());


    vtkSmartPointer<vtkVolume16Reader> reader = vtkSmartPointer<vtkVolume16Reader>::New();
    reader->SetDataDimensions(256, 256);
    reader->SetImageRange(1, 94);
    //reader->SetDataByteOrderToLittleEndian();
    reader->SetFilePrefix ("/Users/peter/repos/esc/data/fedmix/fullHead/headsq");
    reader->SetDataSpacing (0.9375, 0.9375, 1.5);

    // Read the file
    reader->Update();

    vtkSmartPointer<vtkImageData> imageData = reader->GetOutput();
    if (imageData != nullptr) {
        ui->sceneWidget->setImageData(imageData);
    }
    // Add data set to 3D view
    // vtkSmartPointer<vtkDataSet> dataSet = reader->GetOutput();
    // if (dataSet != nullptr) {
    //     ui->sceneWidget->addDataSet(reader->GetOutput());
    // }
}
