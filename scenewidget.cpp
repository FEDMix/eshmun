#include "scenewidget.h"

#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkImagePlaneWidget.h>

SceneWidget::SceneWidget(QWidget* parent)
    : QVTKOpenGLNativeWidget(parent)
{
    vtkNew<vtkGenericOpenGLRenderWindow> window;
    setRenderWindow(window.Get());

    // Camera
    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
    camera->SetViewUp(0, 1, 0);
    camera->SetPosition(0, 0, 10);
    camera->SetFocalPoint(0, 0, 0);

    // Renderer
    m_renderer = vtkSmartPointer<vtkRenderer>::New();
    m_renderer->SetActiveCamera(camera);
    m_renderer->SetBackground(0.5, 0.5, 0.5);
    renderWindow()->AddRenderer(m_renderer);
}

void SceneWidget::addDataSet(vtkSmartPointer<vtkDataSet> dataSet)
{
    // Actor
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();

    // Mapper
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(dataSet);
    actor->SetMapper(mapper);

    m_renderer->AddActor(actor);
    m_renderer->ResetCamera(dataSet->GetBounds());

    renderWindow()->Render();
}

void SceneWidget::setImageData(vtkSmartPointer<vtkImageData> imageData) {
    // An interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
        vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow());

    // Interactor style
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
        vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    renderWindowInteractor->SetInteractorStyle(style);

    vtkSmartPointer<vtkImagePlaneWidget> ipw = 
        vtkSmartPointer<vtkImagePlaneWidget>::New();
    ipw->SetInteractor(renderWindowInteractor);
    //ipw->RestrictPlaneToVolumeOn();
    ipw->SetInputData(imageData);
    ipw->SetWindowLevel(5500, 1000);
    ipw->SetPlaneOrientationToZAxes();
    ipw->DisplayTextOn();

    double origin[3] = {0, 1,0};
    ipw->SetOrigin(origin);
    ipw->UpdatePlacement();
        
    // Render
    renderWindow()->Render();

    renderWindowInteractor->Initialize();
    renderWindow()->Render();
    ipw->On();

    renderWindowInteractor->Start();
}

void SceneWidget::removeDataSet()
{
    vtkActor* actor = m_renderer->GetActors()->GetLastActor();
    if (actor != nullptr) {
        m_renderer->RemoveActor(actor);
    }

    renderWindow()->Render();
}

void SceneWidget::zoomToExtent()
{
    // Zoom to extent of last added actor
    vtkSmartPointer<vtkActor> actor = m_renderer->GetActors()->GetLastActor();
    if (actor != nullptr) {
        m_renderer->ResetCamera(actor->GetBounds());
    }

    renderWindow()->Render();
}
