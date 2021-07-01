#include "overlayviewer.h"

#include "vtkCamera.h"
#include "vtkCommand.h"
#include "vtkImageActor.h"
#include "vtkImageData.h"
#include "vtkImageMapToWindowLevelColors.h"
#include "vtkImageMapper3D.h"
#include "vtkInformation.h"
#include "vtkInteractorStyleImage.h"
#include "vtkObjectFactory.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkLookupTable.h"
#include "vtkImageProperty.h"

vtkStandardNewMacro(OverlayViewer);

OverlayViewer::OverlayViewer() {
    this->pColorTable = vtkSmartPointer<vtkLookupTable>::New();
    pColorTable->SetNumberOfColors(3);
    pColorTable->SetTableRange(0, 2);
    pColorTable->SetTableValue(0, 0, 0, 1, 0);
    pColorTable->SetTableValue(1, 1, 0, 0, 0.5);
    pColorTable->SetTableValue(2, 0, 1, 0, 0.5);
    pColorTable->Build();

    imageMapToColors = vtkSmartPointer<vtkImageMapToColors>::New();
    imageMapToColors->SetLookupTable(pColorTable);
    imageMapToColors->PassAlphaToOutputOn();

    ImageActor2 = vtkSmartPointer<vtkImageActor>::New();
    ImageActor2->SetInterpolate(false);
    ImageActor2->SetPickable(false);
}

OverlayViewer::~OverlayViewer() {

}

void OverlayViewer::SetOverlay(vtkSmartPointer<vtkImageData> imageData) {
    imageMapToColors->SetInputData(imageData);
    UpdateDisplayExtent();
}

void OverlayViewer::InstallPipeline() {
    vtkResliceImageViewer::InstallPipeline();

    if (this->Renderer && this->ImageActor2) {
        this->Renderer->AddViewProp(this->ImageActor2);
    }

    if (this->ImageActor2 && this->imageMapToColors)
    {
        this->ImageActor2->GetMapper()->SetInputConnection(this->imageMapToColors->GetOutputPort());
    }
}

void OverlayViewer::UnInstallPipeline() {
    vtkResliceImageViewer::UnInstallPipeline();

    if (this->ImageActor2) {
        this->ImageActor2->GetMapper()->SetInputConnection(nullptr);
    }

    if (this->Renderer && this->ImageActor2) {
        this->Renderer->RemoveViewProp(this->ImageActor2);
    }
}

void OverlayViewer::UpdateDisplayExtent()
{
  vtkAlgorithm* input = this->GetInputAlgorithm();
  if (!input || !this->ImageActor || !this->ImageActor2)
  {
    return;
  }

  input->UpdateInformation();
  vtkInformation* outInfo = input->GetOutputInformation(0);
  int* w_ext = outInfo->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT());

  // Is the slice in range ? If not, fix it

  int slice_min = w_ext[this->SliceOrientation * 2];
  int slice_max = w_ext[this->SliceOrientation * 2 + 1];
  if (this->Slice < slice_min || this->Slice > slice_max)
  {
    this->Slice = static_cast<int>((slice_min + slice_max) * 0.5);
  }

  // Set the image actor

  switch (this->SliceOrientation)
  {
    case vtkImageViewer2::SLICE_ORIENTATION_XY:
      this->ImageActor->SetDisplayExtent(
        w_ext[0], w_ext[1], w_ext[2], w_ext[3], this->Slice, this->Slice);
      this->ImageActor2->SetDisplayExtent(
        w_ext[0], w_ext[1], w_ext[2], w_ext[3], this->Slice, this->Slice);
      break;

    case vtkImageViewer2::SLICE_ORIENTATION_XZ:
      this->ImageActor->SetDisplayExtent(
        w_ext[0], w_ext[1], this->Slice, this->Slice, w_ext[4], w_ext[5]);
      this->ImageActor2->SetDisplayExtent(
        w_ext[0], w_ext[1], this->Slice, this->Slice, w_ext[4], w_ext[5]);
      break;

    case vtkImageViewer2::SLICE_ORIENTATION_YZ:
      this->ImageActor->SetDisplayExtent(
        this->Slice, this->Slice, w_ext[2], w_ext[3], w_ext[4], w_ext[5]);
      this->ImageActor2->SetDisplayExtent(
        this->Slice, this->Slice, w_ext[2], w_ext[3], w_ext[4], w_ext[5]);
      break;
  }

  // Figure out the correct clipping range

  if (this->Renderer)
  {
    if (this->InteractorStyle && this->InteractorStyle->GetAutoAdjustCameraClippingRange())
    {
      this->Renderer->ResetCameraClippingRange();
    }
    else
    {
      vtkCamera* cam = this->Renderer->GetActiveCamera();
      if (cam)
      {
        double bounds[6];
        this->ImageActor->GetBounds(bounds);
        double spos = bounds[this->SliceOrientation * 2];
        double cpos = cam->GetPosition()[this->SliceOrientation];
        double range = fabs(spos - cpos);
        double* spacing = outInfo->Get(vtkDataObject::SPACING());
        double avg_spacing = (spacing[0] + spacing[1] + spacing[2]) / 3.0;
        cam->SetClippingRange(range - avg_spacing * 3.0, range + avg_spacing * 3.0);
      }
    }
  }
}
