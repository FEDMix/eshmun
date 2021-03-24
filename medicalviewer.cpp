#include "medicalviewer.h"

MedicalViewer::MedicalViewer(QWidget *parent)
    : QVTKOpenGLNativeWidget(parent),
      renderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
      reader(vtkSmartPointer<vtkDICOMImageReader>::New()),
      renderWindowInteractor(vtkSmartPointer<vtkRenderWindowInteractor>::New()),
      imageViewer(vtkSmartPointer<vtkImageViewer2>::New()) {
  // Setup rendering
  readDICOMSeries("1-14.dcm");
  // QSurfaceFormat format = QVTKOpenGLNativeWidget::defaultFormat();
  // format.setSamples(0);
  // QSurfaceFormat::setDefaultFormat(format);

  // this->setFormat(format);
  // this->setEnableHiDPI(true);
  // this->resize(256, 256);

  imageViewer->SetInputConnection(reader->GetOutputPort());
  imageViewer->SetupInteractor(GetInteractor());
  // imageViewer->SetupInteractor(this->GetRenderWindow()->GetInteractor());
  imageViewer->Render();
  // renderWindow.set
  this->setRenderWindow(imageViewer->GetRenderWindow());
  this->show();
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
  // Inicializa
  std::cout << "Window rendered" << std::endl;
}

void MedicalViewer::mouseMoveEvent(QMouseEvent *ev) { emit Mouse_State(); }

void MedicalViewer::onDrawSphereClick() {
  std::cout << "Function triggered" << std::endl;
}
