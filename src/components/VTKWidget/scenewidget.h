#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include "linkedinteractorstyle.h"

#include <QVTKOpenGLNativeWidget.h>
#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageData.h>
#include <vtkImageMapper.h>
#include <vtkImageMapper3D.h>
#include <vtkImageSlice.h>
#include <vtkImageActor.h>
#include <vtkResliceImageViewer.h>
#include <vtkImageProperty.h>
#include "overlayviewer.h"

class SceneWidget : public QVTKOpenGLNativeWidget {
    Q_OBJECT
public:
    enum class Orientation {
        AXIAL, CORONAL, SAGITTAL
    };

    explicit SceneWidget(QWidget* parent = nullptr);

    void SetImageData(vtkSmartPointer<vtkImageData> imageData);
    void AnnotationOverlay(vtkSmartPointer<vtkImageData> imageData);
    void SetImageDataConnection(vtkSmartPointer<vtkAlgorithmOutput> connection);
    vtkSmartPointer<vtkImageData> GetDummyData();
    void SaveScreenshot(std::string path);

    /** Link and synchronize (window-level, slice position)
     *  the provided SceneWidget with this one.
     *  @param twoWay   also call AddLinkedSceneWidget on the provided SceneWidget
     */
    void AddLinkedSceneWidget(SceneWidget* sceneWidget, bool twoWay);

    SceneWidget::Orientation GetOrientation() { return orientation; };

public slots:
    void SetPlaneOrientationToAxial();
    void SetPlaneOrientationToCoronal();
    void SetPlaneOrientationToSagittal();
    void SetSliceIndex(int position);
    int GetSliceIndex();
    double GetColorWindow();
    double GetColorLevel();
    void SetWindowLevel(double window, double level);
    void ResetCamera();
    void Refresh();

private:
    vtkSmartPointer<vtkCamera> camera;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
    vtkSmartPointer<LinkedInteractorStyle> style;
    vtkSmartPointer<vtkImageData> imageData;
    vtkSmartPointer<vtkImageMapper> imageMapper;
    vtkSmartPointer<OverlayViewer> imageViewer;
    SceneWidget::Orientation orientation;

    void GetCenterAndDimensions(float*, float*);
};

#endif // SCENEWIDGET_H
