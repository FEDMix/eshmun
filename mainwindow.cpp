#include "mainwindow.h"

#include <vtkActor.h>
#include <vtkPSphereSource.h>
#include <vtkPolyDataMapper.h>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QObject::connect(ui->medicalViewer, SIGNAL(Mouse_State()), ui->medicalViewer,
                   SLOT(onDrawSphereClick()));
}

MainWindow::~MainWindow() { delete ui; }
