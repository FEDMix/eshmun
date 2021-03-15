#ifndef MEDICALVIEWER_H
#define MEDICALVIEWER_H

#include <QVTKInteractor.h>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkInteractorStyle.h>
#include <vtkRenderer.h>

class MedicalViewer : public QVTKOpenGLNativeWidget {
  Q_OBJECT
 public:
  MedicalViewer(QWidget *parent = nullptr);

  void mouseMoveEvent(QMouseEvent *ev);

 signals:
  void Mouse_State();

 public slots:
  void onDrawSphereClick();

 private:
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderWindow;
  vtkSmartPointer<vtkRenderer> mRenderer;
  vtkSmartPointer<QVTKInteractor> mInteractor;
  vtkSmartPointer<vtkInteractorStyle> mInteractorStyle;
};

#endif  // MEDICALVIEWER_H
