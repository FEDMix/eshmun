#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QVTKOpenGLNativeWidget.h>
#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkImagePlaneWidget.h>

class SceneWidget : public QVTKOpenGLNativeWidget {
    Q_OBJECT
public:
    explicit SceneWidget(QWidget* parent = nullptr);

    void SetImageData(vtkSmartPointer<vtkImageData> imageData);
    vtkSmartPointer<vtkImageData> GetDummyData();
    void SaveScreenshot(std::string path);

public slots:
    void SetPlaneOrientationToXAxis();
    void SetPlaneOrientationToYAxis();
    void SetPlaneOrientationToZAxis();
    void SetSliceIndex(int position);

    void ResetCamera();
    void Refresh();

private:
    vtkSmartPointer<vtkCamera> camera;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
    vtkSmartPointer<vtkImagePlaneWidget> ipw;
    vtkSmartPointer<vtkImageData> imageData;

    void GetCenterAndDimensions(float*, float*);
};

#endif // SCENEWIDGET_H
