#include "scenewidget.h"

#include <vtkDataSetMapper.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkProperty.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageNoiseSource.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>

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
    //ipw->SetWindowLevel(5500, 1000);
    SetPlaneOrientationToZAxis();
    ipw->UpdatePlacement();
    ipw->On();

    Refresh();
}

void SceneWidget::SetPlaneOrientationToXAxis() {
    float center[3], dim[3];
    GetCenterAndDimensions(center, dim);
    int* extent = imageData->GetExtent();

    ipw->SetPlaneOrientationToXAxes();
    ipw->SetSliceIndex(0.5 * (extent[0] + extent[1]));

    camera->SetParallelScale(0.5f * static_cast<float>(dim[1]));
    camera->SetFocalPoint(center[0], center[1], center[2]);
    camera->SetPosition(center[0] + dim[0], center[1], center[2]);
    camera->SetViewUp(0, 1, 0);
    renderer->ResetCameraClippingRange();
}

void SceneWidget::SetPlaneOrientationToYAxis() {
    float center[3], dim[3];
    GetCenterAndDimensions(center, dim);
    int* extent = imageData->GetExtent();

    ipw->SetPlaneOrientationToYAxes();
    ipw->SetSliceIndex(0.5 * (extent[2] + extent[3]));

    camera->SetParallelScale(0.5f * static_cast<float>(dim[2]));
    camera->SetFocalPoint(center[0], center[1], center[2]);
    camera->SetPosition(center[0], center[1] + dim[1], center[2]);
    camera->SetViewUp(0, 0, -1);
    renderer->ResetCameraClippingRange();
}

void SceneWidget::SetPlaneOrientationToZAxis() {
    float center[3], dim[3];
    GetCenterAndDimensions(center, dim);
    int* extent = imageData->GetExtent();

    ipw->SetPlaneOrientationToZAxes();
    ipw->SetSliceIndex(0.5 * (extent[4] + extent[5]));

    camera->SetParallelScale(0.5f * static_cast<float>(dim[1]));
    camera->SetFocalPoint(center[0], center[1], center[2]);
    camera->SetPosition(center[0], center[1], center[2] + dim[2]);
    camera->SetViewUp(0, 1, 0);
    renderer->ResetCameraClippingRange();
}

void SceneWidget::GetCenterAndDimensions(float* center, float* dim) {
    int* extent = imageData->GetExtent();
    double* origin = imageData->GetOrigin();
    double* spacing = imageData->GetSpacing();
    center[0] = origin[0] + 0.5 * (extent[0] + extent[1]) * spacing[0];
    center[1] = origin[1] + 0.5 * (extent[2] + extent[3]) * spacing[1];
    center[2] = origin[2] + 0.5 * (extent[4] + extent[5]) * spacing[2];
    dim[0] = (extent[1] - extent[0] + 1) * spacing[0];
    dim[1] = (extent[3] - extent[2] + 1) * spacing[1];
    dim[2] = (extent[5] - extent[4] + 1) * spacing[2];
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

vtkSmartPointer<vtkImageData> SceneWidget::GetDummyData()
{
    // Create an image of noise
    vtkSmartPointer<vtkImageNoiseSource> noiseSource = 
        vtkSmartPointer<vtkImageNoiseSource>::New();
    noiseSource->SetWholeExtent(0, 100, 0, 100, 0, 100);
    noiseSource->SetMinimum(0.0);
    noiseSource->SetMaximum(255.0);
    noiseSource->Update();
    return noiseSource->GetOutput();
}

void SceneWidget::SaveScreenshot(std::string path)
{
    vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = 
        vtkSmartPointer<vtkWindowToImageFilter>::New();
    windowToImageFilter->SetInput(renderWindow());
    windowToImageFilter->Update();

    vtkSmartPointer<vtkPNGWriter> writer = 
        vtkSmartPointer<vtkPNGWriter>::New();
    writer->SetFileName(path.c_str());
    writer->SetInputConnection(windowToImageFilter->GetOutputPort());
    writer->Write();
}
