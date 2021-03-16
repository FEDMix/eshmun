#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QVTKOpenGLNativeWidget.h>
#include <vtkDataSet.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

class SceneWidget : public QVTKOpenGLNativeWidget {
    Q_OBJECT
public:
    explicit SceneWidget(QWidget* parent = nullptr);

    //! Add a data set to the scene
    /*!
    \param[in] dataSet The data set to add
  */
    void addDataSet(vtkSmartPointer<vtkDataSet> dataSet);

    void setImageData(vtkSmartPointer<vtkImageData> imageData);

    //! Remove the data set from the scene
    void removeDataSet();

public slots:
    //! Zoom to the extent of the data set in the scene
    void zoomToExtent();

private:
    vtkSmartPointer<vtkRenderer> m_renderer;
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
};

#endif // SCENEWIDGET_H
