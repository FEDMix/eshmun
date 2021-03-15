#include "medicalviewer.h"

#include <vtkActor.h>
#include <vtkPSphereSource.h>
#include <vtkPolyDataMapper.h>

MedicalViewer::MedicalViewer(QWidget *parent)
    : QVTKOpenGLNativeWidget(parent),
      mRenderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
      mRenderer(vtkSmartPointer<vtkRenderer>::New()),
      mInteractor(vtkSmartPointer<QVTKInteractor>::New()),
      mInteractorStyle(vtkSmartPointer<vtkInteractorStyle>::New()) {
  // Setup rendering
  mRenderWindow->AddRenderer(mRenderer);
  mRenderWindow->SetInteractor(mInteractor);
  SetRenderWindow(mRenderWindow);
  mInteractor->SetInteractorStyle(mInteractorStyle);
  mInteractor->Initialize();

  // Set background color
  mRenderer->SetBackground(1, 0, 0);
}

void MedicalViewer::mouseMoveEvent(QMouseEvent *ev) { emit Mouse_State(); }

void MedicalViewer::onDrawSphereClick() {
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
