#include "scenewidget.h"

#include "linkedinteractorstyle.h"
#include <vtkDataSetMapper.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkProperty.h>
#include <vtkImageProperty.h>
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
    style = vtkSmartPointer<LinkedInteractorStyle>::New();
    renderWindowInteractor->SetInteractorStyle(style);
    style->SetBaseWidget(this);
    style->SetInteractionModeToImageSlicing();

    // Image reslice mapper
    imageMapper = vtkSmartPointer<vtkImageResliceMapper>::New();
    imageMapper->SliceFacesCameraOn();
    imageMapper->SliceAtFocalPointOn();
    imageMapper->JumpToNearestSliceOn();
    
    // Image slice prop
    image = vtkSmartPointer<vtkImageSlice>::New();
    image->SetMapper(imageMapper);
    image->GetProperty()->SetColorWindow(2000.0);
    image->GetProperty()->SetColorLevel(1000.0);
    renderer->AddViewProp(image);
}

void SceneWidget::SetImageData(vtkSmartPointer<vtkImageData> imageData) {
    this->imageData = imageData;
    this->imageMapper->SetInputData(imageData);
    Refresh();
}

void SceneWidget::SetPlaneOrientationToSagittal() {
    float center[3], dim[3];
    GetCenterAndDimensions(center, dim);

    camera->SetParallelScale(0.5f * static_cast<float>(dim[1]));
    camera->SetFocalPoint(center[0], center[1], center[2]);
    camera->SetPosition(center[0] + dim[0], center[1], center[2]);
    camera->SetViewUp(0, 0, 1);
    renderer->ResetCameraClippingRange();
    Refresh();
}

void SceneWidget::SetPlaneOrientationToCoronal() {
    float center[3], dim[3];
    GetCenterAndDimensions(center, dim);

    camera->SetParallelScale(0.5f * static_cast<float>(dim[2]));
    camera->SetFocalPoint(center[0], center[1], center[2]);
    camera->SetPosition(center[0], center[1] + dim[1], center[2]);
    camera->SetViewUp(0, 0, -1);
    renderer->ResetCameraClippingRange();
    Refresh();
}

void SceneWidget::SetPlaneOrientationToAxial() {
    float center[3], dim[3];
    GetCenterAndDimensions(center, dim);

    camera->SetParallelScale(0.5f * static_cast<float>(dim[1]));
    camera->SetFocalPoint(center[0], center[1], center[2]);
    camera->SetPosition(center[0], center[1], center[2] + dim[2]);
    camera->SetViewUp(0, 1, 0);
    renderer->ResetCameraClippingRange();
    Refresh();
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
    //TODO: ipw->SetSliceIndex(position);
    Refresh();
}

double SceneWidget::GetColorWindow() {
    return image->GetProperty()->GetColorWindow();
}

double SceneWidget::GetColorLevel() {
    return image->GetProperty()->GetColorLevel();
}

void SceneWidget::SetWindowLevel(double window, double level) {
    image->GetProperty()->SetColorWindow(window);
    image->GetProperty()->SetColorLevel(level);
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

void SceneWidget::AddLinkedSceneWidget(SceneWidget* linkedWidget, bool twoWay) {
    style->AddLinkedWidget(linkedWidget);
    if (twoWay) {
        linkedWidget->AddLinkedSceneWidget(this, false);
    }
}
