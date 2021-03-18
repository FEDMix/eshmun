#include "medicalviewer.h"

#include <vtkImageActor.h>
//#include <vtkPSphereSource.h>
#include <vtkDataSetMapper.h>
#include <vtkImageMapper.h>
//#include <vtkPolyDataMapper.h>

MedicalViewer::MedicalViewer(QWidget *parent)
    : QVTKOpenGLNativeWidget(parent),
      renderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
      // renderer(vtkSmartPointer<vtkRenderer>::New()),
      // mInteractor(vtkSmartPointer<QVTKInteractor>::New()),
      // mInteractorStyle(vtkSmartPointer<vtkInteractorStyle>::New()),
      reader(vtkSmartPointer<vtkDICOMImageReader>::New()),
      // imageViewer(vtkSmartPointer<vtkImageViewer2>::New()),
      renderWindowInteractor(
          vtkSmartPointer<vtkRenderWindowInteractor>::New()) {
  // Setup rendering
  readDICOMSeries("1-14.dcm");
  SetRenderWindow(renderWindow);
  showWindow();
}

int MedicalViewer::readDICOMSeries(std::string inputFilename) {
  // Read all the DICOM files in the specified directory.
  reader->SetFileName(inputFilename.c_str());
  reader->Update();
  std::cout << "Read the DICOM file: " << inputFilename << std::endl;
  return 1;
}

void MedicalViewer::showWindow() {
  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();

  // Create actor where the sphere id rendered
  vtkSmartPointer<vtkDataSetMapper> mapper =
      vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(reader->GetOutputPort());

  // Create an actor
  vtkSmartPointer<vtkActor> slice = vtkSmartPointer<vtkActor>::New();
  slice->SetMapper(mapper);

  // Addig actor to renderer
  renderer->AddActor(slice);
  renderer->ResetCamera();

  // Adding renderer to the rednering window
  renderWindow->AddRenderer(renderer);
  renderWindow->Render();
  std::cout << "Window rendered" << std::endl;
}

void MedicalViewer::mouseMoveEvent(QMouseEvent *ev) { emit Mouse_State(); }

void MedicalViewer::onDrawSphereClick() {
  std::cout << "Function triggered" << std::endl;
}
