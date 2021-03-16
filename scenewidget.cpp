#include "scenewidget.h"

#include <vtkDataSetMapper.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkProperty.h>
#include <vtkInteractorStyleImage.h>

SceneWidget::SceneWidget(QWidget* parent)
    : QVTKOpenGLNativeWidget(parent)
{
    vtkNew<vtkGenericOpenGLRenderWindow> window;
    setRenderWindow(window.Get());

    // Camera
    camera = vtkSmartPointer<vtkCamera>::New();
    camera->SetViewUp(0, 1, 0);
    camera->SetPosition(0, 0, 1000);
    camera->SetFocalPoint(0, 0, 0);
    camera->SetParallelProjection(true);

    // Renderer
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->SetActiveCamera(camera);
    renderer->SetBackground(0.5, 0.5, 0.5);
    renderWindow()->AddRenderer(renderer);

    // Render window interactor
    renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow());

    // Interactor style
    vtkSmartPointer<vtkInteractorStyleImage> style = 
        vtkSmartPointer<vtkInteractorStyleImage>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    ipw = vtkSmartPointer<vtkImagePlaneWidget>::New();
    ipw->SetInteractor(renderWindowInteractor);
    ipw->RestrictPlaneToVolumeOn();
    ipw->DisplayTextOn();
}

void SceneWidget::SetImageData(vtkSmartPointer<vtkImageData> imageData) {
    this->imageData = imageData;

    ipw->SetInputData(imageData);
    ipw->SetWindowLevel(5500, 1000);
    ipw->SetPlaneOrientationToZAxes();

    ipw->UpdatePlacement();
    ipw->On();
    Refresh();
}

void SceneWidget::SetPlaneOrientationToXAxis() {
    ipw->SetPlaneOrientationToXAxes();
    camera->SetViewUp(0, 1, 0);
    camera->SetPosition(1000, 0, 0);
    int* extent = imageData->GetExtent();
    ipw->SetSliceIndex((extent[0] + extent[1]) / 2);
    ResetCamera();
}

void SceneWidget::SetPlaneOrientationToYAxis() {
    ipw->SetPlaneOrientationToYAxes();
    camera->SetViewUp(1, 0, 0);
    camera->SetPosition(0, 1000, 0);
    ResetCamera();
}

void SceneWidget::SetPlaneOrientationToZAxis() {
    ipw->SetPlaneOrientationToZAxes();
    camera->SetViewUp(0, 1, 0);
    camera->SetPosition(0, 0, 1000);
    ResetCamera();
}

void SceneWidget::SetSliceIndex(int position) {
    ipw->SetSliceIndex(position);
    Refresh();
}

void SceneWidget::ResetCamera()
{
    renderer->ResetCamera();
    Refresh();
}

void SceneWidget::Refresh()
{
    renderWindow()->Render();
    renderer->ResetCameraClippingRange();
    update();
}
