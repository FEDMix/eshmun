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

    SceneWidget* sceneWidget = dynamic_cast<SceneWidget*>(baseWidget);
    double window = sceneWidget->GetColorWindow();
    double level = sceneWidget->GetColorLevel();
    for(int i=0; i < linkedWidgets.size(); i++){
        SceneWidget* sceneWidget = dynamic_cast<SceneWidget*>(linkedWidgets[i]);
        sceneWidget->SetWindowLevel(window, level);
    }
}

void LinkedInteractorStyle::SetBaseWidget(QWidget* sceneWidget) {
    baseWidget = sceneWidget;
}

void LinkedInteractorStyle::AddLinkedWidget(QWidget* sceneWidget) {
    linkedWidgets.push_back(sceneWidget);
}