#include "vtkObjectFactory.h" // for New() macro
#include "linkedinteractorstyle.h"
#include "scenewidget.h"

vtkStandardNewMacro(LinkedInteractorStyle);

LinkedInteractorStyle::LinkedInteractorStyle()
{
}

LinkedInteractorStyle::~LinkedInteractorStyle()
{
}

void LinkedInteractorStyle::WindowLevel() {
    // Call super
    vtkInteractorStyleImage::WindowLevel();
    double window = GetCurrentImageProperty()->GetColorWindow();
    double level = GetCurrentImageProperty()->GetColorLevel();
    for(size_t i=0; i < linkedWidgets.size(); i++){
        SceneWidget* sceneWidget = linkedWidgets[i];
        sceneWidget->SetWindowLevel(window, level);
    }
}

void LinkedInteractorStyle::Slice() {
    // Call super
    vtkInteractorStyleImage::Slice();

    int slice = baseWidget->GetSliceIndex();
    cout <<" flag" << slice <<"\n";
    SceneWidget::Orientation orientation = baseWidget->GetOrientation();
    for(int i=0; i < linkedWidgets.size(); i++){
        SceneWidget* linkedSceneWidget = linkedWidgets[i];
        SceneWidget::Orientation linkedOrientation = linkedSceneWidget->GetOrientation();
        cout <<" flag\n";
        if (linkedOrientation == orientation) {
            linkedSceneWidget->SetSliceIndex(slice);
        }
    }
}

void LinkedInteractorStyle::SetBaseWidget(SceneWidget* sceneWidget) {
    baseWidget = sceneWidget;
}

void LinkedInteractorStyle::AddLinkedWidget(SceneWidget* sceneWidget) {
    linkedWidgets.push_back(sceneWidget);
}

