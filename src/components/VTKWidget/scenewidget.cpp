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
#include <vtkDICOMImageReader.h>
#include <vtkResliceImageViewer.h>

SceneWidget::SceneWidget(QWidget* parent)
    : QVTKOpenGLNativeWidget(parent)
{
    vtkNew<vtkGenericOpenGLRenderWindow> window;
    setRenderWindow(window.Get());

    // Image viewer
    imageViewer = vtkSmartPointer<OverlayViewer>::New();
    imageViewer->SetRenderWindow(window);
    imageViewer->SetupInteractor(window->GetInteractor());

    // Render window interactor
    renderWindowInteractor = imageViewer->GetRenderWindow()->GetInteractor();
    imageViewer->SetupInteractor(renderWindowInteractor);

    // Renderer
    renderer = imageViewer->GetRenderer();
    renderer->SetBackground(0.5, 0.5, 0.5);

    renderWindow()->SetAlphaBitPlanes(1);
    renderWindow()->SetMultiSamples(0);
    renderer->SetUseDepthPeeling(1);
    renderer->SetMaximumNumberOfPeels(10);
    renderer->SetOcclusionRatio(0.1);

    // Camera
    camera = renderer->GetActiveCamera();
    camera->SetViewUp(0, 1, 0);
    camera->SetPosition(0, 0, 1000);
    camera->SetFocalPoint(0, 0, 0);
    camera->SetParallelProjection(true);

    // Interactor style
    imageViewer->SetSliceScrollOnMouseWheel(true);
    style = vtkSmartPointer<LinkedInteractorStyle>::New();
    style->SetBaseWidget(this);
    renderWindowInteractor->SetInteractorStyle(style);
    renderWindowInteractor->Initialize();
}

void SceneWidget::SetImageData(vtkSmartPointer<vtkImageData> imageData) {
    this->imageData = imageData;
    this->imageViewer->SetInputData(imageData);
    Refresh();
    SetPlaneOrientationToAxial();
}

void SceneWidget::AnnotationOverlay(vtkSmartPointer<vtkImageData> imageData) {
    this->imageViewer->SetOverlay(imageData);
    Refresh();
}

void SceneWidget::SetPlaneOrientationToSagittal() {    
    float center[3], dim[3];
    GetCenterAndDimensions(center, dim);

    camera->SetParallelScale(0.5f * static_cast<float>(dim[1]));
    camera->SetFocalPoint(center[0], center[1], center[2]);
    camera->SetPosition(center[0] + dim[0], center[1], center[2]);
    imageViewer->SetSliceOrientationToXZ();
    renderer->ResetCameraClippingRange();
    Refresh();
}

void SceneWidget::SetPlaneOrientationToCoronal() {    
    float center[3], dim[3];
    GetCenterAndDimensions(center, dim);

    camera->SetParallelScale(0.5f * static_cast<float>(dim[2]));
    camera->SetFocalPoint(center[0], center[1], center[2]);
    camera->SetPosition(center[0], center[1] + dim[1], center[2]);
    imageViewer->SetSliceOrientationToYZ();
    renderer->ResetCameraClippingRange();
    Refresh();
}

void SceneWidget::SetPlaneOrientationToAxial() {
    float center[3], dim[3];
    GetCenterAndDimensions(center, dim);

    camera->SetParallelScale(0.5f * static_cast<float>(dim[1]));
    camera->SetFocalPoint(center[0], center[1], center[2]);
    camera->SetPosition(center[0], center[1], center[2] + dim[2]);
    imageViewer->SetSliceOrientationToXY();
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
    if( position <= imageViewer->GetSliceMax() && position >= imageViewer->GetSliceMin() )
        imageViewer->SetSlice(position);
    Refresh();
}

int SceneWidget::GetSliceIndex() {
    return imageViewer->GetSlice();
}

double SceneWidget::GetColorWindow() {
    return imageViewer->GetColorWindow();
}

double SceneWidget::GetColorLevel() {
    return imageViewer->GetColorLevel();
}

void SceneWidget::SetWindowLevel(double window, double level) {
    imageViewer->SetColorWindow(window);
    imageViewer->SetColorLevel(level);
    Refresh();
}

void SceneWidget::ResetCamera()
{
    renderer->ResetCamera();
    Refresh();
}

void SceneWidget::Refresh()
{
    imageViewer->Render();
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
