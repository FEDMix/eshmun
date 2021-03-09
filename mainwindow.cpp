#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <vtkActor.h>
#include <vtkPSphereSource.h>
#include <vtkPolyDataMapper.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      mRenderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
      mRenderer(vtkSmartPointer<vtkRenderer>::New()),
      mInteractor(vtkSmartPointer<QVTKInteractor>::New()),
      mInteractorStyle(vtkSmartPointer<vtkInteractorStyle>::New()) {
  ui->setupUi(this);

  // Setup rendering
  mRenderWindow->AddRenderer(mRenderer);
  mRenderWindow->SetInteractor(mInteractor);
  ui->openGLNativeWidget->SetRenderWindow(mRenderWindow);
  mInteractor->SetInteractorStyle(mInteractorStyle);
  mInteractor->Initialize();

  // Set background color
  mRenderer->SetBackground(1, 0, 0);

  // Add the UI connections
  QObject::connect(ui->pushButton, &QPushButton::clicked, this,
                   &MainWindow::onDrawSphereClick);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onDrawSphereClick() {
  // Create sphere
  vtkSmartPointer<vtkSphereSource> sphereSource =
      vtkSmartPointer<vtkPSphereSource>::New();
  sphereSource->SetRadius(5);
  sphereSource->Update();

  // Create actor where the sphere id rendered
  vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereMapper->SetInputData(sphereSource->GetOutput());

  vtkSmartPointer<vtkActor> sphere = vtkSmartPointer<vtkActor>::New();
  sphere->SetMapper(sphereMapper);

  // Add the sphere actor to the OpenGL
  mRenderer->AddViewProp(sphere);
  mRenderer->ResetCamera();
  mRenderWindow->Render();
}
