#ifndef MEDICALVIEWER_H
#define MEDICALVIEWER_H

#include <QVTKInteractor.h>
#include <QVTKOpenGLNativeWidget.h>
#include <qsurfaceformat.h>
#include <vtkDICOMImageReader.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkImageViewer2.h>
#include <vtkInteractorStyle.h>
#include <vtkRenderer.h>

class MedicalViewer : public QVTKOpenGLNativeWidget {
  Q_OBJECT
 public:
  MedicalViewer(QWidget *parent = nullptr);

  // Function for reading DICOM series
  int readDICOMSeries(std::string inputFilename);

  // Add a render to the window and show the window
  void showWindow();

  void mouseMoveEvent(QMouseEvent *ev);

 signals:
  void Mouse_State();

 public slots:
  void onDrawSphereClick();

 private:
  // Initialize private variables for rendering
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
  vtkSmartPointer<vtkDICOMImageReader> reader =
      vtkSmartPointer<vtkDICOMImageReader>::New();
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
  vtkSmartPointer<vtkImageViewer2> imageViewer =
      vtkSmartPointer<vtkImageViewer2>::New();
};

#endif  // MEDICALVIEWER_H
