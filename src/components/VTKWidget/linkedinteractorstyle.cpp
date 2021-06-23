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

    double window = baseWidget->GetColorWindow();
    double level = baseWidget->GetColorLevel();
    for(size_t i=0; i < linkedWidgets.size(); i++){
        SceneWidget* sceneWidget = linkedWidgets[i];
        sceneWidget->SetWindowLevel(window, level);
    }
}

void LinkedInteractorStyle::SetBaseWidget(SceneWidget* sceneWidget) {
    baseWidget = sceneWidget;
}

void LinkedInteractorStyle::AddLinkedWidget(SceneWidget* sceneWidget) {
    linkedWidgets.push_back(sceneWidget);
}

