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
    
    void AddLinkedViewer(OverlayViewer* viewer);
    void SetSlice(int slice) override;
    void SetSlice(int slice, bool doSync);
    void SetColorWindow(double s) override;
    void SetColorWindow(double s, bool doSync);
    void SetColorLevel(double s) override;
    void SetColorLevel(double s, bool doSync);

private:
    vtkSmartPointer<vtkImageActor> ImageActor2;
    vtkSmartPointer<vtkLookupTable> pColorTable;
    vtkSmartPointer<vtkImageMapToColors> imageMapToColors;
    std::vector<OverlayViewer*> linkedViewers;
};

#endif // OVERLAYVIEWER_H
