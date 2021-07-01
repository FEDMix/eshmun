#ifndef OVERLAYVIEWER_H
#define OVERLAYVIEWER_H

#include <vtkResliceImageViewer.h>
#include <vtkSmartPointer.h>
#include <vtkImageActor.h>
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"

class OverlayViewer : public vtkResliceImageViewer {

public:
    static OverlayViewer *New();
    vtkTypeMacro(OverlayViewer, vtkObject);

    OverlayViewer();
    ~OverlayViewer();

    void SetOverlay(vtkSmartPointer<vtkImageData> imageData);
    void UpdateDisplayExtent() override;
    void InstallPipeline() override;
    void UnInstallPipeline() override;

private:
    vtkSmartPointer<vtkImageActor> ImageActor2;
    vtkSmartPointer<vtkLookupTable> pColorTable;
    vtkSmartPointer<vtkImageMapToColors> imageMapToColors;
};

#endif // OVERLAYVIEWER_H
